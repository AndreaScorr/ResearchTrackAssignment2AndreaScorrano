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

