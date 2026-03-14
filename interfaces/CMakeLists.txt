cmake_minimum_required(VERSION 3.8)
project(interfaces)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/GameStatus.msg"
  "msg/RobotStatus.msg"
  "msg/SpinVelocity.msg"
  "msg/Position.msg"

  DEPENDENCIES
    std_msgs
    geometry_msgs
    builtin_interfaces
)

ament_package()