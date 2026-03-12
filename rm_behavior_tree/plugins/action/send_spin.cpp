#include "rm_behavior_tree/plugins/action/send_spin.hpp"

namespace rm_behavior_tree
{

SendSpinAction::SendSpinAction(
  const std::string & name, const BT::NodeConfig & conf, const BT::RosNodeParams & params)
: RosTopicSubNode<interfaces::msg::SpinVelocity, interfaces::msg::GameStatus>(name, conf, params)
{
}

bool SendSpinAction::setMessage(interfaces::msg::SpinVelocity & msg)
{
  // 获取输入参数
  float max_velocity = 3.0;   // 默认最大转速
  float frequency = 0.5;       // 默认频率 0.5Hz
  int game_progress = 6;      // 默认比赛进行中
  getInput("max_velocity", max_velocity);
  getInput("frequency", frequency);
  getInput("game_progress", game_progress);

  // 获取游戏状态消息
  auto game_status_msg = getInput<interfaces::msg::GameStatus>("game_status");

  // 检查游戏是否正在进行 (game_progress == 6 表示比赛进行中)
  bool is_game_running = false;
  if (game_status_msg && game_status_msg->game_progress == game_progress) {
    is_game_running = true;
  }

  if (!is_game_running) {
    // 游戏未开始/已结束，停止小陀螺
    msg.chassis_spin_vel = 0.0;
    // 重置时间，下次开始时从正弦波零点开始
    initialized_ = false;
    return true;
  }

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
