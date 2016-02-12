#ifndef Stepper-A4988_h
#define Stepper-A4988_h

#include "Arduino.h"
#include "Stepper-A4988.h"

class A4988
{
	typedef enum StepMode
	{
		NONE,
		FULL,
		HALF,
		QUARTER,
		EIGTHTH,
		SIXTEENTH
	};
	
	public:
		A4988(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin);
		A4988(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin, unsigned int stepsPerRound, unsigned int stepDelay);
		A4988(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin, uint8_t ms1Pin, uint8_t ms2Pin, uint8_t ms3Pin);
		A4988(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin, uint8_t ms1Pin, uint8_t ms2Pin, uint8_t ms3Pin, unsigned int stepsPerRound, unsigned int stepDelay);
		void setStepMode(StepMode mode);
		void doStep();
		void enable();
		void disable();
		boolean isEnabled();
		void up();
		void down();
		void setStepsPerRound(double stepAngle);
		void setStepDelay(unsigned int delayMicroSeconds);
		void setRPM(unsigned int rpm);	
	private:
		unsigned int _stepsPerRound;
		uint8_t _stepPin;
		uint8_t _directionPin;
		uint8_t _enablePin;
		uint8_t _ms1Pin;
		uint8_t _ms2Pin;
		uint8_t _ms3Pin;
		unsigned int _stepDelay; 
		unsigned int _initDelay;
		unsigned int _minDelay; 
		unsigned int _directionChangeDelay;
		boolean _moveUp;
		boolean _isEnabled;
		boolean _isNewRequest;	
		void initPinModes();
		void setFullStepMode();
		void setHalfStepMode();
		void setQuarterStepMode();
		void setEigThthStepMode();
		void setSixteenthStepMode();
};

#endif

