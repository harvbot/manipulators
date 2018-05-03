#pragma once
class HarvbotGripperObserver
{
public:
	HarvbotGripperObserver();
	~HarvbotGripperObserver();

	virtual void ObjectPicked() = 0;
};

