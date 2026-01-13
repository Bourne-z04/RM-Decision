#ifndef RM_BEHAVIOR_TREE__PLUGINS__ACTION__SELECT_RANDOM_OCCUPY_BACKUP_HPP_
#define RM_BEHAVIOR_TREE__PLUGINS__ACTION__SELECT_RANDOM_OCCUPY_BACKUP_HPP_

#include "behaviortree_cpp/bt_factory.h"

namespace rm_behavior_tree
{

class SelectRandomOccupyBackupAction : public BT::SyncActionNode
{
public:
  SelectRandomOccupyBackupAction(
    const std::string & name, const BT::NodeConfig & config);

  static BT::PortsList providedPorts()
  {
    return {
      BT::OutputPort<std::string>("selected_backup")
    };
  }

  BT::NodeStatus tick() override;
};

}  // namespace rm_behavior_tree

#endif  // RM_BEHAVIOR_TREE__PLUGINS__ACTION__SELECT_RANDOM_OCCUPY_BACKUP_HPP_
