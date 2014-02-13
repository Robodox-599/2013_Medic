#ifndef MEDIC_SHOOTER_H
#define MEDIC_SHOOTER_H
#include "WPILib.h"
#include "MedicMacros.h"
#include "MedicRPMSource.h"
#include "MedicPIDOutput.h"

class MedicShooter
{
public:

	MedicShooter();
	MedicShooter(UINT8 shooterWheelVictorChannel, UINT8 shooterMiniWheelVictorChannel, 
				 UINT32 shooterWheelIRChannel,UINT8 elevatorVictorChannel, UINT8 anglePotChannel
				 , UINT8 pnuemFeederSlot, UINT8 feederSolA, UINT8 feederSolB);
				 
	~MedicShooter();
	
	/*
	 * void shootDisc
	 * Parameters: N/A
	 * Summary: Calls setVictors function.
	 */
	void shootDisc();	
	
	/*
	 * double getVelocity
	 * Parameters: N/A
	 * Summary: returns the target velocity.
	 */
	double getVelocity();
	
	/*
	 * void setTarget
	 * Parameters: rpm - the RPM of the shooter motor
	 * Summary: Sets the RPM.
	 */
	void setVelocity(double input);
	void setMiniWheelVelocity(double input);
	
	/*
	 * void setVictors
	 * Parameters: N/A
	 * Summary: sets target velocity to shooter wheel
	 */
	void setVictors();
	
	/*
	 * bool isUpToSpeed
	 * Parameters: N/A
	 * Summary: checks if current velocity has reached target velocity
	 */
	bool isUpToSpeed();
	
	/*
	 * void setTarget
	 * Parameters: rpm - the RPM of the shooter motor
	 * Summary: Sets the RPM.
	 */
	void setVelocityAuto(double targetRPM);
	
	double getShooterRPM();

	
	void shooterElevationControl(bool goal1, bool goal2, bool goal3, double speed, bool fastUp, bool fastDown,
								 bool slowUp, bool slowDown, bool autonGoal, double autonGoalTarget);
	void writeShooterAngle(double input);

	/*
	 * void feedShooter
	 * Parameters: bool feed - do we feed the shooter? 
	 * Summary: Feeds a disc from the mag to the shooter.
	 */
	void feedShooter(bool feed);
	void feedShooterAuto(bool feed, bool frisbeeChambered);
	bool shooterStowed();

	void setCameraAngle(bool up);
	
	bool shooterFired;
	DigitalInput *shooterBottomLimit;
	DigitalInput *shooterTopLimit;

	double targetVelocity;
	double targetMiniWheelVelocity;
	DoubleSolenoid *feeder;
		
private:	
	Victor *shooterWheel;
	Victor *shooterMiniWheel;
	Victor *elevatorMotor;
	

	Counter *shooterIRCount;
	DigitalInput *shooterWheelIR;
	



	DoubleSolenoid *cameraAngle;

	DigitalInput *feederReset;
	Timer *currentTime;
	
	double velocity;
	double rpm;
	double degrees;
	int discCount;
};
#endif

