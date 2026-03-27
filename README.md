# RM Behavior Tree

基于 BehaviorTree.CPP 实现的决策树，用于 RM（RoboMaster）哨兵的自主决策。

## 环境要求

- **操作系统**: Ubuntu 22.04 (Jammy Jellyfish)
- **ROS2 版本**: Humble Hawksbill
- **GCC 版本**: 11 或更高（支持 C++17）

## 编译

colcon build --symlink-install

## 启动

### 模拟裁判系统

chmod +x publish.sh
./publish.sh

### 决策

chmod +x run.sh
./run.sh

### 杀死进程
lsof -i :1667
kill -9 

## 功能实现

1.高转速=4.5±0.5，低转速=1±0.5，转速变换时平滑

2.血量低于110发Supply(-0.25,0.0)，撤退后必须回血到400重新进入进攻分支

3.进入进攻分支后若无扣血则发Attack(6.0,-3.75)，随机移动move=False；扣血，若血量>200则发Center(5.0,-3.0)，随机移动move=True，边长length=1，若血量<=200则发Backline(5.0,-5.0)，随机移动move=True，边长length=1

4.若发Attack(6.0,-3.75)或发Center(5.0,-3.0)附近点的返回结果失败，重新发新的Center(5.0,-3.0)附近点；若发Backline(5.0,-5.0)附近点的返回结果失败，重新发新的Backline(5.0,-5.0)附近点
