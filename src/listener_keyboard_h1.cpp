#include <ros/ros.h>
#include <signal.h>
#include <stdio.h>
#include "std_msgs/String.h"
#include <sstream>
#include <termios.h>


/**
 * This is the file descriptor (0 = keyboard)
 */
int fd = 0;
struct termios cooked, raw;
  /**
   * This function manages the exit with CTRL+C
   */
void quit(int sig)
{
  (void)sig;
  tcsetattr(fd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}

  /*
   * User can select how filtered the message published on "/chatter" topic
   * The character selected is published on "/key_selected" topic
   */
int main(int argc, char** argv)
{
  ros::init(argc, argv, "listener_keyboard_h1");

  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name.
   */
  ros::Publisher key_pub = n.advertise<std_msgs::String>("/key_selected", 1);

  signal(SIGINT,quit);

  char c;

  // get the console in raw mode
  tcgetattr(fd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(fd, TCSANOW, &raw);

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
