#!/bin/bash

# Source ROS2 workspace
source ../install/setup.bash

# Publish robot status at 3 Hz
ros2 topic pub -r 3 /robot_status interfaces/msg/RobotStatus "{
    ally_7_robot_hp: 300,
}" &

# Publish game status at 1 Hz
ros2 topic pub -r 1 /game_status interfaces/msg/GameStatus "{
    game_progress: 4, # 4:比赛开始 3:比赛结束 2:中场休息 1:暂停 0:准备
    stage_remain_time: 299,
}" &

# Wait for all background processes
wait
