#ifndef HarvbotArmScrewNode_H_
#define HarvbotArmScrewNode_H_

#include <HarvbotArmNode.h>
#include <HarvbotArmConstants.h>

class HarvbotArmScrewNode : public HarvbotArmNode {
	protected: 
		float m_pos;
		int m_speed;
		int m_maxStepsCount;
		int m_maxFullRotaionCount;
        int m_reductorGear;
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
            Gets the current position. In general the number of steps which were passed on screw.
        */
		float getSteps();
        
        /**
            Rotates the screew on specified number of steps.
            Returns current positions.
        */
		virtual float rotate(float steps);

        /**
            Gets the current rotaton speed.
        */
		int getSpeed();

        /**
            Sets the current rotation speed.
        */
		virtual void setSpeed(int speed);

        /**
            Makes one whole revolution in specified direction.
        */
		virtual float revolution(int direction);

        /**
            Gets the angle per step.
        */
		virtual float getAnglePerStep();

        /**
            Gets the current angle.
        */
		virtual float getCurrentAngle();

        /**
            Moves screw to start position.
        */
        virtual void goToStartPosition();
};

#endif /* HarvbotArmScrewNode_H_ */