#ifndef RM_BEHAVIOR_TREE__PLUGINS__CONDITION__IS_ATTACK_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__CONDITION__IS_ATTACK_HPP_

#include "behaviortree_cpp/condition_node.h"
#include "sys_interfaces/msg/robot_status.hpp"

namespace rm_behavior_tree
{
/**
 * @brief Condition节点，用于判断机器人是否可以进攻
 * 
 * 该节点从输入端口获取机器人状态消息、血量阈值，并根据条件判断机器人是否血量充足可以进攻。
 * 如果机器人血量充足，返回成功；否则返回失败。
 * @param[in] message 机器人状态话题id
 * @param[in] hp_threshold_attack 攻击血量阈值
 * @return BT::NodeStatus 机器人是否可以进攻
 */
class IsAttackCondition : public BT::SimpleConditionNode
{
public:
  IsAttackCondition(const std::string & name, const BT::NodeConfig & config);

  BT::NodeStatus checkIsAttack();

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<sys_interfaces::msg::RobotStatus>("message"),
      BT::InputPort<int>("hp_threshold_attack")};
  }
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__CONDITION__IS_ATTACK_HPP_