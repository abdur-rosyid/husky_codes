/* @author Abdur Rosyid
 * Website: https://abdurrosyid.com
 * Email: abdoorasheed@gmail.com
 */

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>

/** function declarations **/
bool moveToGoal(double xGoal, double yGoal, double thetaGoal);

/** declare the goal coordinate **/
//For Clearpath World
//double xMyGoal = 3.39586314387;
//double yMyGoal = -3.07275137685;
//For empty world with map (goal is measured from top-left corner of the map)
double yOffset = 5;
double xMyGoal = 5;
double yMyGoal = 0 + yOffset;
double thetaMyGoal = 0.00;

bool goalReached = false;

int main(int argc, char** argv){
    ros::init(argc, argv, "map_navigation");
    ros::NodeHandle n;
    ros::spinOnce();

    goalReached = moveToGoal(xMyGoal, yMyGoal, thetaMyGoal);

    if (goalReached){
        ROS_INFO("Congratulations!");
        ros::spinOnce();

        }else{
             ROS_INFO("Hard Luck!");
             }
}

bool moveToGoal(double xGoal, double yGoal, double thetaGoal){

    //define a client for to send goal requests to the move_base server through a SimpleActionClient
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

    //wait for the action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;
    tf::Quaternion quat;
    tf::Transform goal_transform;

    //set up the frame parameters
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    /* moving towards the goal*/
    quat.setRPY(0.0, 0.0, thetaGoal);
    goal_transform.setRotation(quat);

    goal.target_pose.pose.position.x =  xGoal;
    goal.target_pose.pose.position.y =  yGoal;
    goal.target_pose.pose.position.z =  0.0;  

    //goal.target_pose.pose.orientation.x = 0.0;
    //goal.target_pose.pose.orientation.y = 0.0;
    //goal.target_pose.pose.orientation.z = 0.0;
    //goal.target_pose.pose.orientation.w = 1.0;
    goal.target_pose.pose.orientation.x = goal_transform.getRotation().x();
    goal.target_pose.pose.orientation.y = goal_transform.getRotation().y();
    goal.target_pose.pose.orientation.z = goal_transform.getRotation().z();
    goal.target_pose.pose.orientation.w = goal_transform.getRotation().w();

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

