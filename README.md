# RM Behavior Tree

基于 BehaviorTree.CPP 实现的决策树，用于 RM（RoboMaster）哨兵的自主决策。

## 环境要求

- **操作系统**: Ubuntu 22.04 (Jammy Jellyfish)
- **ROS2 版本**: Humble Hawksbill
- **GCC 版本**: 11 或更高（支持 C++17）

## 系统依赖安装

### 1. 安装 ROS2 Humble

请参考官方文档: [ROS2 Humble 安装指南](https://docs.ros.org/en/humble/Installation.html)

### 2. 安装系统依赖

```bash
# 更新软件包列表
sudo apt update

# 安装 Navigation2 相关包
sudo apt install ros-humble-navigation2 ros-humble-nav2-msgs

# 安装 BehaviorTree 相关依赖
sudo apt install ros-humble-behaviortree-cpp ros-humble-behaviortree-ros2

### 3. 安装其他必要的 ROS2 包

```bash
# 安装 tf2 相关
sudo apt install ros-humble-tf2 ros-humble-tf2-ros

# 安装 geometry msgs
sudo apt install ros-humble-geometry-msgs
``

### 4. 编译项目

```bash
colcon build
```
