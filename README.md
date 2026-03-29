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

1.高转速=4.5±0.5，低转速=0，转速变换时平滑

2.血量低于110发Supply(-0.25,0.0)，撤退后必须回血到400重新进入进攻分支

3.进入进攻分支后，发Attack(6.0,-3.75)

4.发Attack返回失败，发Center(5.0,-3.0)，随机移动move=True，边长length=1

5.在Center附近2.0m以内，发高转速，否则发低转速

6.扣血判定：若扣血，接下来10秒内返回成功。若扣血判定成功，发Center(5.0,-3.0)，随机移动move=True，边长length=1
