#include "action/get_current_location.hpp"

#include <rclcpp/logging.hpp>

namespace rm_behavior_tree
{

GetCurrentLocationAction::GetCurrentLocationAction(
  const std::string & name, const BT::NodeConfig & config,
  const BT::RosNodeParams & params)
: BT::SyncActionNode(name, config)
{
  // 使用外部传入的 node，确保生命周期正确
  node_ = params.nh.lock();
  if (!node_) {
    throw std::runtime_error("Failed to get node from RosNodeParams");
  }

  auto clock = node_->get_clock();
  tf2::Duration buffer_duration(tf2::durationFromSec(10.0));  // 10 seconds buffer
  tf_buffer_ = std::make_shared<tf2_ros::Buffer>(clock, buffer_duration, node_);
  if (!tf_buffer_) {
    throw std::runtime_error("Failed to create tf2_ros::Buffer");
  }

  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
  if (!tf_listener_) {
    throw std::runtime_error("Failed to create tf2_ros::TransformListener");
  }
}

BT::NodeStatus GetCurrentLocationAction::tick()
{
  geometry_msgs::msg::TransformStamped t;

  try {
    t = tf_buffer_->lookupTransform("map", "base_link", tf2::TimePointZero);
    setOutput("current_location", t);

    RCLCPP_DEBUG(
      node_->get_logger(),
      "Current Location:"
      "\nTranslation:"
      "\nx: %f"
      "\ny: %f"
      "\nz: %f"
      "\nRotation:"
      "\nx: %f"
      "\ny: %f"
      "\nz: %f"
      "\nw: %f",
      t.transform.translation.x, t.transform.translation.y, t.transform.translation.z,
      t.transform.rotation.x, t.transform.rotation.y, t.transform.rotation.z,
      t.transform.rotation.w);

    return BT::NodeStatus::SUCCESS;
  } catch (const tf2::TransformException & ex) {
    RCLCPP_WARN(node_->get_logger(), "Failed to transform base_link to map: %s", ex.what());
    return BT::NodeStatus::FAILURE;
  }
}

}  // namespace rm_behavior_tree

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(rm_behavior_tree::GetCurrentLocationAction, "GetCurrentLocation");
