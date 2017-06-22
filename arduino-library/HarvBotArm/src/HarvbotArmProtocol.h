#ifndef HarvbotArmProtocol_H_
#define HarvbotArmProtocol_H_

#include <HarvbotArmConstants.h>
#include <HarvbotArm.h>

class HarvbotArmProtocol {
	private:
		HarvbotArm* m_arm;

		String processInitCommand(String data);

		String getCommandTypeString(HarvbotArmCommands cmd);

		// Build response.
		String buildResponse(String command, String data);

		// Build error response.
		String buildErrorResponse(HarvbotArmProtocolErrorCodes errorCode);

		// Parse command value.
		String parseLine(String data, int index);

		// Parse command value.
		HarvbotArmNodeIdentifiers parseNodeIdentifier(String data);

		String parseParamValue(String data);

		// Parse command value.
		HarvbotArmCommands parseCommandType(String data);

		int commandParamsNumber(String data);

		String getNodeIdentifierString(HarvbotArmNodeIdentifiers nodeIdenfitier);
	public:

		// Initialzies a new instance.
		HarvbotArmProtocol();

		// Releases all resouces.
		~HarvbotArmProtocol();

		// Gets arm instance.
		HarvbotArm* getArm();

		// Processes command.
		String process(String request);

		// Run protocol processing.
		void run();

		virtual String readRequest() = 0;

		virtual void writeResponse(String response) = 0;
};

#endif /* HarvbotArmProtocol_H_ */