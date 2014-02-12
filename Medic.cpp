#include "WPILib.h"

#include "MedicDrive.h"
#include "MedicManipulator.h"
#include "MedicOperatorInterface.h"
#include "MedicShooter.h"
#include "MedicPIDOutput.h"
#include "MedicMacros.h"

int step;

double targetVelocity;
double targetMiniWheelVelocity;
//double timerGoal;

class Medic: public IterativeRobot
{
//	MedicShooter *shooter;
	MedicManipulator *manipulator;
	MedicOperatorInterface *oi;
	MedicDrive *drive;
	Compressor *comp599;
	AnalogChannel *pot;
	AnalogChannel *magazineBottomCounter;
	AnalogChannel *spoilerCounter;
	AnalogChannel *intakeCounter;
	AnalogChannel *magazineInputCounter;
	//Counter *shooterIRCount2;
	Victor *elevatorMotor;
	Victor *shooterWheel;
	Victor *shooterMiniWheel;
	DoubleSolenoid *feeder;
	DoubleSolenoid *cameraAngle;
	Solenoid *rpmSensor;
	DigitalInput *rpmIRSensor;


	

	DigitalInput *shooterBottomLimit;
	DigitalInput *shooterTopLimit;

	
	Timer *timer;

public:

	Medic()
	{
#ifdef NEW_BOT
		manipulator = new MedicManipulator( INTAKE_ROLLER_VICTOR_CHANNEL,
											CONVEYER_VICTOR_CHANNEL,
											CLIMBER_SOLENOID_CHANNEL_A,
											CLIMBER_SOLENOID_CHANNEL_B,
											PNEUMATICS_12V_SLOT );
#else
		manipulator = new MedicManipulator(INTAKE_ROLLER_VICTOR_CHANNEL, CONVEYER_VICTOR_CHANNEL);
#endif
		oi = new MedicOperatorInterface();
		drive = new MedicDrive();
		//shooter = new MedicShooter();
		comp599 = new Compressor(1, 1, 1, 1);//TODO: add real values
		pot = new AnalogChannel(1,1);
		magazineBottomCounter = new AnalogChannel(1, 2);
		magazineInputCounter = new AnalogChannel(1, 3);
		spoilerCounter = new AnalogChannel(1, 4);
		intakeCounter = new AnalogChannel(1,5);
		//shooterIRCount2 = new Counter(new DigitalInput(4));
		elevatorMotor = new Victor(8);
		shooterWheel = new Victor(10);
		shooterMiniWheel = new Victor(9);
		feeder = new DoubleSolenoid(2, 5, 6);
		cameraAngle = new DoubleSolenoid(PNEUMATICS_24V_SLOT, 3, 4);
		rpmSensor = new Solenoid(PNEUMATICS_24V_SLOT, 5);
		rpmIRSensor = new DigitalInput(1, SHOOTER_WHEEL_IR_CHANNEL);


		

		shooterBottomLimit = new DigitalInput(1, ELEVATION_BOTTOM_LIMIT_CHANNEL);
		shooterTopLimit = new DigitalInput(1, ELEVATION_TOP_LIMIT_CHANNEL);

		
		oi->dashboard->init();
		comp599->Start();
		timer = new Timer();
		//shooterIRCount2->Start();
		

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
		drive->isAtLinearTarget = false;
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
		drive->isAtTimeLinearTarget = false;
		manipulator->climbPyramid(false);
		smartDashboardPrint();

	}
	
