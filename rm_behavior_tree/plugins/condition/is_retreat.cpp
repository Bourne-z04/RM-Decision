#include "condition/is_retreat.hpp"

namespace rm_behavior_tree
{

IsRetreatCondition::IsRetreatCondition(const std::string & name, const BT::NodeConfig & config)
: BT::SimpleConditionNode(name, std::bind(&IsRetreatCondition::checkIsRetreat, this), config)
{
}

BT::NodeStatus IsRetreatCondition::checkIsRetreat()
{
  int hp_threshold_retreat;
  auto msg = getInput<uint16_t>("message");
  getInput("hp_threshold_retreat", hp_threshold_retreat);

  if (!msg) {
    throw BT::RuntimeError("missing required input [ally_7_robot_hp]: ", msg.error());
    return BT::NodeStatus::FAILURE;
  }

  if (msg.value() < hp_threshold_retreat) {
    return BT::NodeStatus::SUCCESS;
  } else {
    return BT::NodeStatus::FAILURE;
  }
}

}  // namespace rm_behavior_tree

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<rm_behavior_tree::IsRetreatCondition>("IsRetreat");
}
