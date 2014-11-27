#include "MedicDrive.h"
#include "MedicOperatorInterface.h"
#include "MedicMacros.h"

int step;

class Medic: public IterativeRobot
{
	MedicDrive *drive;
	Compressor *comp599;
	MedicOperatorInterface *oi;
	Solenoid *rpmSensor;
	DigitalInput *rpmIRSensor;


	DigitalInput *shooterBottomLimit;
	DigitalInput *shooterTopLimit;

	
	Timer *timer;

public:

	Medic()
	{

		oi = new MedicOperatorInterface();
		drive = new MedicDrive();
		comp599 = new Compressor(1, 1, 1, 1);//TODO: add real values
		rpmSensor = new Solenoid(PNEUMATICS_24V_SLOT, 5);
		rpmIRSensor = new DigitalInput(1, SHOOTER_WHEEL_IR_CHANNEL);

		oi->dashboard->init();
		comp599->Start();
		timer = new Timer();
	}
	
	void RobotInit()
	{
		
	}
	
	void DisabledInit()
	{
		drive->leftEncoder->Start();
		drive->rightEncoder->Start();		
	}
	
	void AutonomousInit()
	{
		step = 0;
		drive->leftEncoder->Reset();
		drive->rightEncoder->Reset();
	}
	
	void TeleopInit()
	{
		drive->setLinVelocity(0);
		drive->setTurnSpeed(0, false);
		drive->drive();
	}
   
	void TestInit()
	{
		
	}
	
	void DisabledPeriodic()
	{
		step = 0;
		drive->leftEncoder->Reset();
		drive->rightEncoder->Reset();
		smartDashboardPrint();

	}
	
	void AutonomousPeriodic()
	{
		smartDashboardPrint();
	}
	
	void TeleopPeriodic()
	{
		comp599->Start();
		while(IsOperatorControl())
		{
			 teleDrive();
		}
	}
	void TestPeriodic()
	{
		
	}
	
	void teleDrive()
	{
		drive->setLinVelocity(-oi->getDriveJoystick()->GetY(Joystick::kRightHand));
		drive->setTurnSpeed(oi->getDriveJoystick()->GetX(Joystick::kRightHand), oi->getDriveJoystickButton(1));
		drive->drive();
		drive->shift(oi->getDriveJoystickButton(8), oi->getDriveJoystickButton(9));
		if(oi->getDriveJoystickButton(6))
		{
			comp599->Start();
		}
		else if(oi->getDriveJoystickButton(7))
		{
			comp599->Stop();
		}
	}
		
	void smartDashboardPrint()
	{
		oi->dashboard->PutNumber("Linear Velocity", drive->getLinVelocity());
		oi->dashboard->PutNumber("Left Encoder", drive->leftEncoder->Get());
		oi->dashboard->PutNumber("Right Encoder", drive->rightEncoder->Get());
		oi->dashboard->PutNumber("Step", step);
	}
	    		
};

START_ROBOT_CLASS(Medic);
