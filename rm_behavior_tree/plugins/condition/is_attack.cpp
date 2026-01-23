#include "condition/is_attack.hpp"

namespace rm_behavior_tree
{

IsAttackCondition::IsAttackCondition(const std::string & name, const BT::NodeConfig & config)
: BT::SimpleConditionNode(name, std::bind(&IsAttackCondition::checkIsAttack, this), config)
{
}

BT::NodeStatus IsAttackCondition::checkIsAttack()
{
  int hp_threshold_attack;
  auto msg = getInput<sys_interfaces::msg::RobotStatus>("message");
  getInput("hp_threshold_attack", hp_threshold_attack);

  if (!msg) {
    throw BT::RuntimeError("missing required input [robot_status]: ", msg.error());
    std::cout << "missing required input [robot_status]" << '\n';
    return BT::NodeStatus::FAILURE;
  }

  if (msg->ally_7_robot_hp >= hp_threshold_attack) {
    std::cout << "血量充足，可以进攻" << '\n';
    return BT::NodeStatus::SUCCESS;
  } else {
    return BT::NodeStatus::FAILURE;
  }
}

}  // namespace rm_behavior_tree

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<rm_behavior_tree::IsAttackCondition>("IsAttack");
}
