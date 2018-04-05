#include <string>
#include "../HarvbotArmConstants.h"
#include "../HarvbotArmFactory.h"
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
	std::string requestData = this->readRequest();

	std::string response;
	if(requestData == "")
	{
		response = this->buildResponse("invalid-request", "");
	}
	else
	{
		response = this->process(requestData);
	}

	this->writeResponse(response);
}

std::string HarvbotArmProtocol::buildErrorResponse(HarvbotArmProtocolErrorCodes errorCode)
{
	return buildResponse("error", std::string(std::to_string((int)errorCode)));
}

std::string HarvbotArmProtocol::buildResponse(std::string result, std::string data)
{
	std::string response = "";
	if(result != "")
	{
    	response += result;
	}

    if(data != "")
    {
		response += ":";
    	response += data;
    }

    return response;
}

std::string HarvbotArmProtocol::parseLine(std::string data, int index)
{
	char separator = ' ';

	int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.at(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }

    if(found > index) 
	{
		return data.substr(strIndex[0], strIndex[1]);
	}

	return "";
}

int HarvbotArmProtocol::commandParamsNumber(std::string data)
{
	char separator = ' ';
	int found = 0;

    for (int i = 0; i <= data.length(); i++) {
        if (data.at(i) == separator) {
            found++;
        }
    }

	if (data.at(data.length()-1) != separator)
	{
		found++;
	}

    return found - 1;
}

HarvbotArmNodeIdentifiers HarvbotArmProtocol::parseNodeIdentifier(std::string data)
{
	std::string nodeIdenfitier = data.substr(0, 2);

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

std::string HarvbotArmProtocol::getNodeIdentifierString(HarvbotArmNodeIdentifiers nodeIdenfitier)
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

std::string HarvbotArmProtocol::parseParamValue(std::string data)
{
	return data.substr(2, data.length() - 2);
}

HarvbotArmCommands HarvbotArmProtocol::parseCommandType(std::string data)
{
	std::string cmd = this->parseLine(data, 0);

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

std::string HarvbotArmProtocol::getCommandTypeString(HarvbotArmCommands cmd)
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

std::string HarvbotArmProtocol::processInitCommand(std::string data)
{
	std::string armType = this->parseLine(data, 1);

	if(armType == "2")
	{
		this->m_arm = HarvbotArmFactory::CreateArm2();
	}
	else
	{
		this->m_arm = NULL;        
		return this->buildErrorResponse(InvalidArmType);
	}

	return this->buildResponse("ok", "");
}

std::string HarvbotArmProtocol::process(std::string requestData)
{
	int paramsNumber = this->commandParamsNumber(requestData);
	if(paramsNumber == -1)
	{
		return this->buildErrorResponse(InvalidCommand);
	}

	// Get command.
	HarvbotArmCommands cmd = this->parseCommandType(requestData);
	if(cmd == Invalid)
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
        return this->buildResponse("ok", std::to_string(((int)status)));
	}
	else if(cmd == InitStart)
	{
		this->m_arm->goToStartPosition();
		return this->buildResponse("ok", "");
	}

	std::string response = "";
	for(int i=0;i<paramsNumber;i++)
	{
		// Take command parameters.
		std::string par = this->parseLine(requestData, i+1);
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
			float pos = circleNode->currentPosition();

			response += std::to_string(pos);
		}
		else if(cmd == Move)
		{
			HarvbotArmCircleNode* circleNode = ((HarvbotArmCircleNode*)node);

			// Take command parameters.
			float degree = ::atof(this->parseParamValue(par).c_str());
			
			// Set position.
			circleNode->move(degree);
			circleNode->runToPosition();

			response += std::to_string(circleNode->currentPosition());
		}
		else if(cmd == Steps)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			// Set position.
			float steps = screwNode->currentPosition();

			response += std::to_string(steps);
		}
		else if(cmd == Angle)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			// Set position.
			float angle = screwNode->getCurrentAngle();

			response += std::to_string(angle);
		}
		else if(cmd == Rotate)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			float steps = ::atof(this->parseParamValue(par).c_str());

			// Rotate.
			((HarvbotArmScrewNode*)node)->rotate(steps);

			float currentSteps = ((HarvbotArmScrewNode*)node)->currentPosition();

			response += std::to_string(currentSteps);
		}
		else if(cmd == RotateOnAngle)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			float angle = ::atof(this->parseParamValue(par).c_str());

			float steps = angle / screwNode->getAnglePerStep();

			// Rotate.
			float currentSteps = screwNode->rotate(steps);

			response += std::to_string(currentSteps);
		}
		else if(cmd == Revolution)
		{
			HarvbotArmScrewNode* screwNode = ((HarvbotArmScrewNode*)node);

			std::string direction = this->parseParamValue(par);

			// revolution.
			if(direction == "F")
			{
				screwNode->revolution(1);
			}
			else if(direction == "B")
			{
				screwNode->revolution(-1);
			}
			
			int currentSteps = screwNode->currentPosition();

			response += std::to_string(currentSteps);
		}
		else if(cmd == NodeStatus)
		{
			HarvbotNodeStatuses status = node->getStatus();
			response += std::to_string((int)status);
		}

		if(i < paramsNumber -1 )
		{
			response += ' ';
		}
	}

	return this->buildResponse("ok", response);
}