#ifndef HarvbotArmProtocol_H_
#define HarvbotArmProtocol_H_

#include <HarvbotArmConstants.h>
#include <HarvbotArm.h>

class HarvbotArmProtocol {
	private:
		HarvbotArm* m_arm;
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

		// Build response.
		String buildResponse(String command, String nodeType, String data);

		// Parse command value.
		String parseCmdValue(String data, int index);

		virtual String readRequest() = 0;

		virtual void writeResponse(String response) = 0;
};

#endif /* HarvbotArmProtocol_H_ */