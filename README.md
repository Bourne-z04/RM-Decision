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

##功能实现
实现：
1.靠近占领区转速=5±0.5，否则转速=1±0.5
2.血量低于110发Supply(-0.25,0.0)，否则进入进攻分支
3.进入进攻分支后若无扣血则发Attack(6.0,-3.75)，随机移动move=False；扣血则发Center(5.0,-3.0)，随机移动move=True
4.若发Attack(6.0,-3.75)或发Center(5.0,-3.0)附近点的过程中卡住，重新发新的Center(5.0,-3.0)附近点
