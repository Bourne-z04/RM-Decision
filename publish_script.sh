#!/bin/bash

source install/setup.sh

# Publish robot status - RMUL sentry robot
ros2 topic pub -r 10 /robot_status sys_interfaces/msg/RobotStatus "{
    robot_id: 7,
    current_hp: 400,
    shooter_heat: 0,
    team_color: 0,
    is_attacked: 0
}" &

# Publish game status
ros2 topic pub -r 1 /game_status sys_interfaces/msg/GameStatus "{
    game_progress: 4, # 4:比赛开始
    stage_remain_time: 220
}" &

# Publish all robot HP - simplified for RMUL (3v3)
ros2 topic pub -r 3 /robot_hp sys_interfaces/msg/AllRobotHP "{
    red_1_robot_hp: 0,    # Hero - not present in RMUL
    red_2_robot_hp: 0,    # Engineer - not present in RMUL
    red_3_robot_hp: 100,  # Infantry 3
    red_4_robot_hp: 100,  # Infantry 4
    red_5_robot_hp: 100,  # Infantry 5
    red_7_robot_hp: 200,  # Sentry (our robot)
    red_outpost_hp: 0,    # Outpost - not present in RMUL
    red_base_hp: 0,       # Base - not present in RMUL
    blue_1_robot_hp: 0,   # Hero - not present in RMUL
    blue_2_robot_hp: 0,   # Engineer - not present in RMUL
    blue_3_robot_hp: 100, # Infantry 3
    blue_4_robot_hp: 100, # Infantry 4
    blue_5_robot_hp: 100, # Infantry 5
    blue_7_robot_hp: 200, # Sentry (enemy)
    blue_outpost_hp: 0,   # Outpost - not present in RMUL
    blue_base_hp: 0       # Base - not present in RMUL
}" &

# Publish armor detection data (empty for now - no enemies detected)
ros2 topic pub -r 5 /detector/armors auto_aim_interfaces/msg/Armors "{
  header: {
    stamp: {sec: 0, nanosec: 0},
    frame_id: 'my_frame'
  }
  # armors: []  # Empty array - no armors detected
}" &

wait
