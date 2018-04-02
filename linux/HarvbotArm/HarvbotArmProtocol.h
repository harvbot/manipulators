#ifndef HarvbotArmProtocol_H_
#define HarvbotArmProtocol_H_

#include <string>
#include "HarvbotArmConstants.h"
#include "HarvbotArm.h"

class HarvbotArmProtocol {
	private:
		HarvbotArm* m_arm;

		std::string processInitCommand(std::string data);

		std::string getCommandTypeString(HarvbotArmCommands cmd);

		// Build response.
		std::string buildResponse(std::string command, std::string data);

		// Build error response.
		std::string buildErrorResponse(HarvbotArmProtocolErrorCodes errorCode);

		// Parse command value.
		std::string parseLine(std::string data, int index);

		// Parse command value.
		HarvbotArmNodeIdentifiers parseNodeIdentifier(std::string data);

		std::string parseParamValue(std::string data);

		// Parse command value.
		HarvbotArmCommands parseCommandType(std::string data);

		int commandParamsNumber(std::string data);

		std::string getNodeIdentifierString(HarvbotArmNodeIdentifiers nodeIdenfitier);
	public:

		// Initialzies a new instance.
		HarvbotArmProtocol();

		// Releases all resouces.
		~HarvbotArmProtocol();

		// Gets arm instance.
		HarvbotArm* getArm();

		// Processes command.
		std::string process(std::string request);

		// Run protocol processing.
		void run();

		virtual std::string readRequest() = 0;

		virtual void writeResponse(std::string response) = 0;
};

#endif /* HarvbotArmProtocol_H_ */