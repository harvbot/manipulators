#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArm1.h>

HarvbotArm1* manipulator;

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
  // Read message.
  String msg = Serial.readString();

  // Get command.
  String cmd = getValue(msg, ':', 1);
  
  if(cmd == "pos")
  {
      // Take command parameters.
      int nodeType = getValue(msg, ':', 2).toInt();

      // Get node.
      HarvbotArmServoNode* node =  getNode(nodeType);

      // Set position.
      int pos = node->read();

      // Return response.
      Serial.print("harm:pos:");
      Serial.print(pos);
      Serial.println(":~harm");
  }
  else if(cmd == "move")
  {
      // Take command parameters.
      int nodeType = getValue(msg, ':', 2).toInt();
      int degree = getValue(msg, ':', 3).toInt();

      // Get node.
      HarvbotArmServoNode* node =  getNode(nodeType);

      // Set position.
      node->write(degree);

      // Return response.
      Serial.print("harm:move:");
      Serial.print(nodeType);
      Serial.print(":");
      Serial.print(degree);
      Serial.println(":~harm");
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

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
