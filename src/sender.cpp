#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

//Globals
bool waiting_for_response = false;

//checks whether input is in range of (0 -> 100)
//have to convert strings to "old school C++ strings" with c_str()
bool input_ok(std::string input_string)
{
	std::stringstream stream(input_string);
	std::string single_num;

	while (std::getline(stream, single_num, ' '))
	{
		if (std::isdigit(single_num[0]))
		{
			if (std::atoi(single_num.c_str()) > 100 || std::atoi(single_num.c_str()) < 0)
			{
				std::cout << "found value is not within range (0 -> 100). try again." << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "found value is not a number. try again." << std::endl;
			return false;
		}
    }

	return true;
}

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	waiting_for_response = false;
}

int main(int argc, char ** argv)
{
	//needed to use ROS stuff
	ros::init(argc, argv, "sender");
	
	//our node!
	ros::NodeHandle sender_node;

	/* This invokes a call on the master node to handle the communication for the topic.
	   Our node wants to publish to a topic!

	   advertise() returns a publisher object that allows the node to publish messages 
	   to the topic. 1st param = topic name, 2nd param = size of the message queue */
	ros::Publisher topic_pub = sender_node.advertise<std_msgs::String>("topic_one", 1000);
	ros::Subscriber topic_sub = sender_node.subscribe("topic_two", 1000, chatterCallback);

	//extra necessary stuff
	ros::Rate loop_rate(10);

	while (ros::ok())
	{
		std::string inputString;
		std_msgs::String inputMessage;
		bool valid_input = false;

		/* Take user input (if awaiting response let 'chatterCallback' run by holding
		   off on user input cause it gets delayed if we don't) */
		if (!waiting_for_response)
		{
			std::cout << "Enter 5 values separated by space('exit' to quit): ";
			std::getline (std::cin, inputString);

			if (inputString == "exit")
			{
				ros::shutdown();
				std::cout << "exiting" << std::endl;
			}
			else
			{
				valid_input = input_ok(inputString);
			}

			//(don't let invalid inputs through)
			if (valid_input)
			{
				inputMessage.data = inputString;
				topic_pub.publish(inputMessage);
				waiting_for_response = true;
			}
		}

		//extra necessary stuff
		ros::spinOnce();
		loop_rate.sleep();
	}

	ros::spin();
	
	return 0;
}