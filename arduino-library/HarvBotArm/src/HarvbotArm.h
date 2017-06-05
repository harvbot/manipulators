#ifndef HarvbotArm_H_
#define HarvbotArm_H_

#include <HarvbotArmConstants.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmCircleNode.h>
#include <HarvbotArmScrewNode.h>

class HarvbotArm {
	private: 
		int armType;
	protected:
		int nodesCount;
		HarvbotArmNode** nodes;
	public:
		HarvbotArm(int armType);
		~HarvbotArm();
		int getType();

		/**
			Gets bedplate node.
		*/
		virtual HarvbotArmCircleNode* getBedplate();

		/**
			Gets shoulder node.
		*/
		virtual HarvbotArmCircleNode* getShoulder();

		/**
			Gets elbow node.
		*/
		virtual HarvbotArmCircleNode* getElbow();

		/**
			Gets node by node type.
		*/
		virtual HarvbotArmNode* getNodeByType(int nodeType);
};

#endif /* HarvbotArm_H_ */
