#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "std_msgs/String.h"

#define KEYCODE_a 0x61
#define KEYCODE_n 0x6E
#define KEYCODE_e 0x65
#define KEYCODE_c 0x63


int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  (void)sig;
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_key");

  ros::NodeHandle nh;

  ros::Publisher key_pub_ = nh.advertise<std_msgs::String>("keyboard/key", 1);

  signal(SIGINT,quit);

  char c;
  bool dirty=false;

  // get the console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("- Digitando 'a' verrà stampato tutto il messaggio");
  puts("- 'n' mostrerà solo il nome");
  puts("- 'e' mostrerà solo l'eta'");
  puts("- 'c' mostrerà solo il corso di laurea");

  for(;;)
  {
    // get the next event from the keyboard
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }
    std::stringstream ss;

    ROS_DEBUG("value: 0x%02X\n", c);

    switch(c)
    {
      case KEYCODE_a:
        ROS_DEBUG("a");
        dirty = true;
        ss << "a";
        break;
      case KEYCODE_n:
        ROS_DEBUG("n");
        dirty = true;
        ss << "n";
        break;
      case KEYCODE_e:
        ROS_DEBUG("e");
        dirty = true;
        ss << "e";
        break;
      case KEYCODE_c:
        ROS_DEBUG("c");
        dirty = true;
        ss << "c";
        break;
    }

    std_msgs::String msg;
    msg.data = ss.str();
    if(dirty ==true)
    {
      key_pub_.publish(msg);
      dirty=false;
    }
  }

  return 0;
}
