#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_

#include <cmath>

#include "behaviortree_ros2/bt_topic_sub_node.hpp"
#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/spin_velocity.hpp"
#include "interfaces/msg/game_status.hpp"

namespace rm_behavior_tree
{

class SendSpinAction : public BT::RosTopicSubNode<interfaces::msg::SpinVelocity, interfaces::msg::GameStatus>
{
public:
  SendSpinAction(
    const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params);

  bool setMessage(interfaces::msg::SpinVelocity & msg) override;

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<float>("max_velocity"),    // 最大转速 (rad/s)
      BT::InputPort<float>("frequency"),      // 振荡频率 (Hz)
      BT::InputPort<int>("game_progress"),     // 游戏阶段 (4=准备, 5=热身, 6=比赛中, 7=比赛结束)
      BT::InputPort<interfaces::msg::GameStatus>("game_status")  // 游戏状态消息
    };
  }

private:
  rclcpp::Time start_time_;
  bool initialized_ = false;
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SEND_SPIN_HPP_
