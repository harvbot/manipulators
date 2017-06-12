#include <HarvbotArmProtocol.h>
#include <HarvbotArmSerialProtocol.h>

HarvbotArmProtocol* protocol;

void setup() 
{
  Serial.begin(9600);

  protocol = new HarvbotArmSerialProtocol();
}

void loop() 
{
  protocol->run();
}
