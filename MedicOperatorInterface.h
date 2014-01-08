#ifndef MEDIC_OPERATOR_INTERFACE_H
#define MEDIC_OPERATOR_INTERFACE_H


#include "WPILib.h"
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
	
	/*
	 * Joystick getDriveJoystick
	 * Parameters: N/A
	 * Summary: Gets the Drive Joystick 
	 */
	Joystick *getDriveJoystick();
	
	/*
	 * Joystick getDriveJoystickButton
	 * Parameters: UINT8 button - could be any button on the joysticks
	 * Summary: Returns the raw drive button.
	 */
	bool getDriveJoystickButton(UINT8 button);
	
	
	bool getDriveJoystickButtonReleased(UINT8 button);
	

	/*
	 * Joystick getManipJoystick
	 * Parameters: N/A
	 * Summary: Gets the Manipulator Joystick 
	 */
	Joystick *getManipJoystick();
	
	/*
	 * Joystick getManipJoystickButton
	 * Parameters: UINT8 button - could be any button on the joysticks
	 * Summary: Returns the raw manipulator button.
	 */
	bool getManipJoystickButton(UINT8 button);
	
	bool getManipJoystickButtonReleased(UINT8 button);

	/*
	 * bool getPIDToggle
	 * Parameters: UINT8 toggle
	 * Summary: is the PID toggled?
	 */
	bool readAutoShootToggle(UINT8 toggle);
	
	bool readClimbSafetyEnable(UINT8 toggle);
	bool readClimbInterlockToggle(UINT8 toggle);
	
	bool readElevationTarget1(UINT8 toggle);
	bool readElevationTarget2(UINT8 toggle);
	bool readElevationTarget3(UINT8 toggle);

	double readTargetDistance();
	double readTargetCenterX();
	double readTargetCenterY();
	bool readAutoAimToggle();
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
