#include "MedicDrive.h"

MedicDrive::MedicDrive(MedicOperatorInterface *opInt)
{
	if(opInt) oi = opInt;
	linearVelocity = 0;
	turnSpeed = 0;

	isAtLeftTarget = false;
	isAtRightTarget = false;
	isAtLinearTarget = false;
	isAtTurnTarget = false;
	isAtSwivelTurnTarget = false;
	
	isAtTimeLinearTarget = false;
	isAtTimeTurnTarget = false;
	isAtTimeSwivelTarget = false;
	
	currentTicksLeft = 0;//average of encoder values; used in auton
	targetTicksLeft = 0;  //target encoder values; used in auton
	deltaTicksLeft = 0;   //change in encoder values; used in auton
	errorLeft = 0;        //the offset of target ticks relative to current ticks; used in auton
	
	currentTicksRight = 0; //average of encoder values; used in auton
	targetTicksRight = 0;  //target encoder values; used in auton
	deltaTicksRight = 0;   //change in encoder values; used in auton
	errorRight = 0;        //the offset of target ticks relative to current ticks; used in auton
	
	currentTicksLinear = 0; //average of encoder values; used in auton
	targetTicksLinear = 0;  //target encoder values; used in auton
	deltaTicksLinear = 0;   //change in encoder values; used in auton
	errorLinear = 0;        //the offset of target ticks relative to current ticks; used in auton

	currentTicksTurn = 0; //average of encoder values; used in auton
	targetTicksTurn = 0;  //target encoder values; used in auton
	deltaTicksTurn = 0;   //change in encoder values; used in auton
	errorTurn = 0;        //the offset of target ticks relative to current ticks; used in auton

	currentTicksSwivelTurn = 0; //average of encoder values; used in auton
	targetTicksSwivelTurn = 0;  //target encoder values; used in auton
	deltaTicksSwivelTurn = 0;   //change in encoder values; used in auton
	errorSwivelTurn = 0;        //the offset of target ticks relative to current ticks; used in auton

	shifter = new DoubleSolenoid(PNEUMATICS_24V_SLOT, 1, 2); //PNEUMATICS_BUMPER_SLOT, SHIFTER_SOLENOID_CHANNEL_A, SHIFTER_SOLENOID_CHANNEL_B
	shifter->Set(DoubleSolenoid::kReverse);
	
	frontLeftMotor = new Talon(1, DRIVE_FRONT_LEFT_MOTOR_CHANNEL);   
	rearLeftMotor = new Talon(1, DRIVE_REAR_LEFT_MOTOR_CHANNEL);   
	frontRightMotor = new Talon(1, DRIVE_FRONT_RIGHT_MOTOR_CHANNEL); 
	rearRightMotor = new Talon(1, DRIVE_REAR_RIGHT_MOTOR_CHANNEL);

	leftEncoder = new Encoder(LEFT_DRIVE_ENCODER_CHANNEL_A, LEFT_DRIVE_ENCODER_CHANNEL_B, true, Encoder::k1X);
	rightEncoder = new Encoder(RIGHT_DRIVE_ENCODER_CHANNEL_A, RIGHT_DRIVE_ENCODER_CHANNEL_B, false, Encoder::k1X);
	
	timer = new Timer();
	
	currentTimeLinear = 0;
	targetTimeLinear = 0;
	deltaTimeLinear = 0;
	errorTimeLinear = 0;
	
	currentTimeTurn = 0;
	targetTimeTurn = 0;
	deltaTimeTurn = 0;
	errorTimeTurn = 0;
	
	currentTimeSwivel = 0;
	targetTimeSwivel = 0;
	deltaTimeSwivel = 0;
	errorTimeSwivel = 0;
	
}

MedicDrive::~MedicDrive()
{
	 delete shifter;
	 delete frontLeftMotor;
	 delete rearLeftMotor;
	 delete frontRightMotor;
	 delete rearRightMotor;
	 delete timer;
	 
	 shifter = NULL;
	 frontLeftMotor = NULL;
	 rearLeftMotor = NULL;
	 frontRightMotor = NULL;
	 rearRightMotor = NULL;
	 timer = NULL;
}

