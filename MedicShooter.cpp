#include "MedicShooter.h"

MedicShooter::MedicShooter()
{
	MedicShooter(SHOOTER_WHEEL_VICTOR_CHANNEL, SHOOTER_MINI_WHEEL_VICTOR_CHANNEL, SHOOTER_WHEEL_IR_CHANNEL,
				ELEVATOR_VICTOR_CHANNEL, ANGLE_POT_CHANNEL
#ifdef NEW_BOT
				, PNEUMATICS_12V_SLOT, FEEDER_SOLENOID_CHANNEL_A, FEEDER_SOLENOID_CHANNEL_B
#endif
				);
}

MedicShooter::MedicShooter(UINT8 shooterWheelVictorChannel, UINT8 shooterMiniWheelVictorChannel, 
						   UINT32 shooterWheelIRChannel,UINT8 elevatorVictorChannel, UINT8 anglePotChannel
#ifdef NEW_BOT
						   , UINT8 pnuemFeederSlot, UINT8 feederSolA, UINT8 feederSolB
#endif
							)
{
	shooterWheel = new Victor(shooterWheelVictorChannel);
	shooterMiniWheel = new Victor(shooterMiniWheelVictorChannel);
	elevatorMotor = new Victor(elevatorVictorChannel);
	
	shooterBottomLimit = new DigitalInput(1, ELEVATION_BOTTOM_LIMIT_CHANNEL);
	shooterTopLimit = new DigitalInput(1, ELEVATION_TOP_LIMIT_CHANNEL);

	shooterWheelIR = new DigitalInput(shooterWheelIRChannel);
	shooterIRCount = new Counter(shooterWheelIR);
//	shooterIRCount = new Counter(new DigitalInput(shooterWheelIRChannel));
//	shooterIRCount = new Counter(1, shooterWheelIRChannel);
	shooterIRCount->Start();
#ifdef NEW_BOT
	feeder = new DoubleSolenoid(pnuemFeederSlot, feederSolA, feederSolB);
	cameraAngle = new DoubleSolenoid(PNEUMATICS_24V_SLOT, 3, 4);
#endif	
	feederReset = new DigitalInput(1, SHOOTER_TRIGGER_CHANNEL);
	currentTime = new Timer();
	currentTime->Start();

	//shooterFired = false;
}

MedicShooter::~MedicShooter()
{
	delete shooterWheel;
	delete shooterMiniWheel;
	delete shooterWheelIR;
	delete shooterIRCount;
	delete elevatorMotor;
#ifdef NEW_BOT
	delete feeder;
	delete cameraAngle;
#endif
	
	shooterWheel = NULL;
	shooterMiniWheel = NULL;
	shooterWheelIR = NULL;
	shooterIRCount = NULL;
	elevatorMotor = NULL;
#ifdef NEW_BOT
	feeder = NULL;
	cameraAngle = NULL;
#endif
}

/*
 * void shootDisc
 * Parameters: N/A
 * Summary: Calls setVictors function.
 */
void MedicShooter::shootDisc()
{
	setVictors();
}

/*
 * double getVelocity
 * Parameters: N/A
 * Summary: returns the target velocity.
 */
double MedicShooter::getVelocity()
{
	return targetVelocity;
}

/*
 * void setTarget
 * Parameters: rpm - the RPM of the shooter motor
 * Summary: Sets the RPM.
 */
void MedicShooter::setVelocityAuto(double targetRPM)
{
//	if(getShooterRPM() < targetRPM)
//	{
//		setVelocity(1.0);
//	}
//	else if(getShooterRPM() >= targetRPM)
//	{
//		setVelocity(.05);
//	}
}

/*
 * void setVelocity
 * Parameters: input - the velocity 
 * Summary: Sets the target velocity to input.
 */
void MedicShooter::setVelocity(double input)
{
	targetVelocity = input;
}

void MedicShooter::setMiniWheelVelocity(double input)
{
	targetMiniWheelVelocity = input;
}

/*
 * void setVictors
 * Parameters: N/A
 * Summary: sets target velocity to shooter wheel
 */
void MedicShooter::setVictors()
{
	shooterWheel->Set(targetVelocity, SYNC_STATE_OFF);//big one
	shooterMiniWheel->Set(targetMiniWheelVelocity, SYNC_STATE_OFF);//little one
}

/*
 * bool isUpToSpeed
 * Parameters: N/A
 * Summary: checks if current velocity has reached target velocity
 */
bool MedicShooter::isUpToSpeed()
{
	if(targetVelocity == velocity)
	{
		return true;
	} 
	else 
	{
		return false;
	}
}

double MedicShooter::getShooterRPM()
{
	return (60/shooterIRCount->GetPeriod()/(250));
}

