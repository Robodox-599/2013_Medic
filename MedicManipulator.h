#ifndef MEDIC_MANIPULATOR_H
#define MEDIC_MANIPULATOR_H
#include "WPILib.h"
#include "MedicMacros.h"


class MedicManipulator
{
public:
	MedicManipulator();

	MedicManipulator(UINT8 intakeVictorChannel,
			         UINT8 conveyerVictorChannel,
			         UINT8 climberSolA,
			         UINT8 climberSolB,
			         UINT8 pnuemClimberSlot);
	~MedicManipulator();
	
	/*
	 * void intakeDisc
	 * Parameters: bool intake - do we intake a disc?
	 * Summary: intakes a disc with a roller
	 */
	void intakeDisc(bool intake);
	
	/*
	 * void conveyer
	 * Parameters: bool move - do we move the two conveyers? 
	 * Summary: Moves the horizontal and vertical conveyers
	 */
	void conveyer(double intakeSpeed);
	
	/*
	 * void climbPyramid
	 * Parameters: bool climb - do we start climbing?
	 * Summary: climbs the pyramid
	 */
	void climbPyramid(bool climb);
	void setSpoiler (bool up);
	
	
	DoubleSolenoid *spoiler;
	DoubleSolenoid *climber;


private:
	Victor *intakeRoller;
	Victor *horizontalVerticalConveyer;

	
};
#endif

