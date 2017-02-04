#ifndef HarvbotArmNode_H_
#define HarvbotArmNode_H_

#include <Arduino.h>

class HarvbotArmNode {
	public:
		HarvbotArmNode();
		~HarvbotArmNode();
		virtual int read();
		virtual void write(int pos);
};

#endif /* HarvbotArmNode_H_ */