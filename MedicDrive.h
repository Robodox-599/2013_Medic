#ifndef MEDIC_DRIVE_H
#define MEDIC_DRIVE_H
#include "MedicOperatorInterface.h"

class MedicDrive
{
public:
	MedicDrive(MedicOperatorInterface *opInt = NULL);
	~MedicDrive();

	bool shift(UINT8 highButton, UINT8 lowButton);
	
	void setLinVelocity(double linVal);
	
	double getLinVelocity();

	void setTurnSpeed(double turn, bool turboButton);		
	
	double getTurnSpeed();	
	
	void drive();
		
	double getVelocity();		

	double reduceTurn(double reduceBy);
	
	void setLeftMotors(double velocity);
	void setRightMotors(double velocity);
	
	void moveLeftEncoder(double target, double speed);
	void moveRightEncoder(double target, double speed);
	
	
	DoubleSolenoid *shifter;

	Encoder *leftEncoder;
	Encoder *rightEncoder;
	Timer *timer;
	
private:

	Talon *rightMotor1;
	Talon *rightMotor2;
	Talon *rightMotor3;
	Talon *leftMotor4;
	Talon *leftMotor5;
	Talon *leftMotor6;
	
	MedicOperatorInterface *oi;
	
	double linearVelocity; 
	double turnSpeed; 
	
	double leftCmd;
	double rightCmd;
	
};
#endif
