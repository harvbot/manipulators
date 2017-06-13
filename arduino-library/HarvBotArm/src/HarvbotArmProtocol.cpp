#include "HarvbotArmConstants.h"
#include "HarvbotArmFactory.h"
#include "HarvbotArmProtocol.h"

HarvbotArmProtocol::HarvbotArmProtocol() {
}

HarvbotArmProtocol::~HarvbotArmProtocol() {
}

HarvbotArm* HarvbotArmProtocol::getArm() {
	return this->m_arm;
}

void HarvbotArmProtocol::run()
{
	String requestData = this->readRequest();

	if(requestData == "")
	{
		return this->buildResponse("invalid-request", "", "");
	}

	String response = this->process(requestData);

	this->writeResponse(response);
}

String HarvbotArmProtocol::buildResponse(String command, String nodeType, String data)
{
	String result = "harm:";

	if(command != NULL && command != "")
	{
    	result += command;
    	result += ":";
	}

	if(nodeType != NULL && nodeType != "")
	{
		result += nodeType;
		result += ":";
	}

    if(data != NULL && data != "")
    {      
    	result += data;
		result += ":";
    }
    
    result += "~harm";

    return result;
}

String HarvbotArmProtocol::parseCmdValue(String data, int index)
{
	char separator = ':';

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

String HarvbotArmProtocol::process(String requestData) 
{
	// Get command.
	String cmd = this->parseCmdValue(requestData, 1);

	if(cmd == "init")
	{
		String armType = this->parseCmdValue(requestData, 2);

		if(armType == "SE1")
		{
			this->m_arm = HarvbotArmFactory::CreateServoArm1();
		}
		else if(armType == "AFM2")
		{
			this->m_arm = HarvbotArmFactory::CreateAFMotorArm2();
		}
		else
		{
			this->m_arm = NULL;		
			return this->buildResponse("init", "invalid-arm-type", "");
		}

		return this->buildResponse("init", armType, "");
	}
	else if(cmd == "status")
	{
		int status = this->m_arm->getStatus();
		return this->buildResponse(cmd, String(status), "");
	}
	else if(cmd == "init-start")
	{
		this->m_arm->goToStartPosition();
		return this->buildResponse("init-start", "", "");
	}

	HarvbotArm* arm = this->getArm();
	if(arm == NULL)
	{
		return this->buildResponse("undefined-arm", "", "");
	}

	// Take command parameters.
	int nodeType = this->parseCmdValue(requestData, 2).toInt();

	// Get node.
	HarvbotArmNode* node = arm->getNodeByType(nodeType);

	if(node == NULL)
	{
		return this->buildResponse("invalid-node-number", String(nodeType), cmd);
	}

	if(cmd == "pos")
	{
		HarvbotArmCircleNode* circleNode = ((HarvbotArmCircleNode*)node);
		
		// Set position.
		float pos = circleNode->read();

		return this->buildResponse(cmd, String(nodeType), String(pos));
	}
	else if(cmd == "move")
	{
		HarvbotArmCircleNode* circleNode = ((HarvbotArmCircleNode*)node);

		// Take command parameters.
		int degree = this->parseCmdValue(requestData, 3).toInt();
		
		// Set position.
		circleNode->write(degree);

		return this->buildResponse(cmd, String(nodeType), String(circleNode->read()));
	}
	else if(cmd == "steps")
	{
		HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

		// Set position.
		float steps = screwNode->getSteps();

		return this->buildResponse(cmd, String(nodeType), String(steps));
	}
	else if(cmd == "angle")
	{
		HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

		// Set position.
		float angle = screwNode->getCurrentAngle();

		return this->buildResponse(cmd, String(nodeType), String(angle));
	}
	else if(cmd == "rotate-steps")
	{
		HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

		float steps = this->parseCmdValue(requestData, 3).toFloat();

		// Rotate.
		((HarvbotArmScrewNode*)node)->rotate(steps);

		float currentSteps = ((HarvbotArmScrewNode*)node)->getSteps();

		return this->buildResponse(cmd, String(nodeType), String(currentSteps));
	}
	else if(cmd == "rotate-angle")
	{
		HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

		float angle = this->parseCmdValue(requestData, 3).toFloat();

		float steps = angle /screwNode->getAnglePerStep();

		// Rotate.
		float currentSteps = screwNode->rotate(steps);
		
		return this->buildResponse(cmd, String(nodeType), String(currentSteps));
	}
	else if(cmd == "revolution")
	{
		HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

		String direction = this->parseCmdValue(requestData, 3);

		// revolution.
		if(direction == "forward")
		{
			screwNode->revolution(1);
		}
		else if(direction == "backward")
		{
			screwNode->revolution(-1);
		}
		
		int currentSteps = screwNode->getSteps();

		return this->buildResponse(cmd, String(nodeType), String(currentSteps));
	}
	else if(cmd == "node-status")
	{
		int status = node->getStatus();
		return this->buildResponse(cmd, String(nodeType), String(status));
	}
	else
	{
		return this->buildResponse("invalid-command", String(nodeType), cmd);
	}
}