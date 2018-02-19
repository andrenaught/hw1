#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

//Globals
ros::Publisher topic_pub;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	std::string numbers = msg->data.c_str();
	
	std::stringstream stream(numbers);
	std::string temp_string;
	int value;
	int odds = 0;
	int evens = 0;

	while (std::getline(stream, temp_string, ' '))
	{
		value = std::atoi(temp_string.c_str());
		if (value % 2 == 0)
		{
			std::cout << value << "->even number" << std::endl;
			evens++;
		}
		else
		{
			std::cout << value << "->odd number" << std::endl;
			odds++;
		}
	}

	//pack the message and send it to 'topic_two' topic
	std::stringstream string_message;
	std_msgs::String message;

	string_message << "# of even: " << evens << " and # of odd: " << odds;
	message.data = string_message.str();

	topic_pub.publish(message);
}

int main(int argc, char ** argv)
{
	//needed to use ROS stuff
	ros::init(argc, argv, "receiver");

	//our node!
	ros::NodeHandle receiver_node;

	//Tells master node "I want to listen to 'chatter' topic"
	//messages are passed to the callback function (3rd param)
	ros::Subscriber topic_sub = receiver_node.subscribe("topic_one", 1000, chatterCallback);

	//This is for sending back to 'sender' node
	topic_pub = receiver_node.advertise<std_msgs::String>("topic_two", 1000);

	//extra necessary stuff
	ros::spin();

	return 0;
}