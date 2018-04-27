#pragma once
#include "Cameras/HarvbotCamera.h"
#include "Rangefinder/HarvbotRangefinder.h"
#include "Recognition/HarvbotRecognizer.h"
#include "HarvbotArm.h"

class HarvbotGripper
{
	public:
		HarvbotGripper(HarvbotRecognizer* recognizer);
		~HarvbotGripper();
		
		virtual HarvbotArm* getArm() = 0;

		virtual HarvbotCamera* getCamera() = 0;

		virtual HarvbotRangefinder* getRangefinder() = 0;

		void turnOnVisuaization();

		void turnOffVisuaization();

		bool isVisualizationOn();

		virtual void start() = 0;

		virtual void stop() = 0;
	protected:
		HarvbotRecognizer * getRecognizer();
	private:
		bool _isVisualizationOn;

		HarvbotRecognizer* _recognizer;
};

