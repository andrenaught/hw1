#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char ** argv)
{
	ros::init(argc, argv, "hello");
	
	std::cout << "Hello, ROS! This is my first robot program." << std::endl;
	
	return 0;
}