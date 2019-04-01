#include "ros/ros.h"

#include "sensor_msgs/LaserScan.h"

using namespace std;

class ForwardDetect{
private:
	ros::NodeHandle nh_;
	
	ros::Subscriber scan_sub_;
public:
	ForwardDetect();
	~ForwardDetect();
	void lidarCallback(const sensor_msgs::LaserScan::ConstPtr& scan);
};

ForwardDetect::ForwardDetect()
{
	scan_sub_ = nh_.subscribe<sensor_msgs::LaserScan> ("scan", 100, &ForwardDetect::lidarCallback, this);
}

ForwardDetect::~ForwardDetect()
{

}
void ForwardDetect::lidarCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
	double center_dist = scan->ranges[0];
	if (center_dist < 0.15){
		center_dist = 0;
	}
	if (center_dist > 20){
		center_dist = 20;
	}
	cout << "Forward distance: " << center_dist << " m " << endl;

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "forward_detector");

	ForwardDetect ForwardDetect;
	ros::spin();

	return 0;
}

