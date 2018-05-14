#ifndef HarvbotGripper_H_
#define HarvbotGripper_H_

#include <vector>
#include "Cameras/HarvbotCamera.h"
#include "Rangefinder/HarvbotRangefinder.h"
#include "Recognition/HarvbotRecognizer.h"
#include "HarvbotGripperObserver.h"
#include "HarvbotArm.h"

using namespace std;

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

		void attachObserver(HarvbotGripperObserver* observer);

		void detachObserver(HarvbotGripperObserver* observer);
	protected:
		HarvbotRecognizer * getRecognizer();

		vector<HarvbotGripperObserver*> observers;
	private:
		bool _isVisualizationOn;

		HarvbotRecognizer* _recognizer;
};

#endif /* HarvbotGripper_H_ */