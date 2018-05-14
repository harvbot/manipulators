#ifndef HarvbotRecognizer_H_
#define HarvbotRecognizer_H_

#include "../Spatial/HarvbotRect.h"
#include "../Cameras/HarvbotFrame.h"

class HarvbotRecognizer
{
public:
	HarvbotRecognizer();
	~HarvbotRecognizer();

	virtual HarvbotRect recognize(HarvbotFrame* frame) = 0;
};


#endif /* HarvbotRecognizer_H_ */