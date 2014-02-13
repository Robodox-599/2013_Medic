#include "MedicManipulator.h"

MedicManipulator::MedicManipulator()
{
	MedicManipulator(INTAKE_ROLLER_VICTOR_CHANNEL, CONVEYER_VICTOR_CHANNEL,
					 CLIMBER_SOLENOID_CHANNEL_A, CLIMBER_SOLENOID_CHANNEL_B,
					 PNEUMATICS_12V_SLOT);
}

MedicManipulator::MedicManipulator( UINT8 intakeRollerVictorChannel,
									UINT8 conveyerVictorChannel,
									UINT8 climberSolA,
									UINT8 climberSolB, UINT8 pnuemClimberSlot )
{		
	intakeRoller = new Victor(intakeRollerVictorChannel);
	horizontalVerticalConveyer = new Victor(conveyerVictorChannel);
	climber = new DoubleSolenoid(pnuemClimberSlot, climberSolA, climberSolB);
	spoiler = new DoubleSolenoid(PNEUMATICS_24V_SLOT, SPOILER_SOLENOID_CHANNEL_A, SPOILER_SOLENOID_CHANNEL_B);
}

MedicManipulator::~MedicManipulator()
{	
	delete intakeRoller;
	delete horizontalVerticalConveyer;
	delete climber;
	delete spoiler;

	
	intakeRoller = NULL;
	horizontalVerticalConveyer = NULL;
	climber = NULL;
	spoiler = NULL;

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
	if(climb)
	{
		climber->Set(DoubleSolenoid::kForward);
	}
	else
	{
		climber->Set(DoubleSolenoid::kReverse);
	}
}

void MedicManipulator::setSpoiler(bool up)
{
	if(up)
	{
		spoiler->Set(DoubleSolenoid::kForward);
	}
	else
	{
		spoiler->Set(DoubleSolenoid::kReverse);
	}
}
