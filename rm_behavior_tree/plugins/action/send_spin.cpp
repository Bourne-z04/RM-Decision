#include "action/send_spin.hpp"
#include "std_msgs/msg/float32.hpp"
#include <cmath>
#include <algorithm>

namespace rm_behavior_tree
{

SendSpinAction::SendSpinAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: RosTopicPubNode(name, conf, params),
  first_spin_tick_(true),
  current_base_velocity_(1.0f)
{
}

bool SendSpinAction::setMessage(std_msgs::msg::Float32 & msg)
{
  bool is_spin = false;
  float target_spin_velocity = 5.5f;  
  float spin_amplitude = 0.5f; 
  float spin_period = 5.0f;   

  getInput("is_spin", is_spin);
  getInput("spin_velocity", target_spin_velocity);
  getInput("spin_amplitude", spin_amplitude);
  getInput("spin_period", spin_period);

  if (is_spin) {
    auto now = std::chrono::steady_clock::now();

    if (first_spin_tick_) {
      spin_start_time_ = now;
      last_shift_time_ = now;      
      first_spin_tick_ = false;
    }

    target_spin_velocity = std::max(1.0f, std::min(5.0f, target_spin_velocity)); 
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shift_time_).count();

    if (elapsed_ms >= 500) {
      float step = 1.0f; // 每次变 1 档
      if (current_base_velocity_ < target_spin_velocity) {
        current_base_velocity_ += step;
        if (current_base_velocity_ > target_spin_velocity) current_base_velocity_ = target_spin_velocity;
        last_shift_time_ = now;
      } else if (current_base_velocity_ > target_spin_velocity) {
        current_base_velocity_ -= step;
        if (current_base_velocity_ < target_spin_velocity) current_base_velocity_ = target_spin_velocity;
        last_shift_time_ = now;
      }
    }

    float elapsed = std::chrono::duration<float>(now - spin_start_time_).count();
    float phase = std::fmod(elapsed, spin_period) / spin_period;
    float triangular_value;
    if (phase < 0.5f) {
      triangular_value = phase * 2.0f;         
    } else {
      triangular_value = 2.0f - phase * 2.0f;  
    }

    msg.data = (current_base_velocity_ - spin_amplitude) + triangular_value * 2.0f * spin_amplitude;
  } else {
    first_spin_tick_ = true;
    current_base_velocity_ = 1.0f; 
    msg.data = 0.0f;
  }

  return true;
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::SendSpinAction, "SendSpin");
