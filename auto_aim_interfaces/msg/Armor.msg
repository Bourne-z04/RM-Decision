# Single armor plate information
# Based on 26AutoAim Armor class and PB_RM_Vision interface

# Armor identification
string number              # Armor number (1-7, representing different robot types)
string type               # Armor type: "small" or "large"
uint8 robot_type          # Robot type: 1=HERO, 2=ENGINEER, 3=INFANTRY, 6=FLYING, 7=GUARD

# 2D information
geometry_msgs/Point center            # Armor center in image coordinates (z=0 for 2D)
geometry_msgs/Point[] corners         # Four corner points of armor plate (top-left, top-right, bottom-right, bottom-left, z=0)

# 3D position information
geometry_msgs/Pose pose               # 3D pose of armor in camera frame
float32 distance                      # Distance from camera to armor center
float32 distance_to_image_center      # Distance from armor center to image center

# Tracking information
float32 confidence                    # Detection confidence (0.0-1.0)
