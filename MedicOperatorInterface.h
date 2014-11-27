#ifndef MEDIC_OPERATOR_INTERFACE_H
#define MEDIC_OPERATOR_INTERFACE_H

#include "MedicMacros.h"
#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/NamedSendable.h"
#include "SmartDashboard/Sendable.h"
#include "SmartDashboard/SendableChooser.h"

class MedicOperatorInterface
{
	
public:
	MedicOperatorInterface();	
	~MedicOperatorInterface();
	
	enum ShooterTargeting { position1 = 1, position2 = 2, position3 = 3}shooterTarget;
	
	Joystick *getDriveJoystick();
	
	bool getDriveJoystickButton(UINT8 button);
		
	bool getDriveJoystickButtonReleased(UINT8 button);
	
	Joystick *getManipJoystick();
	
	bool getManipJoystickButton(UINT8 button);
	
	bool getManipJoystickButtonReleased(UINT8 button);

	float getBatteryVoltage();
	DriverStation *getDriverStation();
	
	DriverStationLCD *dsLCD;
	SmartDashboard *dashboard;

private:
	Joystick *joyDrive;
	Joystick *joyManip;
	DriverStationEnhancedIO *ds;
	DriverStation *dsSimple;
};
#endif
