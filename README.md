# RM Behavior Tree

基于 BehaviorTree.CPP 实现的决策树，用于 RM（RoboMaster）哨兵的自主决策。

## 环境要求

- **操作系统**: Ubuntu 22.04 (Jammy Jellyfish)
- **ROS2 版本**: Humble Hawksbill
- **GCC 版本**: 11 或更高（支持 C++17）

## 编译

colcon build 

## 启动

### 模拟裁判系统

cd rm_behavior_tree

chmod +x publish.sh
./publish.sh

### 决策

cd rm_behavior_tree

chmod +x run.sh
./run.sh
