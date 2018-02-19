# hw1 - CPSC481

Tested and ran on Ubuntu 16.04 in a terminal

# How to build
Install Kinetic distro of ROS.
Instructions found here: http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment

1. Building the project
```
mkdir -p catkin_ws/src
cd catkin_ws
catkin_make
source devel/setup.bash
```

2. Move the hw1 package folder to catkin_ws/src:

3. In catkin folder enter this command to update the changes:

```
catkin_make
```

# Running the nodes

Open 4 terminals

In each terminal cd to the 'catkin' folder and run this command:
```
source devel/setup.bash
```

In terminal 1: Run the master node
```
roscore
```

In terminal 2: Run the sender node
```
rosrun hw1 sender
```

In terminal 3: Run the receiver node
```
rosrun hw1 receiver
```

The two nodes communicate through two topics: 'topic_one' and 'topic_two'

In terminal 2: input 5 numbers separated by spaces (0-100 range)
```
Enter 5 values separated by space('exit' to quit): 1 2 3 4 5
[ INFO] [1519074084.116582431]: I heard: [# of even: 2 and # of odd: 3]
```

In terminal 3: We can see it count the odd/evens
```
1->odd number
2->even number
3->odd number
4->even number
5->odd number
```

In terminal 2: 'exit' to quit
```
Enter 5 values separated by space('exit' to quit): exit
exiting
```

In terminal 4: Run the Hello node
```
rosrun hw1 hello
Hello, ROS! This is my first robot program.
```
