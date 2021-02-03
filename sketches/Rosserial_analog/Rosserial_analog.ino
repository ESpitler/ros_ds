/*
 * rosserial Analog Twist Node
 * Reads inputs from analog joystick and outputs 
 * geometry_msgs/twist messages
 * Author: Evan Spitler
 * Email: info@improviseddynamics.com
 * based on code from the rosserial_arduino Hello World example
 * and turtlebot3_teleop_key node
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
ros::NodeHandle  nh;

//std_msgs::String str_msg;
geometry_msgs::Twist base_cmd;
ros::Publisher cmd_vel("/cmd_vel", &base_cmd);



int const LBUT = 4; // left button on pin 4
int const RBUT = 5; // right button on pin 5
int const LY = 0; // Left y-axis on analog 0
int const LX = 1; // left x-axis on analog 1
int const RY = 2; // right y-axis on analog 2
int const RX = 3; // right x-axis on analog 3

float LxState = 0.0; //set state variables for the above pins
float LyState = 0.0;
float RxState = 0.0;
float RyState = 0.0;
int leftState = 0;
int rightState = 0;

float mapFloat(float valIn, float in_min, float in_max, float out_min, float out_max)
{
 return (valIn - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
  nh.initNode();
  nh.advertise(cmd_vel);
  geometry_msgs::Twist base_cmd;
  base_cmd.linear.x = 0.0;
  base_cmd.linear.y = 0.0;
  base_cmd.linear.z = 0.0;
  base_cmd.angular.x = 0.0;
  base_cmd.angular.y = 0.0;
  base_cmd.angular.z = 0.0;

  pinMode(LBUT, INPUT); // establish right and left buttons as digital inputs
  pinMode(RBUT, INPUT); // (not required for analog pins)
}

void loop()
{
  LxState = analogRead(LX); // read each analog/digital input and store
  LyState = analogRead(LY); // the state of each
  RxState = analogRead(RX);
  RyState = analogRead(RY);
  leftState = digitalRead(LBUT);
  rightState = digitalRead(RBUT);

  base_cmd.linear.x = mapFloat(RxState, 0, 1023, -0.22, 0.22);
  base_cmd.angular.z = mapFloat(RyState, 1023, 0, -2.84, 2.84);
    
//  str_msg.data = base_cmd;
  cmd_vel.publish(&base_cmd);
  nh.spinOnce();
  delay(1000);
}
//rostopic pub -1 /turle1/cmd_vel geometry_msgs Twist -- '[0.0, 0.0, 0.0]' '[0.0, 0.0, 0.0]'
