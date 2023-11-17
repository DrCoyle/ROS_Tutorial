#include "ros/ros.h"
#include "std_msgs/String.h"

std_msgs::String msg;
int count = 0;

void callback(const std_msgs::StringConstPtr& str) {
    msg = *str;
    //ROS_INFO("Received message %d, which says %s", count, msg.data.c_str());
    count++;
}

//Simple node that subscribes
int main(int argc, char **argv)
{
    //Initialize Ros (argc & argv used for re-mapping, "listener" is node name)
    ros::init(argc, argv, "listener");

    //Create a node handle, this is used by ROS for communications
    ros::NodeHandle n;

    //When subscibing, designate the type, name, buffer, and callback function
    ros::Subscriber chatter_sub = n.subscribe<std_msgs::String>("chatter", 1000, callback);

    //define a ros rate variable (in Hz)
    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        //print to the terminal what is in the last message
        ROS_INFO("Last recieved message %d, which says %s", count, msg.data.c_str());

        //Process pub/subs in buffers
        ros::spinOnce();

        //force a rate for subscribing (and rest of this loop)
        loop_rate.sleep();
    }
    return 0;
}