#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/loggers/groot2_publisher.h"
#include "behaviortree_cpp/utils/shared_library.h"
#include "behaviortree_ros2/plugins.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  BT::BehaviorTreeFactory factory;

  std::string bt_xml_path;
  auto node = std::make_shared<rclcpp::Node>("rm_behavior_tree");

  // 获取包的共享目录路径
  std::string package_share_directory = ament_index_cpp::get_package_share_directory("rm_behavior_tree");
  std::string default_bt_xml = package_share_directory + "/config/test.xml";

  node->declare_parameter<std::string>("style", default_bt_xml);
  node->get_parameter_or<std::string>("style", bt_xml_path, default_bt_xml);

  std::cout << "Start RM_Behavior_Tree" << '\n';
  RCLCPP_INFO(node->get_logger(), "Load bt_xml: \e[1;42m %s \e[0m", bt_xml_path.c_str());

  // 创建独立的 ROS 节点，确保其生命周期与主程序一致
  auto update_msg_node = std::make_shared<rclcpp::Node>("update_msg");
  BT::RosNodeParams params_update_msg;
  params_update_msg.nh = update_msg_node;

  auto send_goal_node = std::make_shared<rclcpp::Node>("send_goal");
  BT::RosNodeParams params_send_goal;
  params_send_goal.nh = send_goal_node;
  params_send_goal.default_port_value = "goal_pose";

  // 批量注册插件
  const std::vector<std::string> bt_plugin_libs = {
    "rate_controller",
    "is_game_time",
  };

  // 消息更新插件列表
  const std::vector<std::string> msg_update_plugin_libs = {
    "sub_game_status",
  };

  for (const auto & p : bt_plugin_libs) {
    factory.registerFromPlugin(BT::SharedLibrary::getOSName(p));
  }

  // 批量注册消息更新插件节点
  for (const auto & p : msg_update_plugin_libs) {
    RegisterRosNode(factory, BT::SharedLibrary::getOSName(p), params_update_msg);
  }

  // 单独注册 send_goal 节点
  RegisterRosNode(factory, BT::SharedLibrary::getOSName("send_goal"), params_send_goal);

  auto tree = factory.createTreeFromFile(bt_xml_path);

  // Connect the Groot2Publisher. This will allow Groot2 to get the tree and poll status updates.
  const unsigned port = 1667;
  BT::Groot2Publisher publisher(tree, port);

  while (rclcpp::ok()) {
    tree.tickWhileRunning(std::chrono::milliseconds(10));
  }

  rclcpp::shutdown();
  return 0;
}