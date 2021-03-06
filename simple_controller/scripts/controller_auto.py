#!/usr/bin/env python

# Author: Abdur Rosyid
# Website: https://abdurrosyid.com
# Email: abdoorasheed@gmail.com

# This code works well in simulation but might not work properly in a real UGV

import rospy
import tf
from nav_msgs.msg import Odometry
from tf.transformations import euler_from_quaternion
from geometry_msgs.msg import Point, Twist
from math import atan2
 
x = 0.0
y = 0.0 
theta = 0.0
 
def newOdom(msg):
    global x
    global y
    global theta
 
    x = msg.pose.pose.position.x
    y = msg.pose.pose.position.y
 
    rot_q = msg.pose.pose.orientation
    (roll, pitch, theta) = euler_from_quaternion([rot_q.x, rot_q.y, rot_q.z, rot_q.w])
 
rospy.init_node("speed_controller")
listener = tf.TransformListener()
 
sub = rospy.Subscriber("/odometry/filtered", Odometry, newOdom)
pub = rospy.Publisher("/cmd_vel", Twist, queue_size = 1)
 
speed = Twist()
 
r = rospy.Rate(4)

while not rospy.is_shutdown():
    try:
        (trans,rot) = listener.lookupTransform('/odom', '/object', rospy.Time(0))

        px = transform.getOrigin().x();
        py = transform.getOrigin().y();
        pz = transform.getOrigin().z();
        qx = transform.getRotation().x();
        qy = transform.getRotation().y();
        qz = transform.getRotation().z();
        qw = transform.getRotation().w();        

    except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
        continue

goal = Point()
goal.x = pz
goal.y = py
 
while not rospy.is_shutdown():
    inc_x = goal.x -x
    inc_y = goal.y -y
 
    angle_to_goal = atan2(inc_y, inc_x)
 
    if abs(angle_to_goal - theta) > 0.1:
        if inc_x > 0.1 and inc_y > 0.1:
            speed.linear.x = 0.0
            speed.angular.z = 0.3
        else:
            speed.linear.x = 0.0
            speed.angular.z = 0.0
    else:
        speed.linear.x = 0.5
        speed.angular.z = 0.0
 
    pub.publish(speed)
    r.sleep()    
