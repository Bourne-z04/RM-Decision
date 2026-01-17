#include <rclcpp/rclcpp.hpp>
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/loggers/groot2_publisher.h"
#include "behaviortree_cpp/utils/shared_library.h"
#include "behaviortree_ros2/plugins.hpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);   
    BT::BehaviorTreeFactory factory;    


    std::string bt_xml_path;    // 行为树XML文件路径
    auto node = std::make_shared<rclcpp::Node>("rm_behavior_tree");
    node->declare_parameter<std::string>("style", "./decision/rm_behavior_tree/config/test.xml");
    node->get_parameter_or<std::string>("style", bt_xml_path, "./decision/rm_behavior_tree/config/test.xml");

    // 输出行为树启动信息
    std::cout << "Start RM_Behavior_Tree" << '\n';  
    RCLCPP_INFO(node->get_logger(), "Load bt_xml: \e[1;42m %s \e[0m", bt_xml_path.c_str());

    auto tree = factory.createTreeFromFile(bt_xml_path);    // 创建行为树实例

    // Connect the Groot2Publisher. This will allow Groot2 to get the tree and poll status updates.
    const unsigned port = 1667;
    BT::Groot2Publisher publisher(tree, port); 
    
    // 以10ms周期（100Hz）持续执行行为树，直到ROS关闭
    while (rclcpp::ok()) {
        tree.tickWhileRunning(std::chrono::milliseconds(10));
    }

    rclcpp::shutdown();  
    return 0;   
}