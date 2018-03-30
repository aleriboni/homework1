#include "ros/ros.h"
#include "std_msgs/String.h"
#include "homework1/persona.h"
#include <sstream>


int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<homework1::persona>("/chatter", 1000);

  ros::Rate loop_rate(1);

  while (ros::ok())
  {

    homework1::persona msg;

    std::stringstream ss1;
    ss1 << "Alessandro";
    msg.nome = ss1.str();

    std::stringstream ss2;
    ss2 << "Informatica";
    msg.corso = ss2.str();

    msg.age = 21;

    ROS_INFO("nome: %s, eta': %i, corso: %s", msg.nome.c_str(), msg.age, msg.corso.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();

  }


  return 0;
}
