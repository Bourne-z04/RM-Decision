#include "action/send_spin.hpp"
#include "std_msgs/msg/float32.hpp"
#include <cmath>
#include <algorithm>
#include <iomanip>

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
  float target_spin_velocity = 0.0f;

  getInput("is_spin", is_spin);
  getInput("spin_velocity", target_spin_velocity);
  getInput("spin_amplitude", spin_amplitude_);
  getInput("spin_period", spin_period_);

  if (is_spin) {
    auto now = std::chrono::steady_clock::now();

    if (first_spin_tick_) {
      spin_start_time_ = now;
      last_shift_time_ = now;
      first_spin_tick_ = false;
    }

    target_spin_velocity = std::max(0.0f, std::min(5.0f, target_spin_velocity));

    // 目标转速低于阈值时，直接归零并停止调制
    if (target_spin_velocity < 0.1f) {
      msg.data = 0.0f;
      current_base_velocity_ = 0.0f;
      first_spin_tick_ = true;
      return true;
    }

    float elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - last_shift_time_).count();
    if (elapsed_ms >= 50) {  // 每 50ms 平滑一次
      float alpha = 0.05f;  // 平滑系数，越小越平滑
      current_base_velocity_ += alpha * (target_spin_velocity - current_base_velocity_);
      last_shift_time_ = now;
    }

    // 三角波调制
    float elapsed = std::chrono::duration<float>(now - spin_start_time_).count();
    float period = std::max(0.1f, spin_period_);  // 防止除零，最小周期 0.1s
    float phase = std::fmod(elapsed, period) / period;
    float triangular_value;
    if (phase < 0.5f) {
      triangular_value = phase * 2.0f;
    } else {
      triangular_value = 2.0f - phase * 2.0f;
    }
    msg.data = (current_base_velocity_ - spin_amplitude_) + triangular_value * 2.0f * spin_amplitude_;
  } else {
    auto now = std::chrono::steady_clock::now();

    // 平滑减速到 0，不加三角波
    float elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - last_shift_time_).count();
    if (elapsed_ms >= 50) {
      float alpha = 0.05f;
      current_base_velocity_ += alpha * (0.0f - current_base_velocity_);
      last_shift_time_ = now;
    }

    if (current_base_velocity_ < 0.1f) {  // 速度接近0时直接发0，然后停止发布
      msg.data = 0.0f;
      current_base_velocity_ = 0.0f;
      first_spin_tick_ = true;
      return true;
    }

    msg.data = current_base_velocity_;
  }

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SendSpinAction, "SendSpin");