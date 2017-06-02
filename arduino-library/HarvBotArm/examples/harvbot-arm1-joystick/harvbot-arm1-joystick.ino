#include <HarvbotArm.h>
#include <HarvbotArm1.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>

HarvbotArm1* manipulator;
int joyPin11 = 0;                 // slider variable connecetd to analog pin 0
int joyPin12 = 1;                 // slider variable connecetd to analog pin 1
int button1 = 8;
int joyPin21 = 2;                 // slider variable connecetd to analog pin 2
int joyPin22 = 3;                 // slider variable connecetd to analog pin 3
int button2 = 9;

int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;

void setup() 
{
  Serial.begin(9600);
  
  HarvbotArmServoNodePins bedplate;
  bedplate.Pin = 2;
  bedplate.InitialPos = 90;

  HarvbotArmServoNodePins shoulder;
  shoulder.Pin = 3;
  shoulder.InitialPos = 5; 

  HarvbotArmServoNodePins elbow;
  elbow.Pin = 4;
  elbow.InitialPos = 20;

  HarvbotArmServoNodePins elbowScrew;
  elbowScrew.Pin = 5;
  elbowScrew.InitialPos = 90;

  HarvbotArmServoNodePins hand;
  hand.Pin = 6;
  hand.InitialPos = 90;

  HarvbotArmServoNodePins handScrew;
  handScrew.Pin = 7;
  handScrew.InitialPos = 90;
  
  manipulator = new HarvbotArm1(bedplate, shoulder, elbow, elbowScrew, hand, handScrew);
}

void loop() 
{
  // reads the value of the variable resistor
  int deltaX1 = getDelta(joyPin11);

  delay(10);
  
  // reads the value of the variable resistor
  int deltaY1 = getDelta(joyPin12);
  
  // reads the value of the variable resistor
  int deltaX2 = getDelta(joyPin21);  
    
  delay(10);
 
  // reads the value of the variable resistor
  int deltaY2 = getDelta(joyPin22);

  changeNodePosition(HARVBOT_ARM_BEDPLATE_NODE, deltaX1);
  changeNodePosition(HARVBOT_ARM_SHOULDER_NODE, deltaY1);

  changeNodePosition(HARVBOT_ARM_ELBOW_NODE, deltaX2);
  changeNodePosition(HARVBOT_ARM_ELBOW_SCREW_NODE, deltaY2);
}

void changeNodePosition(int nodeType, int delta)
{
  if(delta == 0 || abs(delta)==2)
  {
    return;
  }
  
  HarvbotArmServoNode* node = (HarvbotArmServoNode*)manipulator->getNodeByType(nodeType);

  if(node != NULL)
  {
    int nodePos = node->read();
    
    node->write(nodePos+delta);

    Serial.println(String("Node ") + nodeType + String(" moved on ") + delta + String(". Position: ") + node->read());
  }
}

int getDelta(int pin) 
{  
  // read the analog input:
  int reading = analogRead(pin);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }
  else if(distance == -6)
  {
    return -4;  
  }
  else if(distance == 6)
  {
    return 4;
  }

  // return the distance for this axis:
  return 0;
}
