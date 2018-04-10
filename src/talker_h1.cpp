#include "ros/ros.h"
#include "std_msgs/String.h"
#include "homework1/persona.h"
#include <sstream>

/**
  * In this code a node chatter_pub publishes a message Persona on
  * "/chatter" topic
  */
int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker_h1");

  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name.
   */
  ros::Publisher chatter_pub = n.advertise<homework1::persona>("/chatter", 1000);

  /**
    * chatter_pub publishes every second
    */
  ros::Rate loop_rate(1);

  while (ros::ok())
  {
    /**
      * This is a message object.
      * Persona contains three fields: nome, age, corso
      */
    homework1::persona msg;

    std::stringstream ss1;
    ss1 << "Alessandro";
    msg.nome = ss1.str();

    std::stringstream ss2;
    ss2 << "Informatica";
    msg.corso = ss2.str();

    msg.age = 21;

    ROS_INFO("nome: %s, eta': %i, corso: %s", msg.nome.c_str(), msg.age, msg.corso.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object.
     */
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();

  }


  return 0;
}
