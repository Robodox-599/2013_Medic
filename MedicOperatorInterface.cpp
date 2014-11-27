#include "MedicOperatorInterface.h"

MedicOperatorInterface::MedicOperatorInterface()
{
	joyDrive = new Joystick(1);
	joyManip = new Joystick(2);
	dsSimple = DriverStation::GetInstance();
	ds = &dsSimple->GetEnhancedIO();
	dsLCD = DriverStationLCD::GetInstance();	
	dashboard->init();
}


MedicOperatorInterface::~MedicOperatorInterface()
{
	delete dsLCD;
	delete joyDrive;
	delete joyManip;
	
	dsLCD = NULL;
	joyDrive = NULL;
	joyManip = NULL;	
}

/*
 * Joystick getDriveJoystick
 * Parameters: N/A
 * Summary: Gets the Drive Joystick 
 */
Joystick *MedicOperatorInterface::getDriveJoystick()
{
    return joyDrive;
}

/*
 * Joystick getManipJoystick
 * Parameters: N/A
 * Summary: Gets the Manipulator Joystick 
 */
Joystick *MedicOperatorInterface::getManipJoystick()
{
	return joyManip;
}

/*
 * Joystick getDriveJoystickButton
 * Parameters: UINT8 button - could be any button on the joysticks
 * Summary: Returns the raw drive button.
 */
bool MedicOperatorInterface::getDriveJoystickButton(UINT8 button)
{
	 if(joyDrive->GetRawButton(button))
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }
}

/*
 * Joystick getManipJoystickButton
 * Parameters: UINT8 button - could be any button on the joysticks
 * Summary: Returns the raw manipulator button.
 */
bool MedicOperatorInterface::getManipJoystickButton(UINT8 button)
{
	if( joyManip->GetRawButton(button) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float MedicOperatorInterface::getBatteryVoltage()
{
	return DriverStation::GetInstance()->GetBatteryVoltage();
}
