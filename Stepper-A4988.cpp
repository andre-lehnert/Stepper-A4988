#include "Arduino.h"
#include "Stepper-A4988.h"

A4988::A4988(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin)
{
	_stepPin = stepPin;
	_directionPin = directionPin;
	_enablePin = enablePin;
	
	_stepsPerRound = 200;
	_stepDelay = 500;	
	_directionChangeDelay = 100; // ms
	
	initPinModes();
}

A4988::A4988(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin, unsigned int stepsPerRound, unsigned int stepDelay)
{
	_stepPin = stepPin;
	_directionPin = directionPin;
	_enablePin = enablePin;
	
	_stepsPerRound = stepsPerRound;
	_stepDelay = stepDelay;
	_directionChangeDelay = 100; // ms

	initPinModes();
	
	disable();
}

A4988::A4988(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin, uint8_t ms1Pin, uint8_t ms2Pin, uint8_t ms3Pin)
{
	_stepPin = stepPin;
	_directionPin = directionPin;
	_enablePin = enablePin;
	
	_ms1Pin = ms1Pin;
	_ms2Pin = ms2Pin;
	_ms3Pin = ms3Pin;
	
	_stepsPerRound = 200;
	_stepDelay = 500;
	_directionChangeDelay = 100; // ms
	
	initPinModes();
	
	disable();
}

A4988::A4988(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin, uint8_t ms1Pin, uint8_t ms2Pin, uint8_t ms3Pin, unsigned int stepsPerRound, unsigned int stepDelay)
{
	_stepPin = stepPin;
	_directionPin = directionPin;
	_enablePin = enablePin;
	
	_ms1Pin = ms1Pin;
	_ms2Pin = ms2Pin;
	_ms3Pin = ms3Pin;
	
	_stepsPerRound = stepsPerRound;
	_stepDelay = stepDelay;
	_directionChangeDelay = 100; // ms
	
	initPinModes();
	
	disable();
}

/*
 * MS PINs Methods
 * Step resolution
 */
void A4988::setStepMode(StepMode mode)
{
	switch(mode) {
      case FULL: setFullStepMode(); break;
      case HALF: setHalfStepMode(); break;
      case QUARTER: setQuarterStepMode(); break;
      case EIGTHTH: setEigThthStepMode(); break;
      case SIXTEENTH: setSixteenthStepMode(); break;
      
      default:
        setFullStepMode();
    }
}

void A4988::doStep()
{
	digitalWrite(_stepPin,HIGH); 
	delayMicroseconds(_stepDelay); 
	digitalWrite(_stepPin,LOW); 
	delayMicroseconds(_stepDelay); 
}

void A4988::enable()
{
	digitalWrite(_enablePin,LOW); 
	_isEnabled = true;
}

void A4988::disable()
{
	digitalWrite(_enablePin,HIGH); 
	_isEnabled = false;
}

boolean A4988::isEnabled()
{	
	return _isEnabled;
}

void A4988::up()
{
	_moveUp = true;
	disable();
	digitalWrite(_directionPin,LOW);
	delay(_directionChangeDelay);
	enable();
	delay(_directionChangeDelay);
}

void A4988::down()
{
	_moveUp = false;
	disable();
	digitalWrite(_directionPin,HIGH);
	delay(_directionChangeDelay);
	enable();
	delay(_directionChangeDelay);
}

void A4988::setStepsPerRound(double stepAngle)
{
	_stepsPerRound = (360 / stepAngle);
}

void A4988::setStepDelay(unsigned int delayMicroSeconds)
{
	_stepDelay = delayMicroSeconds;
}

void A4988::setRPM(unsigned int rpm)
{
	long minute = 60000000; // MicroSeconds  
	long stepsPerMinute = rpm * _stepsPerRound;

	// Delay between steps
	// stepDelay > minimum delay 
	_stepDelay = (minute / stepsPerMinute) < _minDelay ? _minDelay : (minute / stepsPerMinute); // MicroSeconds
}









void A4988::initPinModes()
{
	if (_stepPin >= 2) { pinMode(_stepPin,OUTPUT); digitalWrite(_stepPin,LOW); }
	if (_directionPin >= 2) { pinMode(_directionPin,OUTPUT); digitalWrite(_directionPin,LOW); }
	if (_enablePin >= 2) { pinMode(_enablePin,OUTPUT); digitalWrite(_enablePin,LOW); }
	if (_ms1Pin >= 2) { pinMode(_ms1Pin,OUTPUT); digitalWrite(_ms1Pin,LOW); }
	if (_ms2Pin >= 2) { pinMode(_ms2Pin,OUTPUT); digitalWrite(_ms2Pin,LOW); }
	if (_ms3Pin >= 2) { pinMode(_ms3Pin,OUTPUT); digitalWrite(_ms3Pin,LOW); }
}

void A4988::setFullStepMode()
{
	digitalWrite(_ms1Pin,LOW);
	digitalWrite(_ms2Pin,LOW);
	digitalWrite(_ms3Pin,LOW);
}

void A4988::setHalfStepMode()
{
	digitalWrite(_ms1Pin,HIGH);
	digitalWrite(_ms2Pin,LOW);
	digitalWrite(_ms3Pin,LOW);
}

void A4988::setQuarterStepMode()
{
	digitalWrite(_ms1Pin,LOW);
	digitalWrite(_ms2Pin,HIGH);
	digitalWrite(_ms3Pin,LOW);
}

void A4988::setEigThthStepMode()
{
	digitalWrite(_ms1Pin,HIGH);
	digitalWrite(_ms2Pin,HIGH);
	digitalWrite(_ms3Pin,LOW);
}

void A4988::setSixteenthStepMode()
{
	digitalWrite(_ms1Pin,HIGH);
	digitalWrite(_ms2Pin,HIGH);
	digitalWrite(_ms3Pin,HIGH);
}
