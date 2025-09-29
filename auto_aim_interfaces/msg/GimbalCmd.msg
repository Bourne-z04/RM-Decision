# Gimbal control command
# Based on 26AutoAim Target_Position_t and Gimbal_Position_t structures

std_msgs/Header header

# Target gimbal pose
float32 yaw                          # Target yaw angle (radians)
float32 pitch                        # Target pitch angle (radians) 
float32 depth                        # Target depth/distance (optional)

# Control mode
uint8 POSITION_MODE = 0              # Position control mode
uint8 VELOCITY_MODE = 1              # Velocity control mode
uint8 mode

# Fire command
bool fire                            # Fire command
uint8 fire_mode                      # Fire mode (single shot, burst, etc.)

# Additional control flags
bool reset                           # Reset gimbal to initial position
bool emergency_stop                  # Emergency stop
