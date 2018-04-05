#ifndef HarvbotArmScrewNode_H_
#define HarvbotArmScrewNode_H_

#include <string>
#include "HarvbotArmNode.h"
#include "../HarvbotArmConstants.h"

class HarvbotArmScrewNode : public HarvbotArmNode {
	protected: 
		float m_pos;
		int m_maxStepsCount;
		int m_maxFullRotaionCount;
        int m_reductorGear;

		/**
		Gets the angle per step.
		*/
		virtual float getAnglePerStep();

		/**
		Gets the current position. In general the number of steps which were passed on screw.
		*/
		virtual float currentPosition();
	public:
		HarvbotArmScrewNode(
            HarvbotArmNodeIdentifiers identifier, 
            float pos, 
            int maxStepsCount, 
            int maxFullRotaionCount=HARVBOT_ARM_CLAW_MAX_FULL_ROTATION,
            int reductorGear=1);

		~HarvbotArmScrewNode();

        HarvbotArmNodeTypes getType();

        /**
            Rotates the screew on specified number of steps.
            Returns current positions.
        */
		virtual float rotate(float steps);

        /**
            Makes one whole revolution in specified direction.
        */
		virtual float revolution(int direction);

		/**
		Gets the current angle.
		*/
		virtual float getCurrentAngle();
};

#endif /* HarvbotArmScrewNode_H_ */