#ifndef HarvbotArmConstants_H_
#define HarvbotArmConstants_H_

#include <math.h>

// Max full rotation
#define HARVBOT_ARM_CLAW_MAX_FULL_ROTATION 28

//								WiringPI			Shifter-sheld      
#define HARVBOT_ARM_SX_STEP         4       //    		16
#define HARVBOT_ARM_SX_DIR          5       // 		    18
#define HARVBOT_ARM_SX_END          6       //    		22
#define HARVBOT_ARM_SX_RATIO        50 * 32
#define HARVBOT_ARM_SX_FR	        24000
#define HARVBOT_ARM_SX_MAX_STEPS    200

#define HARVBOT_ARM_SY_STEP         11      //   		26
#define HARVBOT_ARM_SY_DIR          0      //    		32
#define HARVBOT_ARM_SY_END          27  	//			36
#define HARVBOT_ARM_SY_RATIO        50 * 32
#define HARVBOT_ARM_SY_FR	        24000
#define HARVBOT_ARM_SY_MAX_STEPS    200

#define HARVBOT_ARM_SZ_STEP         23		//  		33   
#define HARVBOT_ARM_SZ_DIR          22      //    		31 
#define HARVBOT_ARM_SZ_END          21		//			29
#define HARVBOT_ARM_SZ_RATIO        50 * 32
#define HARVBOT_ARM_SZ_FR	        24000
#define HARVBOT_ARM_SZ_MAX_STEPS    200

#define HARVBOT_ARM_SJ_STEP         3       //  		15 
#define HARVBOT_ARM_SJ_DIR          2       //  		13
#define HARVBOT_ARM_SJ_END          26		//			27
#define HARVBOT_ARM_SJ_RATIO        1 * 32
#define HARVBOT_ARM_SJ_FR	        24000
#define HARVBOT_ARM_SJ_MAX_STEPS    200

#define HARVBOT_ARM_2_BEDPLATE      170.0
#define HARVBOT_ARM_2_SHOULDER      125.0
#define HARVBOT_ARM_2_ELBOW			120.0

#define HARVBOT_GREAPER_MIN_CONTOUR_SIZE 60
#define HARVBOT_GREAPER_CENTERING_THRESHOLD 15
#define HARVBOT_GREAPER_MOVE_DELTA_X 0.5
#define HARVBOT_GREAPER_MOVE_DELTA_Y 0.3

#define radians(x) M_PI * (x / 180.0)
#define degrees(x) x * 180.0 / M_PI

#define round4(x) (x * 10000.0) / 10000.0

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