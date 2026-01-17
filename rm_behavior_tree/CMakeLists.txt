cmake_minimum_required(VERSION 3.8)
project(rm_behavior_tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies 
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

# Build
set(THIS_PACKAGE_INCLUDE_DEPENDS
    rclcpp
    std_msgs
    behaviortree_cpp
    behaviortree_ros2
)

ament_auto_add_executable(rm_behavior_tree
    src/rm_behavior_tree.cpp
)


ament_auto_package(
  INSTALL_TO_SHARE
    launch
    config
)
