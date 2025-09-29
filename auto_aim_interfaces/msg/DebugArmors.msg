# Debug information for armor detection batch
# Array of debug armor information

std_msgs/Header header
DebugArmor[] debug_armors

# Overall detection statistics
int32 total_detections               # Total number of detections before filtering
int32 valid_detections               # Number of valid detections after filtering
float32 total_detection_time         # Total time for detection pipeline (ms)
float32 fps                          # Current detection FPS

# System status
uint8 detector_status                # Detector status code
string detector_info                 # Detector status information
