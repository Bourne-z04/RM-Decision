#include "rm_behavior_tree/plugins/action/select_random_occupy_backup.hpp"

#include <random>
#include <vector>
#include <string>
#include <rclcpp/rclcpp.hpp>

namespace rm_behavior_tree
{

SelectRandomOccupyBackupAction::SelectRandomOccupyBackupAction(
  const std::string & name, const BT::NodeConfig & config)
: BT::SyncActionNode(name, config)
{
}

BT::NodeStatus SelectRandomOccupyBackupAction::tick()
{
  // 定义9个OccupyArea备份点坐标
  std::vector<std::string> backup_points = {
    "4.023;-3.867;0;0;0;0;1",  // 点1
    "4.890;-3.867;0;0;0;0;1",  // 点2
    "5.757;-3.867;0;0;0;0;1",  // 点3
    "4.023;-3.000;0;0;0;0;1",  // 点4
    "5.757;-3.000;0;0;0;0;1",  // 点6 (跳过点5，因为它是原始OccupyArea点)
    "4.023;-2.133;0;0;0;0;1",  // 点7
    "4.890;-2.133;0;0;0;0;1",  // 点8
    "5.757;-2.133;0;0;0;0;1"   // 点9
  };

  // 创建随机数生成器
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, backup_points.size() - 1);

  // 随机选择一个备份点
  int random_index = dis(gen);
  std::string selected_backup = backup_points[random_index];

  // 输出选择的备份点
  setOutput("selected_backup", selected_backup);

  RCLCPP_INFO(rclcpp::get_logger("select_random_occupy_backup"), "Selected random OccupyArea backup point: %s", selected_backup.c_str());

  return BT::NodeStatus::SUCCESS;
}

}  // namespace rm_behavior_tree

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<rm_behavior_tree::SelectRandomOccupyBackupAction>("SelectRandomOccupyBackup");
}
