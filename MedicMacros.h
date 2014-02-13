#ifndef MEDIC_MACROS_H
#define MEDIC_MACROS_H

<<<<<<< HEAD
=======


>>>>>>> Medic code repairs
//Slots
#define PNEUMATICS_24V_SLOT					    (1)
#define PNEUMATICS_12V_SLOT						(2)
#define ANALOG_BUMPER_SLOT       				(1)
#define DIGITAL_SIDECAR_SLOT_2					(1)

//Digital Sidecar

//Motors
#define DRIVE_FRONT_LEFT_MOTOR_CHANNEL          (1)
#define DRIVE_REAR_LEFT_MOTOR_CHANNEL           (2)
#define DRIVE_FRONT_RIGHT_MOTOR_CHANNEL         (3)
#define DRIVE_REAR_RIGHT_MOTOR_CHANNEL          (4)
#define INTAKE_ROLLER_VICTOR_CHANNEL			(6)
#define	CONVEYER_VICTOR_CHANNEL 				(7)
#define ELEVATOR_VICTOR_CHANNEL					(8)
#define SHOOTER_MINI_WHEEL_VICTOR_CHANNEL		(9)
#define SHOOTER_WHEEL_VICTOR_CHANNEL		    (10)


//Manipulator
#define LOADER_UP               	            (-1)
#define LOADER_DOWN     		                (1)
#define LOADER_OFF                  	        (0)
#define CONVEYER_MOVE							(1)
#define CONVEYER_STOP							(0)
#define INTAKE_MOVE								(-1.0)
#define INTAKE_STOP								(0)

	//Drive
#define DRIVE_SPEED						        (1) //TODO: dummy number
#define TURN_SPEED						        (1) //TODO: dummy number
#define AUTO_DRIVE_DEADZONE						(1)//TODO:dummy number
#define AUTO_TURN_DEADZONE						(1) //TODO:dummy number
													//degrees

#define AIM_DEADZONE							(10)
#define TICKS_DEADZONE							(10)


	//INS
#define GYRO_CHANNEL							(1)//TODO:dummy number

	//Pneumatics
#define SHIFTER_SOLENOID_CHANNEL_A				(1)//24
#define SHIFTER_SOLENOID_CHANNEL_B				(2)//24
#define RPM_SENSOR_POWER						(5)//24

#define CLIMBER_SOLENOID_CHANNEL_A				(3)
#define CLIMBER_SOLENOID_CHANNEL_B				(4)
#define FEEDER_SOLENOID_CHANNEL_A       		(5)
#define FEEDER_SOLENOID_CHANNEL_B       		(6)


#define SPOILER_SOLENOID_CHANNEL_A				(7)//24
#define SPOILER_SOLENOID_CHANNEL_B				(8)//24

//Digitial IO
	
   //Digital
#define LEFT_DRIVE_ENCODER_CHANNEL_A			(4)
#define LEFT_DRIVE_ENCODER_CHANNEL_B			(5)
#define RIGHT_DRIVE_ENCODER_CHANNEL_A		    (6)
#define RIGHT_DRIVE_ENCODER_CHANNEL_B           (7)
#define SHOOTER_WHEEL_IR_CHANNEL				(2)//TODO:DUMMY
#define ELEVATION_TOP_LIMIT_CHANNEL				(10)
#define ELEVATION_BOTTOM_LIMIT_CHANNEL			(9)
#define SHOOTER_TRIGGER_CHANNEL					(8)


	//Misc
#define SYNC_STATE_OFF          		        (0)
#define DRIVE_BASE_WIDTH			  		    (18.99952)
#define INCHES_PER_TICK                			(0.075398)   // circumference of wheel / total ticks per rev
													//6pi / 250
#define TICKS_PER_DEGREE				   	    (4.398037)   //width wheel to wheel * ticks * DEGREES_TO_RADIANS
												//18.99952 * (250 / (180 * 6))
#define FULL_SPEED 							    (1)
#define REDUCTION							    (.75)

#define DESIRED_VOLTAGE							(11) //max voltage
#define BATTERY_COMPENSATION					(DESIRED_VOLTAGE / oi->getBatteryVoltage())   //

#define TARGET_RPM								(5000)
#define SHOOTER_AD_CHANNEL						(1)//TODO:dummy number
#define ANGLE_POT_CHANNEL						(2)
#define SHOOTER_POT_DEGREES_PER_VOLT		    (1)//TODO:dummy number
#define SHOOTER_DEGREES_PER_BIT					(1)//SHOOTER_POT_DEGREES_PER_VOLT * (20v / 4096b)
#define ELEVATION_DEADZONE						(1)//TODO:dummy number
#define SHOOTER_MAX_ELEVATION					(45)//TODO:DUMMY
#define SHOOTER_MIN_ELEVATION					(1.0)//TODO:DUMMY
#define ELEVATION_SPEED							(1)//TODO:DUMMY

#define GOAL_1 	(1)
#define GOAL_2  (2)
#define GOAL_3	(3)

#define TIME_TO_FIRE (.25)
#define SIGHT_CONSTANT (200)

#endif
