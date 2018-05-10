CC	= g++
CFLAGS	= -Wall -std=c++11 -fno-strict-aliasing -g2 -gdwarf-2 -fthreadsafe-statics -D "LINUX" 
INCLUDE	= -I/usr/local/include

LDFLAGS	= -L/usr/local/lib
LDLIBS = -lwiringPi -lpthread -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc

SRC	= Accelerometers/HarvbotAccelerometer.cpp			 \
	Accelerometers/HarvbotADXL345PiI2CAccelerometer.cpp	 \
	HarvbotArm.cpp										 \
    HarvbotArm2.cpp										 \
    HarvbotArm2Gripper.cpp								 \
    Cameras/HarvbotCamera.cpp							 \
    Cameras/HarvbotFrame.cpp							 \
    HarvbotGripper.cpp									 \
    Cameras/HarvbotOpenCvFrame.cpp						 \
    Cameras/HarvbotOpenCvCamera.cpp						 \
    HarvbotArm2GripperBacketObserver.cpp				 \
    HarvbotGripperObserver.cpp							 \
    Recognition/HarvbotOpenCvColorRecognizer.cpp		 \
    Recognition/HarvbotRecognizer.cpp					 \
    Native/ADXL345Pi.cpp								 \
    Native/RF24/RF24.cpp								 \
    Native/RF24/utility/wiringPi/spi.cpp				 \
    Native/VL53L0XPi.cpp								 \
    Rangefinder/HarvbotLaser.cpp						 \
    Rangefinder/HarvbotLaserRangefinder.cpp 			 \
    Rangefinder/HarvbotRangefinder.cpp					 \
    Rangefinder/HarvbotVL53L0XRangefinder.cpp 			 \
    Visualization/HarvbotArm2StateVisualizer.cpp		 \
    Steppers/Stoppers/HarvbotTerminalStopper.cpp		 \
    Steppers/Stoppers/HarvbotStepperStopper.cpp			 \
    Nodes/HarvbotArmStepperCircleNode.cpp				 \
    Nodes/HarvbotArmStepperScrewNode.cpp				 \
    Nodes/HarvbotArmCircleNode.cpp						 \
    HarvbotArmFactory.cpp								 \
	Nodes/HarvbotArmNode.cpp							 \
    Protocols/HarvbotArmProtocol.cpp					 \
    Nodes/HarvbotArmScrewNode.cpp						 \
    Protocols/HarvbotArmSerialProtocol.cpp				 \
    Steppers/HarvbotStepper.cpp							 \
    Steppers/HarvbotTerminableStepper.cpp
	
HEADERS = Accelerometers/HarvbotAccelerometer.cpp		 \
	Accelerometers/HarvbotADXL345PiI2CAccelerometer.cpp	 \
	HarvbotArm.cpp										 \
    HarvbotArm2.cpp										 \
    HarvbotArm2Gripper.cpp								 \
    Cameras/HarvbotCamera.cpp							 \
    Cameras/HarvbotFrame.cpp							 \
    HarvbotGripper.cpp									 \
    Cameras/HarvbotOpenCvFrame.cpp						 \
    Cameras/HarvbotOpenCvCamera.cpp						 \
    HarvbotArm2GripperBacketObserver.cpp				 \
    HarvbotGripperObserver.cpp							 \
    Recognition/HarvbotOpenCvColorRecognizer.cpp		 \
    Recognition/HarvbotRecognizer.cpp					 \
    Native/ADXL345Pi.cpp								 \
    Native/RF24/RF24.cpp								 \
    Native/RF24/utility/wiringPi/spi.cpp				 \
    Native/VL53L0XPi.cpp								 \
    Rangefinder/HarvbotLaser.cpp						 \
    Rangefinder/HarvbotLaserRangefinder.cpp 			 \
    Rangefinder/HarvbotRangefinder.cpp					 \
    Rangefinder/HarvbotVL53L0XRangefinder.cpp 			 \
    Visualization/HarvbotArm2StateVisualizer.cpp		 \
    Steppers/Stoppers/HarvbotTerminalStopper.cpp		 \
    Steppers/Stoppers/HarvbotStepperStopper.cpp			 \
    Nodes/HarvbotArmStepperCircleNode.cpp				 \
    Nodes/HarvbotArmStepperScrewNode.cpp				 \
    Nodes/HarvbotArmCircleNode.cpp						 \
    HarvbotArmFactory.cpp								 \
	Nodes/HarvbotArmNode.cpp							 \
    Protocols/HarvbotArmProtocol.cpp					 \
    Nodes/HarvbotArmScrewNode.cpp						 \
    Protocols/HarvbotArmSerialProtocol.cpp				 \
    Steppers/HarvbotStepper.cpp							 \
    Steppers/HarvbotTerminableStepper.cpp

OBJ	= $(SRC:.cpp=.o)

build:
	echo [Compile] $<
	$(CC) $(CFLAGS) main.cpp $(SRC) $(INCLUDE) $(LDLIBS)

.cpp.o:
	echo [Compile] $<
	$(CC) $(CFLAGS) main.cpp $(SRC) $(INCLUDE) $(LDLIBS) -o gripper
	
gipper: $(SRC)
		$(CC) -o gripper main.cpp $(SRC)
   
clean:
		rm -f *.o core

rebuild: clean build

