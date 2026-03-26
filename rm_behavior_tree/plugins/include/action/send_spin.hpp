#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_

#include "behaviortree_ros2/bt_topic_pub_node.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include <chrono>

namespace rm_behavior_tree
{

class SendSpinAction : public BT::RosTopicPubNode<std_msgs::msg::Float32>
{
public:
  SendSpinAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params);

  bool setMessage(std_msgs::msg::Float32 & msg) override;

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({
      BT::InputPort<bool>("is_spin"),          // 是否转动
      BT::InputPort<float>("spin_velocity"),   // 转速基准值 (rad/s)
      BT::InputPort<float>("spin_amplitude"),  // 三角波幅值 (rad/s)
      BT::InputPort<float>("spin_period"),     // 三角波周期 (s)
      BT::InputPort<std::string>("topic_name") // topic名称
    });
  }

private:
  bool first_spin_tick_;                           // 首次开启spin标记
  std::chrono::steady_clock::time_point spin_start_time_; // spin开启时间戳
  float current_base_velocity_;                   
  std::chrono::steady_clock::time_point last_shift_time_;
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_
