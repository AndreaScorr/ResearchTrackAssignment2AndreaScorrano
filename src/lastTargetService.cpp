#include "ros/ros.h"
#include "assignment_2_2023/LastTarget.h"
#include "assignment_2_2023/PlanningAction.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

/**
* \file lastTargetService.cpp
* \brief Service for last Target setted
* \author Andrea Scorrano
* \version 1.0
* \date 10/03/2024
*
*
* Subscribes to: <BR>
* ° /robot_behavior_state_machine/smach/container_status
*
* Publishes to: <BR>
* ° /PlayWithRobot
*
* Services : <BR>
* ° /lastTarget
*
* Description :
*
* This is a service node that, when called, returns the coordinates of the last target sent by the user.
*
*/



/**
* \brief get the desired positions by the topics and put them in the result argument of the service
* \param req
* \param res
* \return true
* get the desired positions by the topics and put them in the result argument of the service
*/
bool lastTarget(assignment_2_2023::LastTarget::Request &req, assignment_2_2023::LastTarget::Response &res)
{
	//actionlib::SimpleActionClient<assignment_2_2023::PlanningAction> ac("/reaching_goal", true);
	
	//get the desired positions by the topics and put them in the result argument of the service
	ros::param::get("/des_pos_x", res.target_pose.pose.position.x);  
	ros::param::get("/des_pos_y", res.target_pose.pose.position.y);
	ROS_INFO("return x:%f y:%f",res.target_pose.pose.position.x , res.target_pose.pose.position.y);

	return true;
}




int main(int argc, char **argv)
{
	ros::init(argc, argv, "lastTarget_");
	ros::NodeHandle n;
	ros::ServiceServer service= n.advertiseService("/lastTarget", lastTarget); //initialize the ServiceServer
	ros::spin();

	return 0;
}
