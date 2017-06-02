#ifndef HarvbotArmProtocol_H_
#define HarvbotArmProtocol_H_

#include <Arduino.h>
#include <HarvbotArm.h>

class HarvbotArmProtocol {
	protected:
		HarvbotArm* m_arm;
	public:

		// Initialzies a new instance.
		HarvbotArmProtocol(HarvbotArm* arm);

		// Releases all resouces.
		~HarvbotArmProtocol();

		// Gets arm instance.
		HarvbotArm* getArm();

		// Processes command.
		String process(String request);

		// Run protocol processing.
		void run();

		// Build response.
		String buildResponse(String command, int nodeType, String data);

		// Parse command value.
		String parseCmdValue(String data, int index);

		virtual String readRequest() = 0;

		virtual void writeResponse(String response) = 0;
};

#endif /* HarvbotArmProtocol_H_ */