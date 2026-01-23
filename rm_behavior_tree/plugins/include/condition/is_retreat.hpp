#ifndef RM_BEHAVIOR_TREE__PLUGINS__CONDITION__IS_RETREAT_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__CONDITION__IS_RETREAT_HPP_

#include "behaviortree_cpp/condition_node.h"
#include "sys_interfaces/msg/robot_status.hpp"

namespace rm_behavior_tree
{
/**
 * @brief Condition节点，用于判断机器人是否需要撤退
 * 
 * 该节点从输入端口获取机器人状态消息、血量阈值，并根据条件判断机器人是否血量过低需要撤退。
 * 如果机器人血量过低，返回成功；否则返回失败。
 * @param[in] message 机器人状态话题id
 * @param[in] hp_threshold_retreat 撤退血量阈值
 * @return BT::NodeStatus 机器人是否需要撤退
 */
class IsRetreatCondition : public BT::SimpleConditionNode
{
public:
  IsRetreatCondition(const std::string & name, const BT::NodeConfig & config);

  BT::NodeStatus checkIsRetreat();

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<sys_interfaces::msg::RobotStatus>("message"),
      BT::InputPort<int>("hp_threshold_retreat")};
  }
};
}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__CONDITION__IS_RETREAT_TRUE_HPP_