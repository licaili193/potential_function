#!/usr/bin/env python

import rospy
import tf
import math
from geometry_msgs.msg import TransformStamped
from potential_function.srv import *


from robot import *
import time
import math
import threading
import random

import Queue

c = threading.Condition()
gIsDisco = False
gIsBusy = False

_sounds = ['1853595354444153485f48495f564f',
           '1853595354435552494f55535f3034',
           '1853595354574855485f4f485f3230',
           '1853595354424f5f4f4b41595f3033',
           '1853595354424f5f56375f5941574e',
           '18535953545441485f4441485f3031',
           '1853595354455843495445445f3031',
           '1853595354424f5f56375f56415249',
           '1853595354484f5253455748494e32',
           '185359535446585f4341545f303100',
           '185359535446585f444f475f303200',
           '185359535444494e4f534155525f33',
           '185359535446585f4c494f4e5f3031',
           '185359535446585f30335f474f4154',
           '185359535443524f434f44494c4500',
           '1853595354454c455048414e545f30',
           '1853595354585f534952454e5f3032',
           '1853595354545255434b484f524e00',
           '1853595354454e47494e455f524556',
           '18535953545449524553515545414c',
           '185359535448454c49434f50544552',
           '1853595354414952504f52544a4554',
           '1853595354545547424f41545f3031',
           '1853595354545241494e5f57484953',
           '1853595354424f545f435554455f30',
           '18535953544f545f435554455f3033',
           '1853595354474f42424c455f303031',
           '185359535455535f4c495042555a5a',
           '1853595354434f4e46555345445f31',
           '18535953544f545f435554455f3034',
           '1853595354564f4943453000000000',
           '1853595354564f4943453100000000',
           '1853595354564f4943453200000000',
           '1853595354564f4943453300000000',
           '1853595354564f4943453400000000']


def dashCallback(data):
    global x
    global y
    global theta
    x = data.transform.translation.x
    y = data.transform.translation.y
    q = (data.transform.rotation.x,data.transform.rotation.y,data.transform.rotation.z,data.transform.rotation.w)
    euler = tf.transformations.euler_from_quaternion(q)
    theta = euler[2]
    #rospy.loginfo("Dash position: x->"+str(x)+" y->"+str(y)+" theta->"+str(theta))

def goalCallback(data):
    global gx
    global gy
    gx = data.transform.translation.x
    gy = data.transform.translation.y
    #rospy.loginfo("Goal position: x->"+str(gx)+" y->"+str(gy))

def nf_client():
    global x
    global y
    global gx
    global gy

    rospy.wait_for_service('nf_grad')
    try:
        nf = rospy.ServiceProxy('nf_grad', GetPotentialGrad)
        resp = nf(x, y, gx, gy)
        return [resp.res, resp.dx, resp.dy, resp.g]
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def prop(a, b, x):
    return int(x/a*b)

def proc():
    global theta
    global cmd
    t_ori = theta-math.pi
    if t_ori<0:
        t_ori = t_ori+2*math.pi
    if t_ori>=2*math.pi:
        t_ori = t_ori-2*math.pi
    res = nf_client()
    if res[0] == 0:
        v = math.cos(theta-math.pi/2)*(-res[1])+math.sin(theta-math.pi/2)*(-res[2]);
        w = -math.sin(theta-math.pi/2)*(-res[1])+math.cos(theta-math.pi/2)*(-res[2]);
        print "v->" +str(v) +" w->" +str(w) +" theta->" +str(theta-math.pi/2)
        vol = prop(1,100*res[3]/(res[3]+0.1),v)
        #vol = prop(1,300,v)
        dic = prop(1,300,w)
        print "vo->" +str(vol) +" wm->" +str(dic)
        cmd._commandPhaser("wheel,"+str(vol)+","+str(dic))
    else:
        print "Cannot Run NF."
    

def listener():
    rospy.init_node('dash_go', anonymous=True)

    rospy.Subscriber("/vicon/Dash/body", TransformStamped, dashCallback)
    rospy.Subscriber("/vicon/Goal/Goal", TransformStamped, goalCallback)

    while(1):
	time.sleep(0.1)
        proc()


class DashCommandSender(threading.Thread):
    CONNECTED = 0
    DISCONNECTED = 1
    CONNECTING = 2
    DISCONNECTING = 3

    stopthread = threading.Event()

    def __init__(self):
        threading.Thread.__init__(self)
        self.q = Queue.Queue()
        self.lastSendTime = time.time()

        self.dash = robot("DC:86:F3:1F:C5:E9", False)
        self.connectStatus = DashCommandSender.DISCONNECTED

        self.isDisco = False

    def __del__(self):
        self.stop()

    def clear(self):
        self.q.clear()
        self.lastSendTime = time.time()

    def addCommand(self, cmd):
        self.q.put_nowait(cmd)

    def _commandPhaser(self, cmd):
        if cmd == 'connect':
            self.connectStatus = DashCommandSender.CONNECTING
            if not self.dash.isConnected:
                try:
                    self.dash.connect()
                    self.connectStatus = DashCommandSender.CONNECTED
                except:
                    self.connectStatus = DashCommandSender.DISCONNECTED
        elif cmd == 'disconnect':
            self.connectStatus = DashCommandSender.DISCONNECTING
            if self.dash.isConnected:
                self.dash.disconnect()
                time.sleep(1)
                self.connectStatus = DashCommandSender.DISCONNECTED
        elif cmd == 'sound':
            if self.dash.isConnected:
                self.dash.playSound(_sounds[random.randrange(0,35)])
        elif 'wheel' in cmd:
            if self.dash.isConnected:
                scmd = cmd.split(',')
                v = int(scmd[1])
                r = int(scmd[2])
                if v == 0 and r == 0:
                    self.dash.stopWheels()
                else:
                    print str(v) + ',' + str(r)
                    self.dash.setWheelSpeed(v,r)
        else:
            print 'Unknow command...'

    def killAll(self):
        while not self.q.empty():
            self.q.get_nowait()
        self.dash.stopWheels()

    def run(self):
        global gIsDisco
        global gIsBusy

        red = 16
        green = 71
        blue = 41
        redStep = 10
        greenStep = -20
        blueStep = 15

        step = 45
        pos = 90

        while not self.stopthread.isSet():
            #gtk.threads_enter()
            if (not self.q.empty()):
                self._commandPhaser(self.q.get_nowait())
                self.lastSendTime = time.time()
            #gtk.threads_leave()
            red += redStep
            if (red < 0) | (red > 255):
        	red -= redStep
        	redStep = -redStep
            green += greenStep
            if (green < 0) | (green > 255):
        	green -= greenStep
        	greenStep = -greenStep
            blue += blueStep
            if (blue < 0) | (blue > 255):
        	blue -= blueStep
        	blueStep = -blueStep

            c.acquire()
            gIsBusy = True
            if math.ceil(time.time()*100)%10 == 0 and gIsDisco:
                self.dash.colorAll(red, green, blue, red, green, blue, red, green, blue)
           
            if math.ceil(time.time()*10)%10 == 0 and gIsDisco:
                pos += step
                if (pos < -90) | (pos > 90):
                    pos -= (2* step)
                    step = -step
                    self.dash.moveHeadY(0)
                    self.dash.moveHeadX(pos)
            gIsBusy = False
            c.notify_all()
            c.release()

    def stop(self):
        self.stopthread.set()


if __name__ == '__main__':
    global cmd
    global theta
    cmd = DashCommandSender()
    cmd._commandPhaser('connect')
    listener()
    cmd._commandPhaser('disconnect')
