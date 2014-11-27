#include "MedicDrive.h"

MedicDrive::MedicDrive(MedicOperatorInterface *opInt)
{
	if(opInt) oi = opInt;
	linearVelocity = 0;
	turnSpeed = 0;

	shifter = new DoubleSolenoid(PNEUMATICS_24V_SLOT, 1, 2); //PNEUMATICS_BUMPER_SLOT, SHIFTER_SOLENOID_CHANNEL_A, SHIFTER_SOLENOID_CHANNEL_B
	shifter->Set(DoubleSolenoid::kReverse);
	
	rightMotor1 = new Talon(DRIVE_RIGHT_MOTOR1_CHANNEL);   
	rightMotor2 = new Talon(DRIVE_RIGHT_MOTOR2_CHANNEL);   
	rightMotor3 = new Talon(DRIVE_RIGHT_MOTOR3_CHANNEL);
	leftMotor4 = new Talon(DRIVE_LEFT_MOTOR4_CHANNEL);   
	leftMotor5 = new Talon(DRIVE_LEFT_MOTOR5_CHANNEL); 
	leftMotor6 = new Talon(DRIVE_LEFT_MOTOR6_CHANNEL);

	leftEncoder = new Encoder(LEFT_DRIVE_ENCODER_CHANNEL_A, LEFT_DRIVE_ENCODER_CHANNEL_B, true, Encoder::k1X);
	rightEncoder = new Encoder(RIGHT_DRIVE_ENCODER_CHANNEL_A, RIGHT_DRIVE_ENCODER_CHANNEL_B, false, Encoder::k1X);
	
	timer = new Timer();
}

MedicDrive::~MedicDrive()
{
	 delete shifter;
	 delete rightMotor1;
	 delete rightMotor2;
	 delete rightMotor3;
	 delete leftMotor4;
	 delete leftMotor5;
	 delete leftMotor6;
	 delete timer;
	 
	 shifter = NULL;
	 rightMotor1 = NULL;
	 rightMotor2 = NULL;
	 rightMotor3 = NULL;
	 leftMotor4 = NULL;
	 leftMotor5 = NULL;
	 leftMotor6 = NULL;
	 timer = NULL;
}

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


double MedicDrive::reduceTurn(double reduceBy)
{
	return turnSpeed * reduceBy;
}

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
	leftMotor4->Set(-velocity, SYNC_STATE_OFF);
	leftMotor5->Set(-velocity, SYNC_STATE_OFF);
	leftMotor6->Set(-velocity, SYNC_STATE_OFF);
}

void MedicDrive::setRightMotors(double velocity)
{
	rightMotor1->Set(-velocity, SYNC_STATE_OFF);
	rightMotor2->Set(-velocity, SYNC_STATE_OFF);
	rightMotor3->Set(-velocity, SYNC_STATE_OFF);
}

void MedicDrive::drive()
{
	leftCmd = linearVelocity + turnSpeed;
	rightCmd = linearVelocity - turnSpeed;
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}

double MedicDrive::getVelocity()
{
	return linearVelocity;
}
