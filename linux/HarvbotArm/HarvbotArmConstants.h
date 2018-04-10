#ifndef HarvbotArmConstants_H_
#define HarvbotArmConstants_H_

// Max full rotation
#define HARVBOT_ARM_CLAW_MAX_FULL_ROTATION 28

//								WiringPI			Shifter-sheld      
#define HARVBOT_ARM_SX_STEP         4       //    		16
#define HARVBOT_ARM_SX_DIR          5       // 		    18
#define HARVBOT_ARM_SX_END          6       //    		22
#define HARVBOT_ARM_SX_RATIO        50 * 4

#define HARVBOT_ARM_SY_STEP         11      //   		26
#define HARVBOT_ARM_SY_DIR          26      //    		32
#define HARVBOT_ARM_SY_END          27  	//			36
#define HARVBOT_ARM_SY_RATIO        50 * 4

#define HARVBOT_ARM_SZ_STEP         23		//  		33   
#define HARVBOT_ARM_SZ_DIR          22      //    		31 
#define HARVBOT_ARM_SZ_END          21		//			29
#define HARVBOT_ARM_SZ_RATIO        50 * 4

#define HARVBOT_ARM_SJ_STEP         3       //  		15 
#define HARVBOT_ARM_SJ_DIR          2       //  		13
#define HARVBOT_ARM_SJ_END          30		//			27
#define HARVBOT_ARM_SJ_RATIO        1 * 4

#define HARVBOT_ARM_2_BEDPLATE      170.0
#define HARVBOT_ARM_2_SHOULDER      170.0
#define HARVBOT_ARM_2_ELBOW			120.0

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