# Tracker debugging and status information
# Based on PB_RM_Vision TrackerInfo message

std_msgs/Header header

# Tracking performance metrics
float64 position_diff                # Difference between current measurement and prediction for position
float64 yaw_diff                     # Difference between current measurement and prediction for yaw

# Unfiltered measurements
geometry_msgs/Point position         # Unfiltered position measurement
float64 yaw                          # Unfiltered yaw measurement

# Tracker status
uint8 tracker_state                  # Current state of tracker (DETECTING=1, LOST=2, TRACKING=3, LOSING=4)
int32 lost_frames                    # Number of consecutive frames without detection
float32 tracking_confidence          # Overall tracking confidence (0.0-1.0)
