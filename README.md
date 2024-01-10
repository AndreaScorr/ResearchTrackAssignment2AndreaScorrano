Research track 1 Second assignment
==================
Andrea Scorrano

id: 6463777

 Create a new package, in which you will develop three nodes:
- (a) A node that implements an action client, allowing the user to set a target (x, y) or to cancel it. Try to use the
feedback/status of the action server to know when the target has been reached. The node also publishesthe
robot position and velocity as a custom message (x,y, vel_x, vel_z), by relying on the values published on the
topic /odom;
- (b) A service node that, when called, returnsthe coordinates of the last target sent by the user;
- (c) Anotherservice node thatsubscribes to the robot’s position and velocity (using the custom message) and
implements a server to retrieve the distance of the robot from the target and the robot’s average speed.

## How to Run the code
In order to start the whole simulation, open three terminal.
To run the simulation of the enviroment, it's needed to write le following line:

```bash
# roslaunch assignment_2_2023 assignment1.launch

```
To run the three nodes, it's needed to write le following line, to run the launch file:

```
# roslaunch assignment_2_2023 AndreaScorrano.launch 
```
To retrieve the distance of the robot from the target and the robot’s average speed, it's needed to call the service with the following line:

```
# rosservice call /VelocityDistance 
```

The last line must be runned every time it's needed to know the distance of the robot from the target and the robot’s average speed. 

## Pseudocode Flow Charts ##

In this assignment were implemented three nodes. The following flow charts show how each node works.

### setTarget Node ###
This node that implements an action client, allow the user to set a target (x, y) or to cancel it. Has been used the feedback/status of the action server to know when the target has been reached. The node also publishes the robot position and velocity as a custom message (x,y, vel_x, vel_z), by relying on the values published on the topic /odom;
```
Initialize pos_x, pos_y, vel_x, vel_z as global variables
Initialize feedback as a string
Initialize g_shutdown_requested as a boolean (false)

Function odomCallback(msg):
    Print position and velocity information from /odom
    Assign position and velocity values to global variables pos_x, pos_y, vel_x, vel_z

Function feedbackCallBack(msg):
    Assign the value of feedback to feedback

Function shutdownHandler(sig):
    Print "Shutting down..."
    Set g_shutdown_requested to true

Main:
    Initialize ROS node ("Planning")
    Create a SimpleActionClient for the action assignment_2_2023::PlanningAction
    Wait for the action server to start
    Initialize a goal of type assignment_2_2023::PlanningGoal

    Prompt the user to enter the x position of the goal
    Prompt the user to enter the y position of the goal
    Print a message indicating to press ctrl-c to cancel the goal
    Wait for 3 seconds to display the message

    Send the goal to the action

    Create subscribers for the "odom" and "/reaching_goal/feedback" topics and a publisher for "robot/parameters"
    Set up a handler for handling shutdown using ctrl-c

    Loop while ROS is active and g_shutdown_requested is false:
        Create a message of type assignment_2_2023::Parameters
        Assign the current values of position and velocity to the variables of the message
        Publish the message

        Get the state of the action
        If the feedback is "Target reached!", exit the loop

        Run the ROS spin loop to handle callbacks

    Cancel the action goal when the loop ends or the target is reached

End the progra
```


