#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_

#include <cmath>

#include "behaviortree_ros2/bt_topic_pub_node.hpp"
#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/spin_velocity.hpp"

namespace rm_behavior_tree
{

class SendSpinAction : public BT::RosTopicPubNode<interfaces::msg::SpinVelocity>
{
public:
  SendSpinAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params);

  bool setMessage(interfaces::msg::SpinVelocity & msg) override;

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({
      BT::InputPort<float>("max_velocity"),    // 最大转速 (rad/s)
      BT::InputPort<float>("frequency")       // 振荡频率 (Hz)
    });
  }

private:
  rclcpp::Time start_time_;
  bool initialized_ = false;
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_
