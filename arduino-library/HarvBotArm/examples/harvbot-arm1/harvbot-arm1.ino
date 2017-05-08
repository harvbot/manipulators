#include <HarvbotArm.h>
#include <HarvbotArm1.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>

HarvbotArm1* manipulator;

void setup() 
{
  Serial.begin(9600);

  HarvbotArmServoNodePins bedplate;
  bedplate.Pin = 2;
  bedplate.InitialPos = 90;

  HarvbotArmServoNodePins shoulder;
  shoulder.Pin = 3;
  shoulder.InitialPos = 150; 

  HarvbotArmServoNodePins elbow;
  elbow.Pin = 4;
  elbow.InitialPos = 60;

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
  // Read message.
  String msg = Serial.readString();

  if(msg=="")
  {
    delay(100);
    return;
  }

  // Get command.
  String cmd = getValue(msg, ':', 1);

  // Take command parameters.
  int nodeType = getValue(msg, ':', 2).toInt();

  // Get node.
  HarvbotArmServoNode* node = (HarvbotArmServoNode*)manipulator->getNodeByType(nodeType);

  if(node == NULL)
  {
      Serial.println("Node with " + String(nodeType) + " type doesn't exist");
      return;
  }
  
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
  else if(cmd != "")
  {
      Serial.println(getResponse("invalid-command", nodeType, cmd));
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
