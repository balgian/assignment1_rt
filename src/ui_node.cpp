//
// Created by gian on 12/11/24.
//
#include "ros/ros.h"
#include "turtlesim/Spawn.h"
#include "geometry_msgs/Twist.h"
#include <std_srvs/Empty.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  ros::init(argc, argv, "distance_node");
  ros::NodeHandle nh;
  // Spawn the second turtle
  ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
  turtlesim::Spawn srv;
  srv.request.x = 2.0;
  srv.request.y = 2.0;
  srv.request.theta = 0.0;
  srv.request.name = "turtle2";
  if (client.call(srv)) ROS_INFO("Turtle2 created");
  else { ROS_ERROR("Failed to call service spawn"); return 1;}

  while (ros::ok()) {
    int choice;
    do{
      cout << "Select a robot to control (write 1 or 2):" << endl;
      cout << "1. turtle1" << endl;
      cout << "2. turtle2" << endl;
      cin >> choice;
    } while (choice != 1 && choice != 2);

    char robot = choice == 1 ? '1' : '2';
    string turtle_topic = "/turtle" + string(1, robot) + "/cmd_vel";

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(turtle_topic, 10);
    do{
      cout << "Select a command to send (write 1, 2, 3 or 4):" << endl;
      cout << "1. Forward" << endl;
      cout << "2. Backward" << endl;
      cout << "3. Left" << endl;
      cout << "4. Right" << endl;
      cin >> choice;
    } while (choice < 1 && choice > 4);

    geometry_msgs::Twist my_vel;
    float linear_vel;
    cout << "Choose the linear velocity of the robot." << endl;
    cin >> linear_vel;
    if (choice == 1) {
      my_vel.linear.x = linear_vel;
    }
    if (choice == 2) {
      my_vel.linear.x = -linear_vel;
    }
    if (choice == 3) {
      my_vel.linear.y = linear_vel;
    }
    if (choice == 4) {
      my_vel.linear.y = -linear_vel;
    }
    pub.publish(my_vel);
    //Wait one secodn before to ask again
    sleep(1);
    ros::spinOnce();
    char c;
    cout << "Do you want to continue? (y/n)" << endl;
    cin >> c;
    if (c != 'y' && c != 'Y') {
      break;
    }
  }
  return 0;
}