	void AutonomousPeriodic()
	{
		static bool init = true;
		//shoot(true);					//shoot preloads
		
		//drive->autoTurn(55, TURN_SPEED); 
		
		smartDashboardPrint();
			shooterWheel->Set(.95*BATTERY_COMPENSATION);
			shooterMiniWheel->Set(.9*BATTERY_COMPENSATION);
			if(init)
			{
				feeder->Set(DoubleSolenoid::kReverse);
				timer->Start();
				init = false;
			}
				
			if(timer->Get() > 4.5 && timer->Get() < 5)
			{
			feeder->Set(DoubleSolenoid::kForward);
			}
			if(timer->Get() > 5 && timer->Get() < 5.5)
			{
				feeder->Set(DoubleSolenoid::kReverse);
				step++;
			}
			//1 sec pause between shots 1 & 2
			if(timer->Get() > 6.5 && timer->Get() < 7)
			{
			feeder->Set(DoubleSolenoid::kForward);
			}
			if(timer->Get() > 7 && timer->Get() < 7.5)
			{
				feeder->Set(DoubleSolenoid::kReverse);
				step++;
			}
			//1 sec pause between shots 2 & 3
			if(timer->Get() > 8.5 && timer->Get() < 9)
			{
			feeder->Set(DoubleSolenoid::kForward);
			}
			if(timer->Get() > 9 && timer->Get() < 9.5)
			{
				feeder->Set(DoubleSolenoid::kReverse);
				step++;
			}
			
//		if(step == 0)
//		{
//			drive->timeLinear(.25, 3000);//TODO: dummy number
//			if(drive->isAtTimeLinearTarget)
//			{
//			  drive->resetAtTarget();
//			  step++;
//			}
//		}
//		if(step == 1)
//		{
//			drive->autoLinear(90, .25);//TODO: dummy number
//			if(drive->isAtLinearTarget)
//			{
//			drive->resetAtTarget();
//			step++;
//			}
//		}
//		if(step == 2)
//		{
//			drive->autoTurn(45, .25);//TODO: dummy number
//			if(drive->isAtTurnTarget)
//			{
//			drive->resetAtTarget();
//			step++;
//			}
//		}
//
//#ifdef AUTONOMOUS
//		drive->autoTurn(-90, TURN_SPEED); 		
//		drive->autoDrive(1, DRIVE_SPEED);//TODO: dummy number 		//get the weirdly angled discs OF DOOM
//		intake(true);					
//		drive->autoDrive(1, DRIVE_SPEED);//TODO: dummy number 		
//		
//		drive->autoDrive(1, DRIVE_SPEED);//TODO: dummy number 
//		drive->autoTurn(55, TURN_SPEED); 		//aim and then shoot discs of doom 
//		shoot(true);	
//	
//		drive->autoTurn(55, TURN_SPEED); 
//		drive->autoDrive(1, DRIVE_SPEED);//TODO: dummy number 
//		drive->autoTurn(-90, TURN_SPEED); 
//		drive->autoDrive(1, DRIVE_SPEED);//TODO: dummy number 		//get OTHER weirdly angled discs of doom
//		intake(true);	
//		drive->autoDrive(1, DRIVE_SPEED);//TODO: dummy number 
//		
//		drive->autoDrive(1, DRIVE_SPEED);//TODO: dummy number
//		drive->autoTurn(55, TURN_SPEED);			//aim and shoot OTHER weirdly angled discs of doom
//		shoot(true);
//#endif		
		
	}
	
