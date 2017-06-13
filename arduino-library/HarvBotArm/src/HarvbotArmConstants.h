#include <Arduino.h>

// Arm nodes.
#ifndef HARVBOT_ARM_BEDPLATE_NODE
#define HARVBOT_ARM_BEDPLATE_NODE 1
#endif

#ifndef HARVBOT_ARM_SHOULDER_NODE
#define HARVBOT_ARM_SHOULDER_NODE 2
#endif

#ifndef HARVBOT_ARM_ELBOW_NODE
#define HARVBOT_ARM_ELBOW_NODE 3
#endif

#ifndef HARVBOT_ARM_ELBOW_SCREW_NODE
#define HARVBOT_ARM_ELBOW_SCREW_NODE 4
#endif

#ifndef HARVBOT_ARM_HAND_NODE
#define HARVBOT_ARM_HAND_NODE 5
#endif

#ifndef HARVBOT_ARM_HAND_SCREW_NODE
#define HARVBOT_ARM_HAND_SCREW_NODE 6
#endif

#ifndef HARVBOT_ARM_CLAW_NODE
#define HARVBOT_ARM_CLAW_NODE 7
#endif

// Max full rotation
#ifndef HARVBOT_ARM_CLAW_MAX_FULL_ROTATION
#define HARVBOT_ARM_CLAW_MAX_FULL_ROTATION 28
#endif

// Nodes types
#ifndef HARVBOT_ARM_CIRCLE_NODE_TYPE
#define HARVBOT_ARM_CIRCLE_NODE_TYPE 1
#endif

#ifndef HARVBOT_ARM_SCREW_NODE_TYPE
#define HARVBOT_ARM_SCREW_NODE_TYPE 2
#endif

// Arm types
#ifndef HARVBOT_ARM_TYPE_1
#define HARVBOT_ARM_TYPE_1 1
#endif

#ifndef HARVBOT_ARM_TYPE_2
#define HARVBOT_ARM_TYPE_2 2
#endif

#ifndef HARVBOT_ARM_TYPE_3
#define HARVBOT_ARM_TYPE_3 3
#endif

// Default stepper motor speed
#ifndef HARVBOT_DEFAULT_STEPPER_SPEED
#define HARVBOT_DEFAULT_STEPPER_SPEED 50
#endif

// Node statuses
#ifndef HARVBOT_NODE_STATUS_READY
#define HARVBOT_NODE_STATUS_READY 0
#endif

#ifndef HARVBOT_NODE_STATUS_INPROCESS
#define HARVBOT_NODE_STATUS_INPROCESS 1
#endif