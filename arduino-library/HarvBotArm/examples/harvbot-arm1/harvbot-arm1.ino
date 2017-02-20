#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArm1.h>

HarvbotArm1* manipulator;

void setup() 
{
  Serial.begin(9600);
  
  manipulator = new HarvbotArm1();
}

void loop() 
{
  // Read message.
  String msg = Serial.readString();

  // Get command.
  String cmd = getValue(msg, ':', 1);

  // Take command parameters.
  int nodeType = getValue(msg, ':', 2).toInt();

  // Get node.
  HarvbotArmServoNode* node =  getNode(nodeType);
  
  if(cmd == "pos")
  {
      // Set position.
      int pos = node->read();

      String response = getResponse(cmd, nodeType, String(pos));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "move")
  {
      // Take command parameters.
      int degree = getValue(msg, ':', 3).toInt();
      
      // Set position.
      node->write(degree);

      String response = getResponse(cmd, nodeType, String(degree));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "sweep")
  {
      // Take command parameters.
      int degree = getValue(msg, ':', 3).toInt();
      
      // Set position.
      node->sweep(degree);

      String response = getResponse(cmd, nodeType, String(degree));

      // Return response.
      Serial.println(response);
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

String getResponse(String command, int nodeType, String data)
{
    String result = "harm:";
    result += command;
    result += ":";
    result += nodeType;

    if(data != NULL && data != "")
    {
      result += ":";
      result += data;
    }
    
    result += ":~harm";
    return result;
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
