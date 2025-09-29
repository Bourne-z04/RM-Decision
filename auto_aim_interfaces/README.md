# auto_aim_interfaces

基于26AutoAim自瞄模块设计的ROS2接口包，用于rm_behavior_tree决策模块与自瞄模块的通信。

## 设计思路

本接口包的设计参考了两个源码：

1. **PB_RM_Vision的auto_aim_interfaces**: 作为参考框架，了解rm_behavior_tree中现有的接口使用方式
2. **26AutoAim**: 作为目标自瞄模块，分析其数据结构和通信需求

## 消息类型说明

### 核心消息

#### `Armor.msg`
单个装甲板信息，包含：
- **识别信息**: 装甲板编号、类型、机器人类型
- **2D信息**: 图像坐标系中的中心点和四个角点
- **3D信息**: 相机坐标系中的位姿、距离
- **置信度**: 检测置信度

设计基于26AutoAim中的`Armor`类，扩展了PB_RM_Vision接口的字段。

#### `Armors.msg`
装甲板数组，用于批量传输检测结果。

#### `Target.msg`
目标跟踪信息，包含：
- **跟踪状态**: 是否正在跟踪、目标ID、装甲板数量
- **运动信息**: 位置、速度、加速度
- **旋转信息**: 偏航角及其角速度、角加速度  
- **几何信息**: 目标尺寸参数
- **预测时间**: 预测有效时间

设计参考26AutoAim的跟踪系统和卡尔曼滤波器输出。

#### `GimbalCmd.msg`
云台控制指令，包含：
- **目标姿态**: 偏航、俯仰、深度
- **控制模式**: 位置控制/速度控制
- **射击指令**: 开火命令和模式
- **安全控制**: 复位和急停

设计基于26AutoAim中的`Target_Position_t`和`Gimbal_Position_t`结构。

### 调试消息

#### `TrackerInfo.msg`
跟踪器调试信息，用于监控跟踪性能和状态。

#### `DebugArmor.msg` / `DebugArmors.msg`
检测器调试信息，用于开发和性能分析。

## 与26AutoAim的对应关系

| 26AutoAim结构 | 对应接口消息 | 说明 |
|---------------|-------------|------|
| `Armor`类 | `Armor.msg` | 装甲板检测结果 |
| `Target_Position_t` | `GimbalCmd.msg` | 云台目标姿态 |
| `Gimbal_Position_t` | `GimbalCmd.msg` | 云台当前状态(可扩展) |
| 卡尔曼滤波器输出 | `Target.msg` | 目标跟踪结果 |
| 检测器输出 | `Armors.msg` | 批量装甲板检测 |

## 与rm_behavior_tree的集成

rm_behavior_tree已包含对`auto_aim_interfaces`的依赖，现有的节点如：
- `SubArmorsAction`: 订阅`/detector/armors`话题
- `IsDetectEnemy`: 检查是否检测到敌方装甲板

本接口包可直接替换原有的auto_aim_interfaces，保持API兼容性的同时扩展功能。

## 使用示例

### 发布装甲板检测结果
```cpp
auto armors_msg = auto_aim_interfaces::msg::Armors();
armors_msg.header.stamp = this->get_clock()->now();
armors_msg.header.frame_id = "camera_optical_frame";

// 添加检测到的装甲板
for (const auto& armor : detected_armors) {
    auto armor_msg = auto_aim_interfaces::msg::Armor();
    armor_msg.number = std::to_string(armor.ID);
    armor_msg.type = (armor.armorType == LARGE) ? "large" : "small";
    armor_msg.robot_type = armor.robotType;
    // ... 填充其他字段
    armors_msg.armors.push_back(armor_msg);
}

armors_publisher_->publish(armors_msg);
```

### 发布云台控制指令
```cpp
auto gimbal_cmd = auto_aim_interfaces::msg::GimbalCmd();
gimbal_cmd.header.stamp = this->get_clock()->now();
gimbal_cmd.yaw = target_yaw;
gimbal_cmd.pitch = target_pitch;
gimbal_cmd.mode = auto_aim_interfaces::msg::GimbalCmd::POSITION_MODE;
gimbal_cmd.fire = should_fire;

gimbal_publisher_->publish(gimbal_cmd);
```

## 编译和使用

```bash
# 编译接口包
colcon build --packages-select auto_aim_interfaces

# 源环境
source install/setup.bash

# 查看消息定义
ros2 interface show auto_aim_interfaces/msg/Armor
ros2 interface show auto_aim_interfaces/msg/Target
ros2 interface show auto_aim_interfaces/msg/GimbalCmd
```
