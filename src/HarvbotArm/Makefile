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
    Nodes/HarvbotArmStepperLinearNode.cpp				 \
    Nodes/HarvbotArmCircleNode.cpp						 \
    HarvbotArmFactory.cpp								 \
	Nodes/HarvbotArmNode.cpp							 \
    Nodes/HarvbotArmLinearNode.cpp						 \
    Steppers/HarvbotStepper.cpp							 \
    Steppers/HarvbotTerminableStepper.cpp
	
HEADERS = Accelerometers/HarvbotAccelerometer.h			 \
	Accelerometers/HarvbotADXL345PiI2CAccelerometer.h	 \
	HarvbotArm.h										 \
    HarvbotArm2.h										 \
    HarvbotArm2Gripper.h								 \
    Cameras/HarvbotCamera.h								 \
    Cameras/HarvbotFrame.h								 \
    HarvbotGripper.h									 \
    Cameras/HarvbotOpenCvFrame.h						 \
    Cameras/HarvbotOpenCvCamera.h						 \
    HarvbotArm2GripperBacketObserver.h					 \
    HarvbotGripperObserver.h							 \
    Recognition/HarvbotOpenCvColorRecognizer.h			 \
    Recognition/HarvbotRecognizer.h						 \
    Native/ADXL345Pi.h									 \
    Native/RF24/RF24.h									 \
    Native/RF24/utility/wiringPi/spi.h					 \
    Native/VL53L0XPi.hpp								 \
	Native/VL53L0X_defines.hpp							 \
    Rangefinder/HarvbotLaser.h							 \
    Rangefinder/HarvbotLaserRangefinder.h 				 \
    Rangefinder/HarvbotRangefinder.h					 \
    Rangefinder/HarvbotVL53L0XRangefinder.h 			 \
    Visualization/HarvbotArm2StateVisualizer.h			 \
    Steppers/Stoppers/HarvbotTerminalStopper.h			 \
    Steppers/Stoppers/HarvbotStepperStopper.h			 \
    Nodes/HarvbotArmStepperCircleNode.h					 \
    Nodes/HarvbotArmStepperLinearNode.h					 \
    Nodes/HarvbotArmCircleNode.h						 \
    HarvbotArmFactory.h									 \
	Nodes/HarvbotArmNode.h								 \
    Nodes/HarvbotArmLinearNode.h						 \
    Steppers/HarvbotStepper.h							 \
    Steppers/HarvbotTerminableStepper.h

OBJ	= $(SRC:.cpp=.o)

%.o: %.cpp
	echo [Compile] $<
	$(CC) $(CFLAGS) $(INCLUDE) $(LDLIBS) -c $< -o $@

build: $(OBJ)
	echo [Build]
	$(CC) $(CFLAGS) main.cpp $(OBJ) $(HEADERS) $(INCLUDE) $(LDLIBS) -o harvbot-gripper

clean:
		rm -r -f *.o
		rm -r -f */*.o
		rm -r -f */*/*.o

rebuild: clean build

