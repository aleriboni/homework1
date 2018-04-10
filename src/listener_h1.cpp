#include "ros/ros.h"
#include "std_msgs/String.h"
#include "homework1/persona.h"
#include "string.h"


/**
  * In this code a node n subscribes on "/key_selected" topic to filter the
  * message published by "/chatter" topic
  */
std::string temp;


/**
  * This callback saves the message published on the "/key_selected" topic
  * in temp
  */
void keyCallback(const std_msgs::String ::ConstPtr& msg)
{
  temp = msg->data.c_str();
}

/**
  * This callback compares string temp with a, n, e and c to filter the
  * message and prints the filtered mesage
  */
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
  ros::init(argc, argv, "listener_h1");

  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.
   */
  ros::Subscriber sub = n.subscribe("/key_selected", 1000, keyCallback);
  ros::Subscriber sub2 = n.subscribe("/chatter", 1000, chatterCallback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.
   */
  ros::spin();

  return 0;
}
