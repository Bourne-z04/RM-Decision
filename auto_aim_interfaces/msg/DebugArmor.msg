# Debug information for single armor detection
# Extended from basic Armor message with additional debug info

# Basic armor information
Armor armor

# Detection pipeline debug info
float32 detection_time               # Time taken for detection (ms)
float32 classification_confidence    # Confidence of armor classification
float32 pose_estimation_error        # Error in pose estimation

# Image processing debug info
geometry_msgs/Point[] light_bars     # Detected light bar positions (z=0 for 2D)
float32 light_bar_angle             # Angle between light bars
float32 aspect_ratio                # Width to height ratio
float32 area                        # Armor area in pixels

# Additional debug flags
bool is_valid                       # Whether this armor passed validation
string debug_info                   # Additional debug information
