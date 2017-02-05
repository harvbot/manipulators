#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArm1.h>

HarvbotArm1* manipulator;

void setup() 
{
  manipulator = new HarvbotArm1();
}

void loop() 
{
  // Read message.
  string msg = Serial.readString();

  // Get command.
  string cmd = getValue(msg, ':', 1);
  
  switch(cmd)
  {
    case "pos":
    {
      // Take command parameters.
      int nodeType = getValue(msg, ':', 2).toInt();

      // Get node.
      HarvbotArmServoNode* node =  getNode(nodeType);

      // Set position.
      var pos = node.read();

      // Return response.
      Serial.write("harm:pos:"+pos+":~harm");
      
      break;
    }
    case "move":
    {
      // Take command parameters.
      int nodeType = getValue(msg, ':', 2).toInt();
      int degree = getValue(msg, ':', 3).toInt();

      // Get node.
      HarvbotArmServoNode* node =  getNode(nodeType);

      // Set position.
      node.write(degree);

      // Return response.
      Serial.write("harm:move:"+nodeType+":"+degree+":~harm");
      
      break;
    }
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
    default : return null;
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
