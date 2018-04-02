#ifndef HarvbotArmSerialProtocol_H_
#define HarvbotArmSerialProtocol_H_

#include <string>
#include "HarvbotArmProtocol.h"

class HarvbotArmSerialProtocol : public HarvbotArmProtocol {
	public:

		// Initialzies a new instance.
		HarvbotArmSerialProtocol();

		// Releases all resouces.
		~HarvbotArmSerialProtocol();

		std::string readRequest();

		void writeResponse(std::string response);
};

#endif /* HarvbotArmSerialProtocol_H_ */