#include "ros/ros.h"
#include "std_msgs/String.h"

//Simple node that publishes
int main(int argc, char **argv)
{
    //Initialize Ros (argc & argv used for re-mapping, "talker" is node name)
    ros::init(argc,argv,"talker");

    //Create a node handle, this is used by ROS for communications
    ros::NodeHandle n;

    //When you publish, designate the type, name, and buffer
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

    //define a ros rate variable (in Hz)
    ros::Rate loop_rate(10);

    int count = 0;
    while(ros::ok())
    {
        //create a message object to fill for publishing
        std_msgs::String msg;
        msg.data = "hello";
        
        //ROS print of what is in the message
        ROS_INFO("Publishing message %d, which is %s", count, msg.data.c_str());

        //publish your message
        chatter_pub.publish(msg);

        //Process subscriber callbacks waiting to happen
        ros::spinOnce();

        //force a rate for publishing (and rest of this loop)
        loop_rate.sleep();

        //increment message number;
        ++count;
    }

    
    return 0;
}