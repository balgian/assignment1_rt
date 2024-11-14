//
// Created by gian on 12/11/24.
//
#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>

ros::Subscriber sub1;
ros::Subscriber sub2;
ros::Publisher pub1;
ros::Publisher pub2;
turtlesim::Pose pose1;
turtlesim::Pose pose2;

void poseCallback1(const turtlesim::Pose::ConstPtr& msg) {
    pose1 = *msg;
}

void poseCallback2(const turtlesim::Pose::ConstPtr& msg) {
    pose2 = *msg;
}

void controlLoop() {
    float distance = sqrt(pow(pose1.x - pose2.x, 2) + pow(pose1.y - pose2.y, 2));

    if (distance < 2) {
        geometry_msgs::Twist vel;
        vel.linear.x = 0;
        vel.angular.z = 0;
        pub1.publish(vel);
    }

    if (pose1.x < 1 || pose1.x > 10 || pose1.y < 1 || pose1.y > 10) {
        geometry_msgs::Twist vel;
        vel.linear.x = 0;
        vel.angular.z = 0;
        pub1.publish(vel);
    }

    distance = sqrt(pow(pose2.x - pose1.x, 2) + pow(pose2.y - pose1.y, 2));

    if (distance < 2) {
        geometry_msgs::Twist vel;
        vel.linear.x = 0;
        vel.angular.z = 0;
        pub2.publish(vel);
    }

    if (pose2.x < 1 || pose2.x > 10 || pose2.y < 1 || pose2.y > 10) {
        geometry_msgs::Twist vel;
        vel.linear.x = 0;
        vel.angular.z = 0;
        pub2.publish(vel);
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "distance_node");
    ros::NodeHandle nh;

    sub1 = nh.subscribe("/turtle1/pose", 10, poseCallback1);
    sub2 = nh.subscribe("/turtle2/pose", 10, poseCallback2);
    pub1 = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    pub2 = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);

    ros::Rate loop_rate(1);

    while (ros::ok()) {
        controlLoop();
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}