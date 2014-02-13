#include "MedicManipulator.h"

MedicManipulator::MedicManipulator()
{
#ifdef NEW_BOT
	MedicManipulator(INTAKE_ROLLER_VICTOR_CHANNEL, CONVEYER_VICTOR_CHANNEL,
					 CLIMBER_SOLENOID_CHANNEL_A, CLIMBER_SOLENOID_CHANNEL_B,
					 PNEUMATICS_12V_SLOT);
#else
	MedicManipulator(INTAKE_ROLLER_VICTOR_CHANNEL, CONVEYER_VICTOR_CHANNEL);
#endif
}

#ifdef NEW_BOT
MedicManipulator::MedicManipulator( UINT8 intakeRollerVictorChannel,
									UINT8 conveyerVictorChannel,
									UINT8 climberSolA,
									UINT8 climberSolB, UINT8 pnuemClimberSlot )
#else
MedicManipulator::MedicManipulator( UINT8 intakeRollerVictorChannel,
									UINT8 conveyerVictorChannel )
#endif								
{		
	intakeRoller = new Victor(intakeRollerVictorChannel);
	horizontalVerticalConveyer = new Victor(conveyerVictorChannel);
#ifdef NEW_BOT
	climber = new DoubleSolenoid(pnuemClimberSlot, climberSolA, climberSolB);
	spoiler = new DoubleSolenoid(PNEUMATICS_24V_SLOT, SPOILER_SOLENOID_CHANNEL_A, SPOILER_SOLENOID_CHANNEL_B);
#endif
}

MedicManipulator::~MedicManipulator()
{	
	delete intakeRoller;
	delete horizontalVerticalConveyer;
#ifdef NEW_BOT
	delete climber;
	delete spoiler;
#endif
	
	intakeRoller = NULL;
	horizontalVerticalConveyer = NULL;
#ifdef NEW_BOT
	climber = NULL;
	spoiler = NULL;
#endif
}

/*
 * void intakeDisc
 * Parameters: bool intake - do we intake a disc?
 * Summary: intakes a disc with a roller
 */
void MedicManipulator::intakeDisc(bool intake)
{	
	if(intake)
	{
		intakeRoller->Set(INTAKE_MOVE); 
	}
	else
	{
		intakeRoller->Set(INTAKE_STOP);  
	}
}

/*
 * void conveyer
 * Parameters: bool move - do we move the two conveyers? 
 * Summary: Moves the horizontal and vertical conveyers
 */
void MedicManipulator::conveyer(double intakeSpeed)
{	
	
		horizontalVerticalConveyer->Set(intakeSpeed);
	
}	


/*
 * void climbPyramid
 * Parameters: bool climb - do we start climbing?
 * Summary: climbs the pyramid.
 */
void MedicManipulator::climbPyramid(bool climb)
{
#ifdef NEW_BOT
	if(climb)
	{
		climber->Set(DoubleSolenoid::kForward);
	}
	else
	{
		climber->Set(DoubleSolenoid::kReverse);
	}
#endif
}

void MedicManipulator::setSpoiler(bool up)
{
#ifdef NEW_BOT
	if(up)
	{
		spoiler->Set(DoubleSolenoid::kForward);
	}
	else
	{
		spoiler->Set(DoubleSolenoid::kReverse);
	}
#endif
}
