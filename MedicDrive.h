#ifndef MEDIC_DRIVE_H
#define MEDIC_DRIVE_H
#include "WPILib.h"
#include "MedicMacros.h"
#include "MedicOperatorInterface.h"

class MedicDrive
{
public:
	MedicDrive(MedicOperatorInterface *opInt = NULL);
	//MedicDrive();
	~MedicDrive();

	/*
	 * bool shift
	 * Parameters: UINT8 highButton - high gear button
	 * 			   UINT8 lowButton - low gear button
	 * Summary: Sets the shift in high or low gear. 
	 */
	bool shift(UINT8 highButton, UINT8 lowButton);
	
	/*
	 * void setLinVelocity 
	 * Parameters: double linVal - the linear value
	 * Summary: Sets Deadzones and neutral zone.
	 */
	void setLinVelocity(double linVal);
	
	double getLinVelocity();

	/*
	 * void setTurnSpeed
	 * Parameters: double turn - regular turning speed
	 * 		       bool turboButton - is the turbo switched on?
	 * Summary: Sets the turning speed, and/or off.
	 */
	void setTurnSpeed(double turn, bool turboButton);		
	
	double getTurnSpeed();	
	
	/*
	 * void drive
	 * Parameters: N/A
	 * Summary: Sets the speed of the wheels seperately.
	 */
	void drive();
	
	double getJagCmd(bool leftSide);
	
	/*
	 * double getVelocity
	 * Parameters: N/A
	 * Summary: Returns the linear velocity.
	 */
	double getVelocity();		

	/*
	 * double reduceTurn
	 * Parameters: double reduceBy - value to reduce turn speed by
	 * Summary: Reduces the turning speed.
	 */
	double reduceTurn(double reduceBy);
	
	void setLeftMotors(double velocity);
	void setRightMotors(double velocity);
	
	void moveLeftEncoder(double target, double speed);
	void moveRightEncoder(double target, double speed);
	
	void autoLinear(double target, double speed);
	void autoTurn(double target, double speed);
	void autoSwivelTurn(double target, double speed, bool leftSide);
	
	void timeLinear(double distance, double speed, double targetTime_ms);
	void timeTurn(double distance, double speed, double targetTime_ms);
	void timeSwivel(double distance, double speed, double targetTime_ms);
	
	void timeLinear(double speed, double targetTime_ms);
	void timeTurn(double speed, double targetTime_ms);
	void timeSwivel(double speed, double targetTime_ms);
	
	void resetAtTarget();
	void resetTimers();
	
	DoubleSolenoid *shifter;

	Encoder *leftEncoder;
	Encoder *rightEncoder;
	double currentTicksLeft ; //average of encoder values; used in auton
	double targetTicksLeft;  //target encoder values; used in auton
	double deltaTicksLeft;   //change in encoder values; used in auton
	double errorLeft;        //the offset of target ticks relative to current ticks; used in auton
	
	double currentTicksRight; //average of encoder values; used in auton
	double targetTicksRight;  //target encoder values; used in auton
	double deltaTicksRight;   //change in encoder values; used in auton
	double errorRight;        //the offset of target ticks relative to current ticks; used in auton
	
	double currentTicksLinear ; //average of encoder values; used in auton
	double targetTicksLinear;  //target encoder values; used in auton
	double deltaTicksLinear;   //change in encoder values; used in auton
	double errorLinear;        //the offset of target ticks relative to current ticks; used in auton

	double currentTicksTurn; //average of encoder values; used in auton
	double targetTicksTurn;  //target encoder values; used in auton
	double deltaTicksTurn;   //change in encoder values; used in auton
	double errorTurn;        //the offset of target ticks relative to current ticks; used in auton

	double currentTicksSwivelTurn; //average of encoder values; used in auton
	double targetTicksSwivelTurn;  //target encoder values; used in auton
	double deltaTicksSwivelTurn;   //change in encoder values; used in auton
	double errorSwivelTurn;        //the offset of target ticks relative to current ticks; used in auton
	
	Timer *timer;
	
	double currentTimeLinear;
	double targetTimeLinear;
	double deltaTimeLinear;
	double errorTimeLinear;
	
	double currentTimeTurn;
	double targetTimeTurn;
	double deltaTimeTurn;
	double errorTimeTurn;
	
	double currentTimeSwivel;
	double targetTimeSwivel;
	double deltaTimeSwivel;
	double errorTimeSwivel;
	
	bool isAtLeftTarget;
	bool isAtRightTarget;
	bool isAtLinearTarget;
	bool isAtTurnTarget;
	bool isAtSwivelTurnTarget;
	
	bool isAtTimeLinearTarget;
	bool isAtTimeTurnTarget;
	bool isAtTimeSwivelTarget;
	
private:

	Talon *frontLeftMotor;
	Talon *rearLeftMotor;
	Talon *frontRightMotor;
	Talon *rearRightMotor;
	
	MedicOperatorInterface *oi;
	
	double linearVelocity; 
	double turnSpeed; 
	
	double leftCmd;
	double rightCmd;
	
};
#endif
