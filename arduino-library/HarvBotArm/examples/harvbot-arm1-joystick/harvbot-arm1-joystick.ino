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

void setup() 
{
  manipulator = new HarvbotArm1();

  manipulator->getBedplate()->write(90);
  delay(25); 
  manipulator->getShoulder()->write(45);
  delay(25); 
  manipulator->getElbow()->write(0);
  delay(25); 
  manipulator->getElbowScrew()->write(0);
  delay(25); 
  manipulator->getHand()->write(180);
  delay(25); 
  manipulator->getHandScrew()->write(30);
}

void loop() 
{
  // reads the value of the variable resistor
  int deltaX1 = treatValue(analogRead(joyPin11));  
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(100);            
  // reads the value of the variable resistor
  int deltaY1 = treatValue(analogRead(joyPin12));

  // reads the value of the variable resistor
  int deltaX2 = treatValue(analogRead(joyPin21));  
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(100);            
  // reads the value of the variable resistor
  int deltaY2 = treatValue(analogRead(joyPin22));

  changeNodePosition(SERVO_BEDPLATE_PIN, deltaX1);
  changeNodePosition(SERVO_SHOULDER_PIN, deltaY1);

  changeNodePosition(SERVO_ELBOW_PIN, deltaX2);
  changeNodePosition(SERVO_ELBOW_SCREW_PIN, deltaY2);

  delay(100);
}

void changeNodePosition(int nodeType, int delta)
{
  if(delta == 0)
  {
    return;
  }
  
  HarvbotArmServoNode* node = getNode(nodeType);
  
  int nodePos = node->read();
  nodePos += delta;
  
  node->write(nodePos);
  delay(100);
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

int treatValue(int data) {
  return (data * 9 / 1024)-4;
}
