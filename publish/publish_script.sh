#!/bin/bash

source ../install/setup.bash

ros2 topic pub -r 10 /robot_status sys_interfaces/msg/RobotStatus "{
    ally_7_robot_hp: 300,
}" &

ros2 topic pub -r 1 /game_status sys_interfaces/msg/GameStatus "{
    game_progress: 4, # 4:比赛开始 3:比赛结束 2:中场休息 1:暂停 0:准备
    stage_remain_time: 299,
}" &

wait