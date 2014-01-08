#ifndef MEDIC_INS_H
#define MEDIC_INS_H

#include "WPILib.h"
#include "MedicMacros.h"
#include "MedicDrive.h"
#include <math.h>

#define DEGREES_TO_RADIANS (.017453)
#define FULL_ROTATION      (360.0)
#define HALF_ROTATION       (180.0) 
//#define STARTING
/*
 * This will contain all of the Inertial Navigation System code for the Chiropractor
 */

class MedicINS : public PIDSource
{
public:
    MedicINS();
    virtual ~MedicINS();
    //static MedicINS *get_instance();
    
	/*
	 * NavAxes is the three directions of position and rate that our robot will be dealing with.
	 * It will only be called as part of the NavData structure, which will indicate whether the
	 *  values are positions, velocities,or accelerations.
	 */
	struct NavAxes
	{
	    float x;       //positive forward x is x relative to robot, north relative to field
	    float y;       //positive right y is y relative to robot, east relative to field
	};
	
	struct NavData
	{
	    NavAxes position;  //in feet or degrees
	    NavAxes rate;      //in feet/sec or degress/sec
	    NavAxes positionLast;
	};
	
	/*
	 * init()
	 * initializes the INS
	 */
	void init();
	
	/*
	 * update()
	 * updates the INS, must be called regularly
	 */
	void update();     
    
	/*
	 * getRelativeRobot()
	 * returns the x,y, and psi values of position and rate for the robot,
	 *  relative to a robot starting at (0,0,0)
	 */
	NavAxes getRelativeRobot();      
    
	/*
	 * getRelativeField()
	 * returns the x,y, and psi values of position and rate for the robot,
	 *  relative to the robot's starting position on the field.
	 */
	NavData getRelativeField();  
	
	/* getPsi()
	 * parameters: none
	 * returns: value of psi, the robot heading
	 */
	float getPsi(); //gangnam style!
	
	/* getGyroINS()
	 * used for getting the gyro to be used in PIDController objects as a PIDSource
	 * parameters: none
	 * returns: pointer to the gyro_INS
	 */
	Gyro* getGyroINS();
	
	double PIDGet();

private:
    // Singleton 
    //MedicINS();
    //~MedicINS();
    //MedicINS(const MedicINS &);             // intentionally undefined
    //MedicINS & operator=(const MedicINS &); // intentionally undefined
 
    //static MedicINS *instance;
    
    // Objects
    Gyro               *gyroINS;
    ADXL345_I2C        *I2CAccelerometer;
    //Encoder            *encoder_left;
    //Encoder            *encoder_right;
    //DriverStationLCD   *ds_lcd;
    PIDController      *PIDConHeadingHold;
    
    // Variables
    NavData relativeField;
    NavAxes relativeRobot;
    NavAxes navStartingPosition;
    MedicDrive *driveBase;
    float psiLast;     //positive clockwise in degrees
    float psi;
    float dPsi;
    float encoderSum;
    float encoderDifference;
    float averageEncoderDistance;
    
    // Functions
    
    // Values
    float initPsi; //in degrees
    float dt; // in millisecs
    
};

#endif

