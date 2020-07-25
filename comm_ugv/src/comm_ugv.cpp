/** \author Ardiansyah Al Farouq. */

// CPP headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <iostream>

// ROS headers
#include <ros/ros.h>

// MoveIt! headers
#include <moveit/move_group_interface/move_group.h>

// Std C++ headers
#include <string>
#include <vector>
#include <map>

//#include "tf/transform_broadcaster.h"
//#include "tf/transform_datatypes.h"
//#include "geometry_msgs/TransformStamped.h"
#include <tf/transform_broadcaster.h>

//////////////////////////////////////////
#define xData 	8081
#define yData 	8082
#define zData 	8083
#define qXData 	8084
#define qYData 	8085
#define qZData 	8086
#define qQData 	8087

//////////////////////////////////////////////////////////////////////////////////////////////////////////
static int *resultX, *resultY, *resultZ, *resultQX, *resultQY, *resultQZ, *resultQQ;
int datX=0, datY=0, datZ=0, datQX=0, datQY=0, datQZ=0, datQQ=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void indivData(){
	int KeyX = xData;	int KeyY = yData;
	int KeyZ = zData;	int KeyQQ = qQData;
	int KeyQX = qXData; int KeyQY = qYData; int KeyQZ = qZData;

	int spaceIdX = shmget(KeyX, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	resultX = (int*)shmat(spaceIdX, NULL, 0);

	int spaceIdY = shmget(KeyY, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	resultY = (int*)shmat(spaceIdY, NULL, 0);

	int spaceIdZ = shmget(KeyZ, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	resultZ = (int*)shmat(spaceIdZ, NULL, 0);

	int spaceIdQX = shmget(KeyQX, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	resultQX = (int*)shmat(spaceIdQX, NULL, 0);

	int spaceIdQY = shmget(KeyQY, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	resultQY = (int*)shmat(spaceIdQY, NULL, 0);

	int spaceIdQZ = shmget(KeyQZ, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	resultQZ = (int*)shmat(spaceIdQZ, NULL, 0);

	int spaceIdQQ = shmget(KeyQQ, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	resultQQ = (int*)shmat(spaceIdQQ, NULL, 0);

	*resultX = *resultY = *resultZ = *resultQX = *resultQY = *resultQZ = *resultQQ = 0;
}

int main(int argc, char** argv)
{	
	ros::init(argc, argv, "comm_ugv");
	ROS_INFO("Start Communication");
	static tf::TransformBroadcaster br;
	tf::Transform transform;

	indivData();

	//sleep(10);
	ros::Rate rate(50);	
	while (ros::ok())
	{
		float X = (float)*resultX / 1000000.0;
		float Y = (float)*resultY / 1000000.0;
		float Z = (float)*resultZ / 1000000.0;
		float QX = (float)*resultQX / 1000000.0;
		float QY = (float)*resultQY / 1000000.0;
		float QZ = (float)*resultQZ / 1000000.0;
		float QQ = (float)*resultQQ / 1000000.0;

		if( Z < 0) Z = Z *-1;
		//transform.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
		transform.setRotation( tf::Quaternion(QX, QY, QZ, QQ) );		
		transform.setOrigin( tf::Vector3(X/1000.0,Y/1000.0,Z/1000.0) );
		
		br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "camera_rs_link", "object"));
		//br.sendTransform(tf::StampedTransform(transform, ros::Time(0), "/camera_rs_link", "/object"));
		//br.sendTransform(tf::StampedTransform(transform, ros::Time::now() - ros::Duration(32400), "/camera_rs_link", "/object"));
		printf("\n- %f %f %f\n",X/1000.0,Y/1000.0,Z/1000.0);
		rate.sleep();
		//ROS_INFO("__");
		printf("\n ..%f %f %f\n",X/1000.0,Y/1000.0,Z/1000.0);
		ros::spinOnce();

	}
	ROS_INFO("Stop Sleep");
	return EXIT_SUCCESS;
}
