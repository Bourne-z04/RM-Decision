# Target information for tracking and prediction
# Based on 26AutoAim tracking system and PB_RM_Vision Target message

std_msgs/Header header

# Tracking status
bool tracking                         # Whether the target is being tracked
string id                            # Target ID
int32 armors_num                     # Number of armors on this target

# Position and motion information
geometry_msgs/Point position         # Target position in world frame
geometry_msgs/Vector3 velocity       # Target velocity
geometry_msgs/Vector3 acceleration   # Target acceleration (if available)

# Rotation information  
float64 yaw                          # Target yaw angle
float64 v_yaw                        # Target yaw angular velocity
float64 a_yaw                        # Target yaw angular acceleration (if available)

# Target geometry (for different robot types)
float64 radius_1                     # Target radius 1
float64 radius_2                     # Target radius 2  
float64 dz                           # Target height offset

# Prediction time
float64 predicted_time               # Time for which this prediction is valid
