#include <HarvbotArm.h>
#include <HarvbotArm2.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArmScrewNode.h>
#include <HarvbotArmAFMotorScrewNode.h>

HarvbotArm2* manipulator;

void setup() 
{
  Serial.begin(9600);

  HarvbotArmServoNodePins bedplate;
  bedplate.Pin = 22;
  bedplate.InitialPos = 90;

  HarvbotArmServoNodePins shoulder;
  shoulder.Pin = 23;
  shoulder.InitialPos = 150; 

  HarvbotArmServoNodePins elbow;
  elbow.Pin = 24;
  elbow.InitialPos = 60;

  HarvbotArmAFMotorScrewNode* claw = new HarvbotArmAFMotorScrewNode(HARVBOT_ARM_CLAW_NODE, 2, 0, 200);
  claw->setSpeed(50);
  
  manipulator = new HarvbotArm2(bedplate, shoulder, elbow, claw);
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
  HarvbotArmNode* node = manipulator->getNodeByType(nodeType);

  if(node == NULL)
  {
      Serial.println("Node with " + String(nodeType) + " type doesn't exist");
      return;
  }
  
  if(cmd == "pos")
  {
      // Set position.
      int pos = ((HarvbotArmServoNode*)node)->read();

      String response = getResponse(cmd, nodeType, String(pos));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "move")
  {
      // Take command parameters.
      int degree = getValue(msg, ':', 3).toInt();
      
      // Set position.
      ((HarvbotArmServoNode*)node)->write(degree);

      String response = getResponse(cmd, nodeType, String(((HarvbotArmServoNode*)node)->read()));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "sweep")
  {
      // Take command parameters.
      int degree = getValue(msg, ':', 3).toInt();
      
      // Set position.
      ((HarvbotArmServoNode*)node)->write(degree);

      String response = getResponse(cmd, nodeType, String(degree));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "steps")
  {
      // Set position.
      float steps = ((HarvbotArmScrewNode*)node)->getSteps();

      String response = getResponse(cmd, nodeType, String(steps));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "angle")
  {
      // Set position.
      float angle = ((HarvbotArmScrewNode*)node)->getCurrentAngle();

      String response = getResponse(cmd, nodeType, String(angle));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "rotate-steps")
  {
      float steps = getValue(msg, ':', 3).toFloat();
    
      // Rotate.
      ((HarvbotArmScrewNode*)node)->rotate(steps);

      float currentSteps = ((HarvbotArmScrewNode*)node)->getSteps();

      String response = getResponse(cmd, nodeType, String(currentSteps));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "rotate-angle")
  {
      float angle = getValue(msg, ':', 3).toFloat();

      float steps = angle / ((HarvbotArmScrewNode*)node)->getAnglePerStep();
    
      // Rotate.
      float currentSteps = ((HarvbotArmScrewNode*)node)->rotate(steps);
      
      String response = getResponse(cmd, nodeType, String(currentSteps));

      // Return response.
      Serial.println(response);
  }
  else if(cmd == "revolution")
  {
      String direction = getValue(msg, ':', 3);
    
      // revolution.
      if(direction == "forward")
      {
        ((HarvbotArmScrewNode*)node)->revolution(1);
      }
      else if(direction == "backward")
      {
        ((HarvbotArmScrewNode*)node)->revolution(-1);
      }
      
      int currentSteps = ((HarvbotArmScrewNode*)node)->getSteps();

      String response = getResponse(cmd, nodeType, String(currentSteps));

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
