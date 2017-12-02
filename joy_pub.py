#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

def callback(data):
	twist=Twist()
	twist.linear.x=data.buttons[6]
	twist.linear.y=data.buttons[7]
	twist.linear.z=data.buttons[1]
	pub.publish(twist)
def start():
	global pub
	pub = rospy.Publisher('joy_data', Twist,queue_size=10)
	rospy.Subscriber("joy",Joy,callback)
	rospy.init_node('JoyPubli')
	rospy.spin()
if __name__ == '__main__':
	start()