/*
 * bool shift
 * Parameters: UINT8 highButton - high gear button
 * 			   UINT8 lowButton - low gear button
 * Summary: Sets the shift in high or low gear. 
 */
bool MedicDrive::shift(UINT8 highButton, UINT8 lowButton)
{
	 static bool lastGearWasHi = true;
	    
	    if(lowButton)
	    {
	        shifter->Set(DoubleSolenoid::kForward);
	        lastGearWasHi = false;
	    }
	    else if(highButton)
	    {
	        shifter->Set(DoubleSolenoid::kReverse);
	        lastGearWasHi = true;
	    }
	    
	    return lastGearWasHi;	
}

/*
 * void setLinVelocity 
 * Parameters: double linVal - the linear value
 * Summary: Sets Deadzones and neutral zone.
 */
void MedicDrive::setLinVelocity(double linVal) 
{
	if(linVal > .1) //DEADZONE
	{
		linearVelocity = linVal;
	}
	else if(linVal < -.1) //DEADZONE
	{
		linearVelocity = linVal;
	}
	else 
	{
		linearVelocity = 0; //NEUTRAL
	}
	
}

double MedicDrive::getLinVelocity()
{
	return linearVelocity;
}

/*
 * double reduceTurn
 * Parameters: double reduceBy - value to reduce turn speed by
 * Summary: Reduces the turning speed.
 */
double MedicDrive::reduceTurn(double reduceBy)
{
	return turnSpeed * reduceBy;
}

/*
 * void setTurnSpeed
 * Parameters: double turn - regular turning speed
 * 		       bool turboButton - is the turbo switched on?
 * Summary: Sets the turning speed, and/or off.
 */
void MedicDrive::setTurnSpeed(double turn, bool turboButton)
{
	if((turn > .1 && !turboButton) || (turn < -.1 && !turboButton)) //DEADZONE
	{
		turnSpeed = turn * REDUCTION;
	}
	if(turn < .1 && turn > -.1) //DEADZONE
	{
		turnSpeed = 0; //NEUTRAL;
	}
	if((turn > .1 && turboButton) || (turn < -.1 && turboButton)) //DEADZONE
	{
		turnSpeed = turn;
	}
}

double MedicDrive::getTurnSpeed()
{
	return turnSpeed;
}

void MedicDrive::setLeftMotors(double velocity)
{
	frontLeftMotor->Set(-velocity, SYNC_STATE_OFF);
	rearLeftMotor->Set(-velocity, SYNC_STATE_OFF);
		
}

void MedicDrive::setRightMotors(double velocity)
{
	frontRightMotor->Set(velocity, SYNC_STATE_OFF); 
	rearRightMotor->Set(velocity, SYNC_STATE_OFF); 
}

/*
 * void drive
 * Parameters: N/A
 * Summary: Sets the speed of the wheels seperately.
 */
void MedicDrive::drive()
{
	leftCmd = linearVelocity + turnSpeed;
	rightCmd = linearVelocity - turnSpeed;
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}

void MedicDrive::moveLeftEncoder(double target, double speed)
{
	static bool init = true;
	static double initTicks = 0;
	
	currentTicksLeft = leftEncoder->Get();
	
	if(init)
	{
		initTicks = currentTicksLeft;
		targetTicksLeft = target;
		init = false;
	}
	else
	{
		deltaTicksLeft = currentTicksLeft - initTicks;
		errorLeft = targetTicksLeft - deltaTicksLeft;
		if(errorLeft < 0 - TICKS_DEADZONE)
		{
			setLeftMotors(speed);
			isAtLeftTarget = false;
		}
		else if(errorRight > 0 + TICKS_DEADZONE)
		{
			setLeftMotors(-speed);
			isAtLeftTarget = false;
		}
		else
		{
			setLeftMotors(0);
			init = true;
			isAtLeftTarget = true;
		}
		if(isAtLeftTarget)
		{
			setLeftMotors(0);
		}
	}
	
}

