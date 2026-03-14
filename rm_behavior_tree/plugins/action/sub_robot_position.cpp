#include "action/sub_robot_position.hpp"

namespace rm_behavior_tree
{

SubRobotPositionAction::SubRobotPositionAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: BT::RosTopicSubNode<nav_msgs::msg::Odometry>(name, conf, params)
{
}

BT::NodeStatus SubRobotPositionAction::onTick(
  const std::shared_ptr<nav_msgs::msg::Odometry> & last_msg)
{
  if (last_msg)
  {
    RCLCPP_DEBUG(
      logger(), "[%s] new message, position: (%.3f, %.3f, %.3f)", name().c_str(),
      last_msg->pose.pose.position.x,
      last_msg->pose.pose.position.y,
      last_msg->pose.pose.position.z);

    // Extract position xyz from odometry message
    interfaces::msg::Position position;
    position.x = last_msg->pose.pose.position.x;
    position.y = last_msg->pose.pose.position.y;
    position.z = last_msg->pose.pose.position.z;

    setOutput("position", position);
  }
  std::cout << "position: " << position.x << ", " << position.y << ", " << position.z << std::endl;

  return BT::NodeStatus::SUCCESS;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SubRobotPositionAction, "SubRobotPosition");
