#include "ros/ros.h"
#include "std_msgs/String.h"
#include "homework1/persona.h"
#include "string.h"

std::string temp;

void keyCallback(const std_msgs::String ::ConstPtr& msg)
{
  temp = msg->data.c_str();
}

void chatterCallback(const homework1::persona& msg)
{

  if(temp.compare("a") == 0)
    ROS_INFO("I heard: [%s, %i, %s]", msg.nome.c_str(), msg.age, msg.corso.c_str());
  else if(temp.compare("n") == 0)
    ROS_INFO("I heard: [%s]", msg.nome.c_str());
  else if(temp.compare("e") == 0)
    ROS_INFO("I heard: [%i]", msg.age);
  else if(temp.compare("c") == 0)
    ROS_INFO("I heard: [%s]", msg.corso.c_str());

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("keyboard/key", 1000, keyCallback);
  ros::Subscriber sub2 = n.subscribe("/chatter", 1000, chatterCallback);

  ros::spin();

  return 0;
}
