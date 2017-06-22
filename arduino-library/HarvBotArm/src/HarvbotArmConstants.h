#ifndef HarvbotArmConstants_H_
#define HarvbotArmConstants_H_

#include <Arduino.h>

// Max full rotation
#ifndef HARVBOT_ARM_CLAW_MAX_FULL_ROTATION
#define HARVBOT_ARM_CLAW_MAX_FULL_ROTATION 28
#endif

// Default stepper motor speed
#ifndef HARVBOT_DEFAULT_STEPPER_SPEED
#define HARVBOT_DEFAULT_STEPPER_SPEED 50
#endif

enum HarvbotArmNodeIdentifiers
{
    Undefined = -1,
    Bedplate = 1,
    Shoulder = 2,
    Elbow = 3,
    ElbowScrew = 4,
    Hand = 5,
    HandScrew = 6,
    Claw = 7
};

enum HarvbotArmNodeTypes
{
    Circle = 1,
    Screw = 2
};

enum HarvbotArmTypes
{
    ArmType1 = 1,
    ArmType2 = 2,
    ArmType3 = 3
};

// Node statuses
enum HarvbotNodeStatuses
{
    Ready = 0,
    InProcess = 1
};

enum HarvbotArmProtocolErrorCodes
{
    Uninitialized = 101,
    InvalidArmType = 102,
    InvalidNodeIdentifier = 103,
    InvalidCommand = 104
};

enum HarvbotArmCommands
{
    Invalid,
    Init,
    InitStart,
    Status,
    Move,
    Position,
    Steps,
    Angle,
    Rotate,
    RotateOnAngle,
    Revolution,
    NodeStatus
};

#endif /* HarvbotArmConstants_H_ */