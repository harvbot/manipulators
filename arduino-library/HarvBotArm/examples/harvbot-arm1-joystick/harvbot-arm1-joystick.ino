#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArm1.h>

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
  
  manipulator = new HarvbotArm1();
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

  changeNodePosition(SERVO_BEDPLATE_PIN, deltaX1);
  changeNodePosition(SERVO_SHOULDER_PIN, deltaY1);

  changeNodePosition(SERVO_ELBOW_PIN, deltaX2);
  changeNodePosition(SERVO_ELBOW_SCREW_PIN, deltaY2);
}

void changeNodePosition(int nodeType, int delta)
{
  if(delta == 0 || abs(delta)==2)
  {
    return;
  }
  
  HarvbotArmServoNode* node = getNode(nodeType);

  if(node != NULL)
  {
    int nodePos = node->read();
    
    node->sweep(nodePos+delta);

    Serial.println(String("Node ") + nodeType + String(" moved on ") + delta + String(". Position: ") + node->read());
  }
}

HarvbotArmServoNode* getNode(int nodeType)
{
  switch(nodeType)
  {
    case SERVO_BEDPLATE_PIN:
    {
      return manipulator->getBedplate();
    }
    case SERVO_SHOULDER_PIN:
    {
      return manipulator->getShoulder();
    }
    case SERVO_ELBOW_PIN:
    {
      return manipulator->getElbow();
    }
    case SERVO_ELBOW_SCREW_PIN:
    {
      return manipulator->getElbowScrew();
    }
    case SERVO_HAND_PIN:
    {
      return manipulator->getHand();
    }
    case SERVO_HAND_SCREW_PIN:
    {
      return manipulator->getHandScrew();
    }
    default : return NULL;
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
