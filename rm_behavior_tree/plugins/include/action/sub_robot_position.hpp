#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SUB_ROBOT_POSITION_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SUB_ROBOT_POSITION_HPP_

#include "behaviortree_ros2/bt_topic_sub_node.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "interfaces/msg/position.hpp"

namespace rm_behavior_tree
{
class SubRobotPositionAction : public BT::RosTopicSubNode<nav_msgs::msg::Odometry>
{
public:
  SubRobotPositionAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params);

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("topic_name"),
      BT::OutputPort<interfaces::msg::Position>("position")};
  }

  BT::NodeStatus onTick(
    const std::shared_ptr<nav_msgs::msg::Odometry> & last_msg) override;
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SUB_ROBOT_POSITION_HPP_
