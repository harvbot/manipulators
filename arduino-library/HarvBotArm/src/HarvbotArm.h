#ifndef HarvbotArm_H_
#define HarvbotArm_H_

#include <HarvbotArmConstants.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmCircleNode.h>
#include <HarvbotArmScrewNode.h>

class HarvbotArm {
	private: 
		HarvbotArmTypes armType;
	protected:
		int nodesCount;
		HarvbotArmNode** nodes;
	public:
		HarvbotArm(HarvbotArmTypes armType);

		~HarvbotArm();

		HarvbotArmTypes getType();

		virtual void goToStartPosition() = 0;

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
		virtual HarvbotArmNode* getNodeByType(HarvbotArmNodeIdentifiers node);

		/**
			Gets the arm current status.
		*/
		HarvbotNodeStatuses getStatus();
};

#endif /* HarvbotArm_H_ */
