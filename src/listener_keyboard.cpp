#include <ros/ros.h>
#include <signal.h>
#include <stdio.h>
#include "std_msgs/String.h"
#include <sstream>

int fd = 0;

void quit(int sig)
{
  (void)sig;
  ros::shutdown();
  exit(0);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_key");

  ros::NodeHandle n;

  ros::Publisher key_pub = n.advertise<std_msgs::String>("keyboard/key", 1);

  signal(SIGINT,quit);

  char c;

  puts("Reading from keyboard");
  puts("-------------------------------------------------");
  puts("- Digitando 'a' verrà stampato tutto il messaggio");
  puts("- 'n' mostrerà solo il nome");
  puts("- 'e' mostrerà solo l'eta'");
  puts("- 'c' mostrerà solo il corso di laurea");
  puts("------------------------------------------------");

  std_msgs::String msg;

  while(ros::ok()){

  if(read(fd, &c, 1) < 0)
  {
    perror("read():");
    exit(-1);
  }
  if(c == 'a' || c == 'e' || c == 'n' || c == 'c')
    {
      std::stringstream ss;
      ss << c;
      msg.data = ss.str();
      key_pub.publish(msg);
    }
  }
  return 0;
}
