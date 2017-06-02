#ifndef HarvbotArmSerialProtocol_H_
#define HarvbotArmSerialProtocol_H_

#include <Arduino.h>
#include <HarvbotArmProtocol.h>

class HarvbotArmSerialProtocol : public HarvbotArmProtocol {
	public:

		// Initialzies a new instance.
		HarvbotArmSerialProtocol(HarvbotArm* arm);

		// Releases all resouces.
		~HarvbotArmSerialProtocol();

        String readRequest();

		void writeResponse(String response);
};

#endif /* HarvbotArmSerialProtocol_H_ */