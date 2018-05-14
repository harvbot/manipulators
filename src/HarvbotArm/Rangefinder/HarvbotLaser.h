#ifndef HarvbotLaser_H_
#define HarvbotLaser_H_

class HarvbotLaser
{
public:
	HarvbotLaser(unsigned short pin);
	~HarvbotLaser();

	void powerOn();

	void powerOff();
private:
	unsigned short _pin;
};

#endif /* HarvbotLaser_H_ */