	void TeleopPeriodic()
	{
		comp599->Start();
		while(IsOperatorControl())
		{
			 teleDrive();
//			 intake();
//			 shoot();
//			 shooterWheel->Set(-(-(oi->getManipJoystick()->GetThrottle()+1)/2));
//			 if(((oi->getManipJoystick()->GetThrottle() + 1)/2) > .5)
//			 {
//			 	shooterMiniWheel->Set(.9 * BATTERY_COMPENSATION);
//			 }
//			 else
//			 {
//			 	shooterMiniWheel->Set(0);
//			 }
//			 //climb();
//			 if(oi->getDriveJoystickButton(3))
//			 {
//				 manipulator->climber->Set(DoubleSolenoid::kForward);
//			 }
//			 else if (oi->getDriveJoystickButton(2))
//			 {
//				 manipulator->climber->Set(DoubleSolenoid::kReverse);
//			 }
//		
//			if(oi->getDriveJoystickButton(4))
//			{
//				cameraAngle->Set(DoubleSolenoid::kForward);
//			}
//			else if (oi->getDriveJoystickButton(5))
//			{
//				cameraAngle->Set(DoubleSolenoid::kReverse);
//			}
//			 smartDashboardPrint();

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
	
	void shoot()
	{
//		if(oi->readAutoShootToggle(1))//TODO: Macro goes here
//		{
//			shooter->setVelocityAuto(TARGET_RPM);
//			shooter->setMiniWheelVelocity(.9 * BATTERY_COMPENSATION);
//			shooter->shootDisc();
//		}
//		else
//		{
//			setVelocity(-(oi->getManipJoystick()->GetThrottle()+1)/2);
//			if(((oi->getManipJoystick()->GetThrottle() + 1)/2) > .5)
//			{
//				setMiniWheelVelocity(.9 * BATTERY_COMPENSATION);
//			}
//			else
//			{
//				setMiniWheelVelocity(0);
//			}
//		//	shooter->shootDisc();
//		}
//		shooter->shooterElevationControl(oi->readElevationTarget1(2), oi->readElevationTarget2(3), 
//										 oi->readElevationTarget3(4), .75, oi->getManipJoystickButton(11), 
//										 oi->getManipJoystickButton(10), oi->getManipJoystickButton(6), 
//										 oi->getManipJoystickButton(7), false, 0);
		shooterElevationControl(false, false, false, .75, oi->getManipJoystickButton(11), 
												 oi->getManipJoystickButton(10), oi->getManipJoystickButton(6), 
												 oi->getManipJoystickButton(7), false, 0);
//		shooter->feedShooter(oi->getManipJoystickButton(1));

#ifdef NEW_BOT
		if(oi->getManipJoystickButton(1))
		{
			feeder->Set(DoubleSolenoid::kForward);
		}
		else
		{
			feeder->Set(DoubleSolenoid::kReverse);
		}
//		shooter->writeShooterAngle(pot->GetVoltage());
//		
//		if(oi->getDriveJoystickButton(4))
//		{
//			shooter->setCameraAngle(true);
//		}
//		else if(oi->getDriveJoystickButton(5))
//		{
//			shooter->setCameraAngle(false);
//		}
#endif
	}
	void setVelocity(double input)
	{
		targetVelocity = input;
	}

	void setMiniWheelVelocity(double input)
	{
		targetMiniWheelVelocity = input;
	}

	/*
	 * void setVictors
	 * Parameters: N/A
	 * Summary: sets target velocity to shooter wheel
	 */
	void setVictors()
	{
		shooterWheel->Set(targetVelocity, SYNC_STATE_OFF);//big one
		shooterMiniWheel->Set(targetMiniWheelVelocity, SYNC_STATE_OFF);//little one
	}
	
	void intake()
	{
		if(oi->getDriveJoystickButton(2))//TODO: Macro goes here
		{
			manipulator->intakeDisc(true); // move		
		}
		else
		{
			manipulator->intakeDisc(false); // move
		}
		if(-(-oi->getDriveJoystick()->GetThrottle() + 1)/2 <= 0)
		{
		   manipulator->conveyer(-(-oi->getDriveJoystick()->GetThrottle() + 1)/2);
		}

#ifdef NEW_BOT
		if(oi->getManipJoystickButton(8))
		{
			manipulator->spoiler->Set(DoubleSolenoid::kForward);
		}
		else if(oi->getManipJoystickButton(9))
		{
			manipulator->spoiler->Set(DoubleSolenoid::kReverse);
		}
#endif
	}	
	void shooterElevationControl(bool goal1, bool goal2, bool goal3, double speed, bool fastUp, 
											   bool fastDown, bool slowUp, bool slowDown, bool autonGoal, double autonGoalTarget)
	{
		static float motorSpeed = 0;
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
			if(fastUp)
			{
				motorSpeed = 1;
			}
			else if(fastDown)
			{
				motorSpeed = -1;
			}
			else if(slowUp)
			{
				motorSpeed = .25;
			}
			else if(slowDown)
			{
				motorSpeed = -.25;
			}
			else
			{
				motorSpeed = 0;
			}
			//goal =  angle;
			
		//}
		if(shooterTopLimit->Get() == 0 && motorSpeed > 0)
		{
			motorSpeed = 0;
		}
		if(shooterBottomLimit->Get() == 0 && motorSpeed < 0)
		{
			motorSpeed = 0;
		}
		
		//Apply Limit for physical stops
	//    if (angle > SHOOTER_MAX_ELEVATION && motorSpeed > 0)
	//	{
	//		motorSpeed = 0;
	//	}
	//	else if (angle < SHOOTER_MIN_ELEVATION && motorSpeed < 0)
	//	{
	//		motorSpeed = 0;
	//	}
	    elevatorMotor->Set(motorSpeed, SYNC_STATE_OFF);//In Deadzone(0)	
	}
	
	void intake(bool autonIntake)
	{
		if(autonIntake)
		{
			manipulator->intakeDisc(true); // intake
			manipulator->conveyer(true); // move	
		}
		else
		{
			manipulator->intakeDisc(false); // intake
			manipulator->conveyer(false); // move
		}
	
	}
	
	void climb()
	{
		static bool readyForPistons = false;
	//	if(oi->readClimbSafetyEnable(8))
		//{
			//shooter->shooterElevationControl(false, false, false, .75, false, false, false, false, true, 0);
			//if(shooter->shooterStowed())
			//{
				readyForPistons = true;
			//}
		//}
		if(readyForPistons && oi->getDriveJoystickButton(3))
		{
			manipulator->climbPyramid(true);
		}
		if(oi->getDriveJoystickButton(2))
		{
			manipulator->climbPyramid(false);
		}
		if(oi->readClimbInterlockToggle(10) && oi->getDriveJoystickButton(3))
		{
			manipulator->climbPyramid(true);
			if(oi->getDriveJoystickButton(2))
			{
				manipulator->climbPyramid(false);
			}
		}				
	}	

	void autoAim(double targetX, double targetY)
	{
		if(targetX < 320 - AIM_DEADZONE)
		{
			//turn left
			drive->setTurnSpeed(-.3, false);
			drive->drive();
		}
		else if(targetX > 320 + AIM_DEADZONE)
		{
			//turn right
			drive->setTurnSpeed(.3, false);
			drive->drive();
		}
		else
		{
			//stop
			drive->setTurnSpeed(0, false);
			drive->drive();
		}
		if(targetY < 240 - AIM_DEADZONE)
		{
			//aim down
			drive->setLinVelocity(.3);
			drive->drive();
		}
		else if(targetY > 240 + AIM_DEADZONE)
		{
			//aim up
			drive->setLinVelocity(-.3);
			drive->drive();
		}
		else
		{
			//stop
			drive->setLinVelocity(0);
			drive->drive();
		}
	}
	bool seesDiscSpoiler()
	{
		if(spoilerCounter->GetVoltage()*100 > SIGHT_CONSTANT)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool seesDiscIntake()
	{
		if(intakeCounter->GetVoltage()*100 > SIGHT_CONSTANT)
		{
			return true;
		}
		else
		{
			return false;
		}
	}	
	bool seesDiscLoader()
	{
		if(magazineInputCounter->GetVoltage()*100 > SIGHT_CONSTANT)
		{
			return true;
		}
		else
		{
			return false;
		}
	}	
	bool seesDiscMagazine()
	{
		if(magazineBottomCounter->GetVoltage()*100 > SIGHT_CONSTANT)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	void countDiscs()
	{
		static int robotCount = 0;
		static int nonMagazineCount = 0;
		static int magazineCount = 0;
		static bool lastIntake = false;
		static bool lastManualLoad = false;
		static bool lastMagazine = false;
		
		if(seesDiscIntake() && !lastIntake)
		{
			robotCount ++;
		}
		if(seesDiscSpoiler() && !lastManualLoad)
		{
			robotCount ++;
			
		}
		if(seesDiscLoader() && !lastMagazine)
		{
			magazineCount ++;
		}
//		if(shooter->shooterFired)
//		{
//			magazineCount --;
//			robotCount --;
//		}
		nonMagazineCount = robotCount - magazineCount;
		lastIntake = seesDiscIntake();
	    lastManualLoad = seesDiscSpoiler();
		lastMagazine = seesDiscLoader();
	}
	
	void smartDashboardPrint()
	{
		oi->dashboard->PutNumber("Linear Velocity", drive->getLinVelocity());
		oi->dashboard->PutNumber("Left Encoder", drive->leftEncoder->Get());
		oi->dashboard->PutNumber("Right Encoder", drive->rightEncoder->Get());
		oi->dashboard->PutBoolean("isAtTargetD", drive->isAtLinearTarget);
		oi->dashboard->PutNumber("Step", step);
//		oi->dashboard->PutNumber("step", step);
//		oi->dashboard->PutNumber("currentTicksD", drive->currentTicksLinear);
//		oi->dashboard->PutNumber("targetTicksD", drive->targetTicksLinear);
//		oi->dashboard->PutNumber("deltaTicksD", drive->deltaTicksLinear);
//		oi->dashboard->PutNumber("errorD", drive->errorLinear);
//		oi->dashboard->PutNumber("errorDuplicateD", drive->errorLinear);
//		
//		oi->dashboard->PutNumber("currentTimeD", drive->currentTimeLinear);
//		oi->dashboard->PutNumber("targetTimeD", drive->targetTimeLinear);
//		oi->dashboard->PutNumber("deltaTimeD", drive->deltaTimeLinear);
//		oi->dashboard->PutNumber("errorTimeD", drive->errorTimeLinear);
//		
//		oi->dashboard->PutNumber("voltage", oi->getBatteryVoltage());
//		oi->dashboard->PutNumber("pot voltage", pot->GetVoltage());
//		oi->dashboard->PutNumber("Top Limit", shooter->shooterTopLimit->Get());
//		oi->dashboard->PutNumber("Bottom Limit", shooter->shooterBottomLimit->Get());
//		//oi->dashboard->PutNumber("Shooter RPM", shooter->getShooterRPM());
//		oi->dashboard->PutNumber("Shooter Target Velocity", shooter->targetVelocity);
//		oi->dashboard->PutNumber("Shooter Mini WHeel Target", shooter->targetMiniWheelVelocity);
		
		//oi->dashboard->PutNumber("rpm", ( shooter->getShooterRPM() ));
		//oi->dashboard->PutNumber("Shooter RPM", (60/shooterIRCount2->GetPeriod()));
//		
//		oi->dashboard->PutBoolean("isAtTargetT", drive->isAtTurnTarget);
//		oi->dashboard->PutNumber("currentTicksT", drive->currentTicksTurn);
//		oi->dashboard->PutNumber("targetTicksT", drive->targetTicksTurn);
//		oi->dashboard->PutNumber("deltaTicksT", drive->deltaTicksTurn);
//		oi->dashboard->PutNumber("errorT", drive->errorTurn);
//		oi->dashboard->PutNumber("errorDuplicateT", drive->errorTurn);
	}
	    		
};

START_ROBOT_CLASS(Medic);
