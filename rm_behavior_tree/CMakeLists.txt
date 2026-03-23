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
    nav_msgs
    geometry_msgs
    tf2_ros
    behaviortree_cpp
    behaviortree_ros2
)

# 定义宏函数 add_target_dependencies
function(add_target_dependencies target)
    target_include_directories(${target} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/plugins/include>)
    ament_target_dependencies(${target} ${THIS_PACKAGE_INCLUDE_DEPENDS})
    target_compile_definitions(${target} PRIVATE BT_PLUGIN_EXPORT)
endfunction()

ament_auto_add_executable(rm_behavior_tree
    src/rm_behavior_tree.cpp
)

# Actions
ament_auto_add_library(send_goal SHARED
    plugins/action/send_goal.cpp
)
add_target_dependencies(send_goal)

ament_auto_add_library(sub_game_status SHARED
    plugins/action/sub_game_status.cpp
)
add_target_dependencies(sub_game_status)

ament_auto_add_library(sub_robot_status SHARED
    plugins/action/sub_robot_status.cpp
)
add_target_dependencies(sub_robot_status)

ament_auto_add_library(sub_deduction_reason SHARED
    plugins/action/sub_deduction_reason.cpp
)
add_target_dependencies(sub_deduction_reason)

ament_auto_add_library(send_spin SHARED
    plugins/action/send_spin.cpp
)
add_target_dependencies(send_spin)

ament_auto_add_library(get_current_location SHARED
    plugins/action/get_current_location.cpp
)
add_target_dependencies(get_current_location)

# Decorators
ament_auto_add_library(rate_controller SHARED
    plugins/decorator/rate_controller.cpp
)
add_target_dependencies(rate_controller)

# Conditions
ament_auto_add_library(is_game_time SHARED
    plugins/condition/is_game_time.cpp
)
add_target_dependencies(is_game_time)

ament_auto_add_library(is_retreat SHARED
    plugins/condition/is_retreat.cpp
)
add_target_dependencies(is_retreat)

ament_auto_add_library(is_near_goal SHARED
    plugins/condition/is_near_goal.cpp
)
add_target_dependencies(is_near_goal)


ament_auto_package(
  INSTALL_TO_SHARE
    launch
    config
)
