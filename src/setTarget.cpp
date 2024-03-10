#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
//#include <actionlib_tutorials/FibonacciAction.h>
#include <assignment_2_2023/PlanningAction.h>
//from geometry_msgs.msg import Point
#include <geometry_msgs/Point.h>
#include "nav_msgs/Odometry.h"
#include "assignment_2_2023/Parameters.h"
#include <string>
#include <signal.h>


float pos_x;
float pos_y;
float vel_x;
float vel_z;
std::string feedback; 
bool g_shutdown_requested = false; //is setted true when ctrl-c is pressed

/**
* \file setTarget.cpp
* \brief set the taget position of the robot
* \author Andrea Scorrano
* \verion 1.0
* \date 10/03/2024
- Action Clients / Services
* \param [in] world_width Define the width of the discretized world.
*
*
* Subscribes to: <BR>
* ° /odom
* ° /reaching_goal/feedback
* 
* Publishes to: <BR>
* ° /robot/parameters
*
*
* Action client: <BR>
* °/reaching_goal

* Description : <BR>
*
*This node that implements an action client, allow the user to set a target (x, y) or to cancel it. Has been used the feedback/status of the action server to know when the target has been reached. 
*The node also publishes the robot position and velocity as a custom message (x,y, vel_x, vel_z), by relying on the values published on the topic /odom.

*/


/**
* \brief get the position and the velocity from the topic /odom
* \param msg
*
* This function get the position and the velocity from the topic /odom and put in the variables pos_x,pox_y,vel_x,vel_z
*/
void odomCallback(const nav_msgs::Odometry::ConstPtr &msg)
{

  //get the position and the velocity from the topic /odom
  // ROS_INFO("%s", msg->header.frame_id.c_str());
  // ROS_INFO("%f", msg->twist.twist.linear.x);
  ROS_INFO("[pose x: %f ,  pose y: %f ,  vel x: %f  vel z: %f]",
   msg->pose.pose.position.x,
   msg->pose.pose.position.x,
   msg->twist.twist.linear.x,
   msg->twist.twist.angular.z);
  
  pos_x=msg->pose.pose.position.x;
  pos_y=msg->pose.pose.position.x;
  vel_x=msg->twist.twist.linear.x;
  vel_z=msg->twist.twist.angular.z;
  
}




/**
* \brief get the feedback from the topic /reaching_goal/feedback"
* \param msg
*
* This function get the feedback from the topic /reaching_goal/feedback and put in the variable feedback
*/
void feedbackCallBack(const assignment_2_2023::PlanningActionFeedback::ConstPtr &msg)
{
  // ROS_INFO("%s", msg->header.frame_id.c_str());
  // ROS_INFO("%f", msg->twist.twist.linear.x);
  
  //get the feedback 
	feedback=msg->feedback.stat;
  
}

/**
* \brief shut down handler
* \param sig	
*
* This function is called by this function: signal(SIGINT, shutdownHandler) it check when the command ctrl-c is pressed on the keyboard
*/

void shutdownHandler(int sig) 
{

    //This function will be called when the SIGINT (Ctrl+C) signal is received
	ROS_INFO("Shutting down...");
 	g_shutdown_requested = true;
 }


/**
* \brief main function
* \param argc
* \param argv
*
*
*/


int main (int argc, char **argv)
	{
	ros::init(argc, argv, "Planning");
	ros::NodeHandle nh;
	 // create the action client
	 // true causes the client to spin its own thread
	actionlib::SimpleActionClient<assignment_2_2023::PlanningAction> ac("/reaching_goal", true);
	ROS_INFO("Waiting for action server to start.");
	 // wait for the action server to start
	ac.waitForServer(); //will wait for infinite time

	ROS_INFO("Action server started, sending goal.");

	assignment_2_2023::PlanningGoal goal; //initialize a goal
	  //geometry_msgs::Point desired_position_;

	ROS_INFO("insert x position:");
	std::cin>>goal.target_pose.pose.position.x;
	  
	  
	ROS_INFO("insert y position:");
	std::cin>>goal.target_pose.pose.position.y;
	  
	ROS_INFO("press ctrl-c to cancel the goal ");
	ros::Duration(3.0).sleep(); //sleep 3 seconds in order to show the message
	  
	// send a goal to the action
	ac.sendGoal(goal);

	ros::Subscriber sub = nh.subscribe("odom", 1, odomCallback); //define a subscriber to get the position of the robot
	ros::Subscriber subFeedback =nh.subscribe("/reaching_goal/feedback",1,feedbackCallBack);  //define a subscriber to get the feedback 
	ros::Publisher pub2 = nh.advertise<assignment_2_2023::Parameters>("robot/parameters", 1); //define a publisher for the x position the y position the velocity along x, angular velocity along z axis 
	  
	std::string state;
	signal(SIGINT, shutdownHandler); //handler for the ctrl-c


	while(ros::ok() && !g_shutdown_requested ) //continue while ros is ok and ctrl-c is not pressed
	{
		assignment_2_2023::Parameters parameters; //define parameters
	  	parameters.pos_x=  pos_x;
	  	parameters.pos_y = pos_y;
	 	parameters.vel_x = vel_x;
	  	parameters.vel_z = vel_z;
	  	pub2.publish(parameters);
	  	actionlib::SimpleClientGoalState state = ac.getState(); //get state 
	   	//ROS_INFO("status: %s", feedback.c_str());
	   	if(feedback.compare("Target reached!")==0) //check if the feedback return the Target reachet
	   	{
	   		break; //exit from the loop
	   	}
	   	
	   	ros::spinOnce();

		
	}  
	ac.cancelGoal(); //when ctrl-c or the target is reached is pressed the goal is cancelled
  

  return 0;
}
