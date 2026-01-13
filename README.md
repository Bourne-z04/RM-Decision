# rm_behavior_tree

基于 BehaviorTree.CPP 的 Robomaster 哨兵决策树，与导航模块基于 ROS2 action 进行信息传递，可在仿真环境中进行决策预设开发，并部署到实体机器人上运行。

**当前版本说明**：行为树已简化，只保留导航相关的核心功能，移除了云台控制、底盘旋转、敌人检测和躲避移动等功能。

## 文件结构

- BehaviorTree.ROS2

    forcked from [BehaviorTree/BehaviorTree.ROS2](https://github.com/BehaviorTree/BehaviorTree.ROS2), provides a standard way to implement:

  - Action clients
  - Service Clients
  - Topic Subscribers
  - Topic Publishers

- rm_behavior_tree

    Robomaster 哨兵决策树部分

- rm_decision_interfaces

    对接裁判系统的自定义 ROS 消息类型

## 环境配置

当前开发环境为 Ubuntu22.04, ROS2 humble, BehaviorTree.CPP 4.5

1. 安装依赖

    ```sh
    sudo apt-get update && sudo apt-get install -y ros-humble-behaviortree-cpp ros-humble-nav2-msgs
    ```

2. 克隆仓库

    ```sh
    git clone https://gitee.com/SMBU-POLARBEAR/rm_behavior_tree.git
    cd rm_behavior_tree
    ```

3. 编译

    ```sh
    colcon build --symlink-install --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    ```

## 使用方法

1. 启动行为树

    ```sh
    ros2 launch rm_behavior_tree rm_behavior_tree.launch.py \
    style:=basic \
    use_sim_time:=True
    ```

    `style` 参数与决策树预设文件名一致，详见下文。

2. （可选）开启虚拟裁判系统话题发布（用于测试）

    ```sh
    ./rm_decision_interfaces/publish_script.sh
    ```

## 当前的行为树预设

- `basic`

（1）启动后先订阅并更新黑板。
（2）判断比赛是否进行。若比赛非进行，则持续以 1Hz 发 “Home” 目标。若比赛进行则进入决策主循环。

主循环：
（1）进入进攻分支前置条件：自身状态良好（血量≥200、热量≤150），否则进入撤退分支。
（2）进入进攻分支，下发控制区 OccupyArea 目标
（3）否则转撤退分支，下发补给区 SupplyArea目标。
（4）若自身状态再次满足"血量≥200、热量≤150"，进入进攻分支。

## 使用 Groot 可视化行为树

1. 下载 [Groot Linux installer](https://www.behaviortree.dev/groot)

2. 安装 Groot

    ```sh
    chmod +x Groot2-*-linux-installer.run
    ./Groot2-*-linux-installer.run
    ```

3. 运行 Groot

    ```sh
    cd ~/Groot2/bin
    ./groot2
    ```

4. 在 Groot 中打开 [Project.btproj](./rm_behavior_tree/config/Project.btproj)
