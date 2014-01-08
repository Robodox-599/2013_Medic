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

/*
 * bool getPIDToggle
 * Parameters: UINT8 toggle
 * Summary: is the PID toggled?
 */
bool MedicOperatorInterface::readAutoShootToggle(UINT8 toggle)
{
	if(ds->GetDigital(toggle) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool MedicOperatorInterface::readClimbSafetyEnable(UINT8 toggle)
{
	if(ds->GetDigital(toggle) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool MedicOperatorInterface::readElevationTarget1(UINT8 toggle)
{
	if(ds->GetDigital(toggle) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MedicOperatorInterface::readElevationTarget2(UINT8 toggle)
{
	if(ds->GetDigital(toggle) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool MedicOperatorInterface::readElevationTarget3(UINT8 toggle)
{
	if(ds->GetDigital(toggle) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


double MedicOperatorInterface::readTargetDistance()
{
	return dashboard->GetNumber("TargetDistance");
}

double MedicOperatorInterface::readTargetCenterX()
{
	return dashboard->GetNumber("TargetCenterX");
}

double MedicOperatorInterface::readTargetCenterY()
{
	return dashboard->GetNumber("TargetCenterY");
}

bool MedicOperatorInterface::readAutoAimToggle()
{
	if(ds->GetDigital(1))
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
	//return 0.0;
}

