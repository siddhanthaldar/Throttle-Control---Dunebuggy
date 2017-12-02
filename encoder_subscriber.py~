#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import UInt16
#from std_msgs.msg import Float64

tar_vel = 0
act_vel = 0
oldLeft = 0
oldRight = 0
errorsum = 0
prev_error = 0

def callback_xbox(data) :
	global tar_vel	
	global v_tx
	global v_ty
	global v_tz
	global angle
	v_tx = data.linear.x
	v_ty = data.linear.y
	v_tz = data.linear.z

	if v_tx :
		tar_vel += 1     #Increment velocity by 1
	if v_ty  :
		tar_vel -= 1     #Decrease velocity by 1
	if v_tz  :
		tar_vel = 0
	


def callback(data):
	global left_vel
	global right_vel
	global newLeft
	global newRight
	global tar_vel
	global oldLeft 
	global oldRight 
	global error
	global kp
	global ki
	global kd
	global tar_vel
	global errorsum 
	global errordiff
	global act_vel
	global prev_error 
	global output
	global angle 
	

	output = 0
	
	kp = 4
	ki = 0.001
	kd = 0 

        newLeft = data.linear.x
        newRight = data.linear.y
	
	#wheel radius = 10.5 inch, dt = 20ms, no. of ticks per turn = 12800
	left_vel = 0.006452 * (newLeft - oldLeft) * 18 / 5                 
	right_vel = 0.006452 * (newRight - oldRight) * 18 / 5
	act_vel = (left_vel + right_vel)/2

	error = tar_vel - act_vel
	errorsum = errorsum + error
	errordiff = error - prev_error
	
	output = kp * error + ki * errorsum + kd * errordiff
	prev_error = error
	
	#if output < 0:
	#	output = - output
	
	angle = int(output)
	if angle > 30:
		angle = 30
	if angle < 0 :
		angle = 0
	oldLeft = newLeft
	oldRight = newRight

	pub = rospy.Publisher("pid", UInt16, queue_size = 10)
        pub.publish(angle)	
	
	'''
        print "left_vel: %f" % left_vel
        print "right_vel: %f" % right_vel
        print "newleft: %f" % newLeft
        print "newRight: %f" % newRight
	print "Error: %f" % error
	print "Angle: %f" % angle
	print("tar_vel: %f" % tar_vel)
	print("Act_vel: %f" % act_vel)
	'''

def encoder():
    global angle
    global tar_vel
    global act_vel
    angle = 0
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("joy_data", Twist, callback_xbox)
    rospy.Subscriber("encoders", Twist, callback)
    #pub = rospy.Publisher("pid", UInt16, queue_size = 10)
    #pub.publish(angle)	
    #graph1 = rospy.Publisher("target_vel", Float64, queue_size = 10)
    #graph1.publish(tar_vel)
    #graph2 = rospy.Publisher("actual_vel", Float64, queue_size = 10)
    #graph2.publish(act_vel)
    
    rospy.spin()

if __name__ == '__main__':
    encoder()
