#include "action/send_spin.hpp"
#include "std_msgs/msg/float32.hpp"
#include <cmath>

namespace rm_behavior_tree
{

SendSpinAction::SendSpinAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: RosTopicPubNode(name, conf, params),
  first_spin_tick_(true)
{
}

bool SendSpinAction::setMessage(std_msgs::msg::Float32 & msg)
{
  bool is_spin = false;
  float spin_velocity = 5.5f;  // 转速基准值 (rad/s)
  float spin_amplitude = 0.5f;  // 三角波幅值 (rad/s)
  float spin_period = 5.0f;    // 三角波周期 (s)

  getInput("is_spin", is_spin);
  getInput("spin_velocity", spin_velocity);
  getInput("spin_amplitude", spin_amplitude);
  getInput("spin_period", spin_period);

  if (is_spin) {
    // 首次开启spin时，记录起始时间戳
    if (first_spin_tick_) {
      spin_start_time_ = std::chrono::steady_clock::now();
      first_spin_tick_ = false;
    }

    // 计算从spin开启起经过的时间
    auto now = std::chrono::steady_clock::now();
    float elapsed = std::chrono::duration<float>(now - spin_start_time_).count();

    // 三角波：在 [base-amp, base+amp] 范围内周期性变化
    // phase ∈ [0,1): 0→1 上升，1→0 下降，周期=period
    float phase = std::fmod(elapsed, spin_period) / spin_period;
    float triangular_value;
    if (phase < 0.5f) {
      triangular_value = phase * 2.0f;         // 0→1 线性上升
    } else {
      triangular_value = 2.0f - phase * 2.0f;   // 1→0 线性下降
    }

    // velocity ∈ [base-amp, base+amp]，周期性地三角波动
    msg.data = (spin_velocity - spin_amplitude) + triangular_value * 2.0f * spin_amplitude;
  } else {
    first_spin_tick_ = true;
    msg.data = 0.0f;
  }

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SendSpinAction, "SendSpin");
