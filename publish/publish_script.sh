#!/bin/bash

source ../install/setup.bash

ros2 topic pub -r 1 /game_status sys_interfaces/msg/GameStatus "{
    game_progress: 4, # 4:比赛开始
    stage_remain_time: 220,
}" &