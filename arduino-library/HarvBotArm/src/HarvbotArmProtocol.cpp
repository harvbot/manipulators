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
		return this->buildResponse("invalid-request", "");
	}

	String response = this->process(requestData);

	this->writeResponse(response);
}

String HarvbotArmProtocol::buildErrorResponse(HarvbotArmProtocolErrorCodes errorCode)
{
	return buildResponse("error", String((int)errorCode));
}

String HarvbotArmProtocol::buildResponse(String result, String data)
{
	if(result != NULL && result != "")
	{
    	result += result;
	}

    if(data != NULL && data != "")
    {
		result += ":";
    	result += data;
    }
    
    return result;
}

String HarvbotArmProtocol::parseLine(String data, int index)
{
	char separator = ' ';

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

int HarvbotArmProtocol::commandParamsNumber(String data)
{
	char separator = ' ';
	int found = 0;

    for (int i = 0; i <= data.length(); i++) {
        if (data.charAt(i) == separator) {
            found++;
        }
    }

    return found - 1;
}

HarvbotArmNodeIdentifiers HarvbotArmProtocol::parseNodeIdentifier(String data)
{
	String nodeIdenfitier = data.substring(0, 2);

	if(nodeIdenfitier == "BP")
	{
		return Bedplate;
	}
	else if(nodeIdenfitier == "SH")
	{
		return Shoulder;
	}
	else if(nodeIdenfitier == "EL")
	{
		return Elbow;
	}
	else if(nodeIdenfitier == "ES")
	{
		return ElbowScrew;
	}
	else if(nodeIdenfitier == "HA")
	{
		return Hand;
	}
	else if(nodeIdenfitier == "HS")
	{
		return HandScrew;
	}
	else if(nodeIdenfitier == "CL")
	{
		return Claw;
	}
	else
	{
		return Undefined;
	}
}

String HarvbotArmProtocol::getNodeIdentifierString(HarvbotArmNodeIdentifiers nodeIdenfitier)
{
	if(nodeIdenfitier == Bedplate)
	{
		return "BP";
	}
	else if(nodeIdenfitier == Shoulder)
	{
		return "SH";
	}
	else if(nodeIdenfitier == Elbow)
	{
		return "EL";
	}
	else if(nodeIdenfitier == ElbowScrew)
	{
		return "ES";
	}
	else if(nodeIdenfitier == Hand)
	{
		return "HA";
	}
	else if(nodeIdenfitier == HandScrew)
	{
		return "HS";
	}
	else if(nodeIdenfitier == Claw)
	{
		return "CL";
	}
	else
	{
		return "";
	}
}

String HarvbotArmProtocol::parseParamValue(String data)
{
	return data.substring(2);
}

HarvbotArmCommands HarvbotArmProtocol::parseCommandType(String data)
{
	String cmd = this->parseLine(data, 1);

	if(cmd == "HIN")
	{
		return Init;
	}
	else if(cmd == "HAS")
	{
		return Status;
	}
	else if(cmd == "HIS")
	{
		return InitStart;
	}
	else if(cmd == "HNP")
	{
		return Position;
	}
	else if(cmd == "HNM")
	{
		return Move;
	}
	else if(cmd == "HSS")
	{
		return Steps;
	}
	else if(cmd == "HSA")
	{
		return Angle;
	}
	else if(cmd == "HSR")
	{
		return Rotate;
	}
	else if(cmd == "HRA")
	{
		return RotateOnAngle;
	}
	else if(cmd == "HRE")
	{
		return Revolution;
	}
	else if(cmd == "HNS")
	{
		return NodeStatus;
	}
	else
	{
		return Invalid;
	}
}

String HarvbotArmProtocol::getCommandTypeString(HarvbotArmCommands cmd)
{
	switch(cmd)
	{
		case Init: return "HIN";
		case Status: return "HAS";
		case InitStart: return "HIS";
		case Position: return "HNP";
		case Move: return "HNM";
		case Steps: return "HSS";
		case Angle: return "HSA";
		case Rotate: return "HSR";
		case RotateOnAngle: return "HRA";
		case Revolution: return "HRE";
		case NodeStatus: return "HNS";
		default: return "";
	}
}

String HarvbotArmProtocol::processInitCommand(String data)
{
	String armType = this->parseLine(data, 2);

	if(armType == "1")
	{
		this->m_arm = HarvbotArmFactory::CreateServoArm1();
	}
	else if(armType == "2")
	{
		this->m_arm = HarvbotArmFactory::CreateAFMotorArm2();
	}
	else
	{
		this->m_arm = NULL;        
		return this->buildErrorResponse(InvalidArmType);
	}

	return this->buildResponse("ok", "");
}

String HarvbotArmProtocol::process(String requestData) 
{
	int paramsNumber = this->commandParamsNumber(requestData);
	if(paramsNumber == -1)
	{
		return this->buildErrorResponse(InvalidCommand);
	}

	// Get command.
	HarvbotArmCommands cmd = this->parseCommandType(requestData);
	if(cmd==Invalid)
	{
		return this->buildErrorResponse(InvalidCommand); 
	}

	if(cmd == Init)
	{
		return this->processInitCommand(requestData);
	}

	HarvbotArm* arm = this->getArm();
	if(arm == NULL)
	{
		return this->buildErrorResponse(Uninitialized);
	}

	else if(cmd == Status)
	{
		HarvbotNodeStatuses status = this->m_arm->getStatus();
        return this->buildResponse("ok", String((int)status));
	}
	else if(cmd == InitStart)
	{
		this->m_arm->goToStartPosition();
		return this->buildResponse("ok", "");
	}

	String response = "";
	for(int i=0;i<paramsNumber;i++)
	{
		// Take command parameters.
		String par = this->parseLine(requestData, i+1); 
		HarvbotArmNodeIdentifiers nodeType = this->parseNodeIdentifier(par);

		// Get node.
		HarvbotArmNode* node = arm->getNodeByType(nodeType);

		if(node == NULL)
		{
			return this->buildErrorResponse(InvalidNodeIdentifier);
		}

		response += this->getNodeIdentifierString(nodeType);
		
		if(cmd == Position)
		{
			HarvbotArmCircleNode* circleNode = ((HarvbotArmCircleNode*)node);
			
			// Set position.
			float pos = circleNode->read();

			response += String(pos);
		}
		else if(cmd == Move)
		{
			HarvbotArmCircleNode* circleNode = ((HarvbotArmCircleNode*)node);

			// Take command parameters.
			float degree = this->parseParamValue(par).toFloat();
			
			// Set position.
			circleNode->write(degree);

			response += String(circleNode->read());
		}
		else if(cmd == Steps)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			// Set position.
			float steps = screwNode->getSteps();

			response += String(steps);
		}
		else if(cmd == Angle)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			// Set position.
			float angle = screwNode->getCurrentAngle();

			response += String(angle);
		}
		else if(cmd == Rotate)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			float steps = this->parseParamValue(par).toFloat();

			// Rotate.
			((HarvbotArmScrewNode*)node)->rotate(steps);

			float currentSteps = ((HarvbotArmScrewNode*)node)->getSteps();

			response += String(currentSteps);
		}
		else if(cmd == RotateOnAngle)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			float angle = this->parseParamValue(par).toFloat();

			float steps = angle /screwNode->getAnglePerStep();

			// Rotate.
			float currentSteps = screwNode->rotate(steps);

			response += String(currentSteps);
		}
		else if(cmd == Revolution)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			String direction = this->parseParamValue(par);

			// revolution.
			if(direction == "F")
			{
				screwNode->revolution(1);
			}
			else if(direction == "B")
			{
				screwNode->revolution(-1);
			}
			
			int currentSteps = screwNode->getSteps();

			response += String(currentSteps);
		}
		else if(cmd == NodeStatus)
		{
			HarvbotNodeStatuses status = node->getStatus();
			response += String((int)status);
		}

		if(i < paramsNumber -1 )
		{
			response += ' ';
		}
	}

	return this->buildResponse("ok", response);
}