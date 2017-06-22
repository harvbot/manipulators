#include <HarvbotArmNode.h>
#include <HarvbotArmAFMotorScrewNode.h>
#include <HarvbotArmConstants.h>

HarvbotArmAFMotorScrewNode* claw;

int joyPinX = 8;

int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;

void setup() 
{
  Serial.begin(9600);

  claw = new HarvbotArmAFMotorScrewNode(Claw, 2, 0, 200);
 
  // Do not forget to setup speed, otherwise stepper won't work.
  claw->setSpeed(60);
}

void loop() 
{
   int deltaX = getDelta(joyPinX);

  if(deltaX != 0)
  {
    if(deltaX > 0)
    {
      claw->rotate(200); 
    }
    else
    {
      claw->rotate(-200); 
    }

    // Rotate claw for 1 step;
    Serial.println("Claw was rotated. Current pos: " + String(claw->getSteps()));
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

