#ifndef HarvbotArmLinearNode_H_
#define HarvbotArmLinearNode_H_

#include <string>
#include "HarvbotArmNode.h"
#include "../HarvbotArmConstants.h"

class HarvbotArmLinearNode : public HarvbotArmNode {
	protected: 
		float m_pos;
		int m_stepsPerRevolution;
		int m_maxRevolutionsCount;
        int m_reductorGear;

		virtual float setCurrentPosition(float pos);
	public:
		HarvbotArmLinearNode(
            HarvbotArmNodeIdentifiers identifier, 
            float pos, 
            int stepsPerRevolution,
            int maxRevolutionsCount=HARVBOT_ARM_CLAW_MAX_FULL_ROTATION,
            int reductorGear=1);

		~HarvbotArmLinearNode();

        HarvbotArmNodeTypes getType();

		virtual void open();

		virtual void close();

        /**
            Rotates the screew on specified number of steps.
            Returns current positions.
        */
		virtual float rotate(float steps);

        /**
            Makes one whole revolution in specified direction.
        */
		virtual float revolution(bool direction);

		/**
		Gets the current angle.
		*/
		virtual float getCurrentAngle();

		/**
		Gets the current position. In general the number of steps which were passed on screw.
		*/
		virtual float currentPosition();

		/**
		Gets the angle per step.
		*/
		virtual float getAnglePerStep();
};

#endif /* HarvbotArmLinearNode_H_ */