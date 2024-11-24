# Research Track 1: Assignment 1
	
## Project Overview

This project consists of two ROS nodes: `distance_node` and `ui_node`. These nodes work together to control two turtles in the *turtlesim* simulator.

## Node 1: `distance_node`

The distance_node is responsible for controlling the movement of two turtles in the turtlesim simulator. It uses the `geometry_msgs/Twist` message type to send *velocity commands* to the turtles.

### Key Features

1. Subscribes to the `/turtle1/pose` and `/turtle2/pose` topics to receive the *current position* of the turtles;
2. Subscribes to the `/turtle1/cmd_vel` and `/turtle2/cmd_vel` topics to receive *velocity commands* for the turtles;
3. Publishes *velocity commands* to the `/turtle1/cmd_vel` and `/turtle2/cmd_vel` topics to control the movement of the turtles;
4. Uses the `controlLoop` function to implement a simple control algorithm that keeps the turtles at a safe distance from each other.

## Node 2: `ui_node`

The `ui_node` is responsible for providing a user interface for controlling the turtles. It uses the `std_srvs/Empty` message type to trigger actions in the distance_node.

### Key Features

1. Uses the `ros::ServiceClient` class to spawn a second turtle.

2. Provides a simple text-based interface for the user to select which turtle to control;
3. Publishes *velocity commands* to the `/turtle1/cmd_vel` and `/turtle2/cmd_vel` topics to *control the movement* of the turtles;

## How to Use

1. Run the `distance_node` executable using the `rosrun` command.
2. Run the `ui_node` executable using the `rosrun` command.
3. Use the text-based interface provided by the `ui_node` to select which turtle to control and send velocity commands to the turtles.

## Notes

This project is a starting point for developing a ROS-based application that interacts with the `turtlesim` simulator.
The `distance_node` and `ui_node` executables must be run in separate terminals.
**The `distance_node` executable must be run before the `ui_node` executable.**

## Dependencies:

- ROS (Robot Operating System)
- ROS packages:
  - `roscpp`
  - `turtlesim`
  - `geometry_msgs`
  - `std_srvs`