void MedicDrive::moveRightEncoder(double target, double speed)
{
	static bool init = true;
	static double initTicks = 0;
	
	currentTicksRight = rightEncoder->Get();
	
	if(init)
	{
		initTicks = currentTicksRight;
		targetTicksRight = target;
		init = false;
	}
	else
	{
		deltaTicksRight = currentTicksRight - initTicks;
		errorRight = targetTicksRight - deltaTicksRight;
		if(errorRight < 0 - TICKS_DEADZONE)
		{
			setRightMotors(speed);
			isAtRightTarget = false;
		}
		else if(errorRight > 0 + TICKS_DEADZONE)
		{
			setRightMotors(-speed);
			isAtRightTarget = false;
		}
		else
		{
			setRightMotors(0);
			init = true;
			isAtRightTarget = true;
		}
		if(isAtRightTarget)
		{
			setRightMotors(0);
		}
	}
	
}

void MedicDrive::autoLinear(double target, double speed)
{
		targetTicksLinear = target / INCHES_PER_TICK;
		moveLeftEncoder(-targetTicksLinear, speed);
		moveRightEncoder(targetTicksLinear, -speed);
		if(!isAtLeftTarget && !isAtRightTarget)
		{
			isAtLinearTarget = false;
		}
		else
		{
			isAtLinearTarget = true;
			setLeftMotors(0);
			setRightMotors(0);
		}
		

}
void MedicDrive::autoTurn(double target, double speed)
{
		targetTicksTurn = target * TICKS_PER_DEGREE;
		moveLeftEncoder(targetTicksTurn, -speed);
		moveRightEncoder(-targetTicksTurn, -speed);
		if(!isAtLeftTarget && !isAtRightTarget)
		{
			isAtTurnTarget = false;
		}
		else
		{
			isAtTurnTarget = true;
			setLeftMotors(0);
			setRightMotors(0);
		}
}

void MedicDrive::timeLinear(double speed, double targetTime_ms)
{
	static bool init = true;
	static double initTime = 0;
	
	currentTimeLinear = timer->Get() * 1000; //convert to milliseconds
		
	if(init)
	{
		initTime = currentTimeLinear;
		targetTimeLinear = targetTime_ms;	
		timer->Start();
		init = false;
	}
	else
	{
		deltaTimeLinear = currentTimeLinear - initTime;
		errorTimeLinear = targetTimeLinear - deltaTimeLinear;
		
		if(errorTimeLinear > 0)
		{
			setRightMotors(speed * BATTERY_COMPENSATION);
			setLeftMotors(speed * BATTERY_COMPENSATION);
			isAtTimeLinearTarget = false;
		}
		else if(errorTimeLinear <= 0)
		{
			timer->Stop();
			setRightMotors(0);
			setLeftMotors(0);
			//resetTimers();
			isAtTimeLinearTarget = true;
		}
		
	}
}

void MedicDrive::timeTurn(double speed, double targetTime_ms)
{
	
}

void MedicDrive::timeLinear(double distance, double speed, double targetTime_ms)
{
	
}

void MedicDrive::timeTurn(double distance, double speed, double targetTime_ms)
{
	
}

void MedicDrive::resetAtTarget()
{
	isAtLeftTarget = false;
	isAtRightTarget = false;
	isAtLinearTarget = false;
	isAtTurnTarget = false;
	isAtSwivelTurnTarget = false;
	isAtTimeLinearTarget = false;
	isAtTimeTurnTarget = false;
	isAtTimeSwivelTarget = false;
}

void MedicDrive::resetTimers()
{
	currentTimeLinear = 0;
	targetTimeLinear = 0;
	deltaTimeLinear = 0;
	errorTimeLinear = 0;
	
	currentTimeTurn = 0;
	targetTimeTurn = 0;
	deltaTimeTurn = 0;
	errorTimeTurn = 0;
}

/*
 * double getVelocity
 * Parameters: N/A
 * Summary: Returns the linear velocity.
 */
double MedicDrive::getVelocity()
{
	return linearVelocity;
}
