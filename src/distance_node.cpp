//
// Created by gian on 12/11/24.
//
#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

ros::Subscriber sub1_pose, sub1_vel;
ros::Subscriber sub2_pose, sub2_vel;
ros::Publisher pub1_vel;
ros::Publisher pub2_vel;
turtlesim::Pose pose1;
turtlesim::Pose pose2;
geometry_msgs::Twist vel1;
geometry_msgs::Twist vel2;
ros::Publisher distance_pub;

void poseCallback1(const turtlesim::Pose::ConstPtr& msg) {
    pose1 = *msg;
}

void poseCallback2(const turtlesim::Pose::ConstPtr& msg) {
    pose2 = *msg;
}

void velCallback1(const geometry_msgs::Twist::ConstPtr& msg) {
    vel1 = *msg;
}

void velCallback2(const geometry_msgs::Twist::ConstPtr& msg) {
    vel2 = *msg;
}

void controlLoop() {
    geometry_msgs::Twist vel;
    float distance = sqrt(pow(pose1.x - pose2.x, 2) + pow(pose1.y - pose2.y, 2));

    std_msgs::Float32 distance_msg;
    distance_msg.data = distance;
    distance_pub.publish(distance_msg);

    ROS_INFO("Distance between turtles: %f", distance);

    if (distance < 2) {
        vel.linear.x = (vel1.linear.x == 0 ? 0 : vel1.linear.x > 0 ? -2.5 : 2.5);
        vel.linear.y = (vel1.linear.y == 0 ? 0 : vel1.linear.y > 0 ? -2.5 : 2.5);
        pub1_vel.publish(vel);
        vel.linear.x = (vel2.linear.x == 0 ? 0 : vel2.linear.x > 0 ? -2.5 : 2.5);
        vel.linear.y = (vel2.linear.y == 0 ? 0 : vel2.linear.y > 0 ? -2.5 : 2.5);
        pub2_vel.publish(vel);
        sleep(1);
        vel.linear.x = 0;
        vel.linear.y = 0;
        pub1_vel.publish(vel);
        pub2_vel.publish(vel);
    }

    if (pose1.x < 1 || pose1.x > 10 || pose1.y < 1 || pose1.y > 10) {
        vel.linear.x = (vel1.linear.x == 0 ? 0 : vel1.linear.x > 0 ? -2.5 : 2.5);
        vel.linear.y = (vel1.linear.y == 0 ? 0 : vel1.linear.y > 0 ? -2.5 : 2.5);
        pub1_vel.publish(vel);
        sleep(1);
        vel.linear.x = 0;
        vel.linear.y = 0;
        pub1_vel.publish(vel);
    }

    if (pose2.x < 1 || pose2.x > 10 || pose2.y < 1 || pose2.y > 10) {
        vel.linear.x = (vel2.linear.x == 0 ? 0 : vel2.linear.x > 0 ? -2.5 : 2.5);
        vel.linear.y = (vel2.linear.y == 0 ? 0 : vel2.linear.y > 0 ? -2.5 : 2.5);
        pub2_vel.publish(vel);
        sleep(1);
        vel.linear.x = 0;
        vel.linear.y = 0;
        pub2_vel.publish(vel);
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "distance_node");
    ros::NodeHandle nh;

    sub1_pose = nh.subscribe("/turtle1/pose", 10, poseCallback1);
    sub2_pose = nh.subscribe("/turtle2/pose", 10, poseCallback2);
    sub1_vel = nh.subscribe("/turtle1/cmd_vel", 10, velCallback1);
    sub2_vel = nh.subscribe("/turtle2/cmd_vel", 10, velCallback2);
    pub1_vel = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    pub2_vel = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);
    distance_pub = nh.advertise<std_msgs::Float32>("/distance", 10);

    ros::Rate loop_rate(10);

    while (ros::ok()) {
        controlLoop();
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}