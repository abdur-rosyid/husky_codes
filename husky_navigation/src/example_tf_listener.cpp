/* Modified from the code authored by Jordi Pages, PAL Robotics */
/* Modified by @author Abdur Rosyid
 * Website: https://abdurrosyid.com
 * Email: abdoorasheed@gmail.com
 */


// ROS headers
#include <ros/ros.h>

// TF Transform Listener
#include <tf/transform_listener.h>
#include <tf2/LinearMath/Transform.h>

#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/PoseStamped.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Std C++ headers
#include <string>
#include <vector>
#include <map>

using namespace std;

/** function declarations **/
bool moveToGoal(double px, double py, double qx, double qy, double qz, double qw);

bool goalReached = false;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "demoTfListener");
  ros::NodeHandle node;
  ros::spinOnce();

  tf::TransformListener listener;
  geometry_msgs::PoseStamped goal_pose;

  ros::Rate rate(10.0);
  while (node.ok()){
    tf::StampedTransform transform;
    try{
      //wait for the transform to be found
      listener.waitForTransform("/odom", "/object_6", ros::Time(0), ros::Duration(10.0) );
      //Once the transform is found,get the initial_transform transformation.
      listener.lookupTransform("/odom", "/object_6", ros::Time(0), transform);
      double vpx = transform.getOrigin().x();
      double vpy = transform.getOrigin().y();
      double vpz = transform.getOrigin().z();
      double vqx = transform.getRotation().x();
      double vqy = transform.getRotation().y();
      double vqz = transform.getRotation().z();
      double vqw = transform.getRotation().w();
      cout<< "Current position wrt odom: ("<< vpx << ","<< vpy << ","<< vpz << ")"<< endl;
      cout<< "Current orientation wrt odom: ("<< vqx << ","<< vqy << ","<< vqz << ","<< vqw << ")"<< endl;

      goal_pose.pose.position.x = vpx;
      goal_pose.pose.position.y = vpy;
      goal_pose.pose.position.z = vpz;
      goal_pose.pose.orientation.x = vqx;
      goal_pose.pose.orientation.y = vqy;
      goal_pose.pose.orientation.z = vqz;
      goal_pose.pose.orientation.w = vqw;

      goalReached = moveToGoal(vpx, vpy, vqx, vqy, vqz, vqw);

      if (goalReached){
          ROS_INFO("Congratulations!");
          ros::spinOnce();

          }else{
                   ROS_INFO("Hard Luck!");
               }
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }

    rate.sleep();
  }  
      
}

bool moveToGoal(double px, double py, double qx, double qy, double qz, double qw){

    //define a client for to send goal requests to the move_base server through a SimpleActionClient
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

    //wait for the action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    //set up the frame parameters
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    /* moving towards the goal*/
    goal.target_pose.pose.position.x =  px;
    goal.target_pose.pose.position.y =  py;
    goal.target_pose.pose.position.z =  0.0;  

    goal.target_pose.pose.orientation.x = qx;
    goal.target_pose.pose.orientation.y = qy;
    goal.target_pose.pose.orientation.z = qz;
    goal.target_pose.pose.orientation.w = qw;

    ROS_INFO("Sending goal location ...");
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("You have reached the destination");
        return true;
    }
    else{
        ROS_INFO("The robot failed to reach the destination");
        return false;
    }

}

