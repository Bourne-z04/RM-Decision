# nav2_msgs

基于 `pb_rm_simulation` 导航模块推测并创建的 ROS2 导航消息包，专为 `rm_behavior_tree` 决策模块设计。

## 包含的消息类型

### Actions (动作)

1. **NavigateToPose.action**
   - 用于导航到指定位姿
   - Goal: `geometry_msgs/PoseStamped pose`
   - Result: `std_msgs/Empty result`
   - Feedback: 包含距离、导航时间、恢复次数和当前位置信息

2. **ComputePathToPose.action**
   - 用于计算到指定位姿的路径
   - Goal: 目标位姿、规划器ID、起始位姿选项
   - Result: 计算得到的路径和规划时间
   - Feedback: 无

3. **FollowPath.action**
   - 用于跟随指定路径
   - Goal: 路径和控制器ID
   - Result: 空结果
   - Feedback: 到目标距离、速度和导航时间

### Messages (消息)

1. **Path.msg**
   - 表示机器人路径的位姿数组
   - 包含头信息和位姿序列

### Services (服务)

1. **GetMap.srv**
   - 获取地图服务
   - Response: `nav_msgs/OccupancyGrid map`

2. **SetInitialPose.srv**
   - 设置机器人初始位姿
   - Request: `geometry_msgs/PoseWithCovarianceStamped pose`
   - Response: `bool success`

## 使用方式

该包已集成到 `rm_behavior_tree` 中，主要在以下节点中使用：

- `SendGoalAction`: 使用 `NavigateToPose` action 发送导航目标
- 其他行为树节点可根据需要使用其他消息类型

## 编译

```bash
cd /root/rm_behavior_tree
colcon build --packages-select nav2_msgs
```

## 依赖

- geometry_msgs
- std_msgs
- builtin_interfaces
- action_msgs
- nav_msgs

## 兼容性

该包基于 `pb_rm_simulation` 导航模块的使用模式设计，与 `rm_behavior_tree` 完全兼容。