void MedicShooter::shooterElevationControl(bool goal1, bool goal2, bool goal3, double speed, bool fastUp, 
										   bool fastDown, bool slowUp, bool slowDown, bool autonGoal, double autonGoalTarget)
{
	//Make function use boolean value to either go up or down at a certain rate from
	//joystick button used as source of boolean
//	static bool manualSlew = false;
//	static double error = 0;
//	static double goal = 0;
//	double motorSpeed = 0;
//	double angle = 0;
//	
//	manualSlew = fastUp || fastDown || slowUp || slowDown;
	
//	if(autonGoal)
//	{
//		goal = autonGoalTarget;
//	}
//	else
//	{
//		if(goal1)
//		{
//			goal = GOAL_1;
//		}
//		else if(goal2)
//		{
//			goal = GOAL_2;
//		}
//		else if(goal3)
//		{
//			goal = GOAL_3;
//		}
//	}
//	
//	angle = degrees;
//	error = goal - angle;
//	if(!manualSlew)//TODO:maybe add braking
//	{
//		if(error < -ELEVATION_DEADZONE)
//		{
//			motorSpeed = speed;
//		}
//		else if(error > ELEVATION_DEADZONE) 
//		{
//			motorSpeed = -speed;
//		}
//		else 
//		{
//			motorSpeed = 0;
//		}
//	}// use auto if not manual slew enabled
//	else
//	{
		//Use manual
//		if(fastUp)
//		{
//			motorSpeed = 1;
//		}
//		else if(fastDown)
//		{
//			motorSpeed = -1;
//		}
//		else if(slowUp)
//		{
//			motorSpeed = .25;
//		}
//		else if(slowDown)
//		{
//			motorSpeed = -.25;
//		}
//		//goal =  angle;
//		
//	//}
//	if(shooterTopLimit->Get() == 0 && motorSpeed > 0)
//	{
//		motorSpeed = 0;
//	}
//	if(shooterBottomLimit->Get() == 0 && motorSpeed < 0)
//	{
//		motorSpeed = 0;
//	}
//	
//	//Apply Limit for physical stops
////    if (angle > SHOOTER_MAX_ELEVATION && motorSpeed > 0)
////	{
////		motorSpeed = 0;
////	}
////	else if (angle < SHOOTER_MIN_ELEVATION && motorSpeed < 0)
////	{
////		motorSpeed = 0;
////	}
//    elevatorMotor->Set(motorSpeed, SYNC_STATE_OFF);//In Deadzone(0)	
}

void MedicShooter::writeShooterAngle(double input)
{
	degrees = input;
}


void MedicShooter::feedShooter(bool feed)
{
	static double currTime = 0;
	static double initTime = 0;
	static double elapsedTime = 0;
	static bool init = true;
	static bool buttonHeld = false;
	
	static bool currentFeederReset = false;
	static bool lastFeederReset = false;
	
	currentFeederReset = feederReset->Get();
	currTime = currentTime->Get();
	elapsedTime = currTime - initTime;
	
	if(currentFeederReset && !lastFeederReset)
	{
		shooterFired = true;
	}
	else
	{
		shooterFired = false;
	}
	if((feed && init) || (buttonHeld && init))
	{
		initTime = currTime;
		init = false;
		buttonHeld = false;
	}
	if(feed && !init && elapsedTime > .15)
	{
		buttonHeld = true;
	}
	if(!init)
	{
		if(elapsedTime < TIME_TO_FIRE)
		{
#ifdef NEW_BOT
			feeder->Set(DoubleSolenoid::kForward);
#endif
		}
		else if(!(!currentFeederReset && lastFeederReset))
		{
#ifdef NEW_BOT
			feeder->Set(DoubleSolenoid::kReverse);
#endif
		}
		else if(!currentFeederReset && lastFeederReset)
		{
			init = true;
		}
	}
	lastFeederReset = currentFeederReset;
}

void MedicShooter::feedShooterAuto(bool feed, bool frisbeeChambered)
{
	static double currTime = 0;
	static double initTime = 0;
	static double elapsedTime = 0;
	static bool init = true;
	static bool buttonHeld = false;
	
	static bool currentFeederReset = false;
	static bool lastFeederReset = false;
	
	currentFeederReset = feederReset->Get();
	currTime = currentTime->Get();
	elapsedTime = currTime - initTime;
	
	if(currentFeederReset && !lastFeederReset)
	{
		shooterFired = true;
	}
	else
	{
		shooterFired = false;
	}
	if(feed && init && frisbeeChambered)
	{
		initTime = currTime;
		init = false;
		buttonHeld = false;
	}
	if(feed && !init && elapsedTime > .15)
	{
		buttonHeld = true;
	}
	if(!init)
	{
		if(elapsedTime < TIME_TO_FIRE)
		{
#ifdef NEW_BOT
			feeder->Set(DoubleSolenoid::kForward);
#endif
		}
		else if(!(!currentFeederReset && lastFeederReset))
		{
#ifdef NEW_BOT
			feeder->Set(DoubleSolenoid::kReverse);
#endif
		}
		else if(!currentFeederReset && lastFeederReset)
		{
			init = true;
		}
	}
	lastFeederReset = currentFeederReset;
}

void MedicShooter::setCameraAngle(bool up)
{
#ifdef NEW_BOT
	if(up)
	{
		cameraAngle->Set(DoubleSolenoid::kForward);
	}
	else
	{
		cameraAngle->Set(DoubleSolenoid::kReverse);
	}
#endif
}

bool MedicShooter::shooterStowed()
{
	
	if(degrees < SHOOTER_MIN_ELEVATION || shooterBottomLimit->Get())
	{
		return true;
	}
	else
	{
		return false;
	}
}


