#include "action/send_spin.hpp"

namespace rm_behavior_tree
{

SendSpinAction::SendSpinAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: RosTopicPubNode(name, conf, params)
{
}

bool SendSpinAction::setMessage(interfaces::msg::SpinVelocity & msg)
{
  // 获取输入参数
  float max_velocity = 3.0;   // 默认最大转速
  float frequency = 0.5;     // 默认频率 0.5Hz
  getInput("max_velocity", max_velocity);
  getInput("frequency", frequency);

  // 初始化起始时间
  if (!initialized_) {
    start_time_ = node_->now();
    initialized_ = true;
  }

  // 计算正弦值: sin(2 * PI * frequency * time)
  double elapsed_time = (node_->now() - start_time_).seconds();
  float sine_value = std::sin(2.0 * M_PI * frequency * elapsed_time);

  // 应用最大转速
  msg.chassis_spin_vel = sine_value * max_velocity;

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SendSpinAction, "SendSpin");
