#include "MedicINS.h"

MedicINS::MedicINS()
{
    //ds_lcd = DriverStationLCD::GetInstance();
    
	gyroINS = new Gyro(ANALOG_BUMPER_SLOT, GYRO_CHANNEL);
	I2CAccelerometer = new ADXL345_I2C(DIGITAL_SIDECAR_SLOT_2);
	driveBase = new MedicDrive();
	//encoder_left = new Encoder(DIGITAL_SIDECAR_SLOT_4, DRIVE_ENCODER_LEFT_CH_A, 
    //                                      DIGITAL_SIDECAR_SLOT_4, DRIVE_ENCODER_LEFT_CH_B, CounterBase::k1X);
	//encoder_right = new Encoder(DIGITAL_SIDECAR_SLOT_4, DRIVE_ENCODER_RIGHT_CH_A, 
    //                                       DIGITAL_SIDECAR_SLOT_4, DRIVE_ENCODER_RIGHT_CH_B, CounterBase::k1X);
	initPsi = 180; //TODO: fill in actual start heading, in degrees
	
	//TODO: call init() here?
	navStartingPosition.x = 0;
	navStartingPosition.y = 0;
	
	relativeField.position.x = 0;
	relativeField.position.y = 0;
	relativeField.positionLast.x = 0;
	relativeField.positionLast.y = 0;
	relativeField.rate.x = 0;
	relativeField.rate.y = 0;
	
	relativeRobot.x = 0;
	relativeRobot.y = 0;
	psi = initPsi;
	
	gyroINS->Reset();
	
	dt = 50; // in millisecs
}

MedicINS::~MedicINS()
{
	delete gyroINS;
	delete I2CAccelerometer;
	//delete encoder_left;
	//delete encoder_right;
	
	gyroINS = NULL;
	I2CAccelerometer = NULL;
	//encoder_left = NULL;
	//encoder_right = NULL;
}
/*
MedicINS* MedicINS::get_instance()
{
    if (instance == NULL)
    {
        instance = new MedicINS();
    }
    
    return instance;
}*/

/*
 * init()
 * initializes the INS
 * sets robot position to 0, rate to 0, and field position based on defined positions TODO:figure out starting positions
 */
void MedicINS::init()
{

    navStartingPosition.x = 0;
    navStartingPosition.y = 0;
    
    relativeField.position.x = 0;
    relativeField.position.y = 0;
    relativeField.positionLast.x = 0;
    relativeField.positionLast.y = 0;
    relativeField.rate.x = 0;
    relativeField.rate.y = 0;
    
    relativeRobot.x = 0;
    relativeRobot.y = 0;
    psi = initPsi;
    
    gyroINS->Reset();
}
   
/*
 * update()
 * updates the INS, must be called regularly
 */
void MedicINS::update()
{
	encoderSum = (driveBase->rightEncoder->Get() + driveBase->leftEncoder->Get());
	encoderDifference = (driveBase->rightEncoder->Get() - driveBase->leftEncoder->Get());
	averageEncoderDistance = encoderSum/2;
	
	dPsi = encoderDifference/DRIVE_BASE_WIDTH;
    //get accelerometer data
    ADXL345_I2C::AllAxes accelerometerData = I2CAccelerometer->GetAccelerations();
    
    //update relative to robot velocities
    relativeRobot.x += accelerometerData.XAxis;
    relativeRobot.y += accelerometerData.YAxis;
    
    //update psi from gyro
    //Normalized to 0-360
    psi = gyroINS->GetAngle() - FULL_ROTATION * floor((gyroINS->GetAngle() + HALF_ROTATION)/FULL_ROTATION);
    
    //update relative to field rate

 
    //update relative to field positions
    relativeField.position.x += averageEncoderDistance*(cos(psiLast) - dPsi/2 * sin(psiLast));
    relativeField.position.y += averageEncoderDistance* (sin(psiLast) + dPsi / 2 * cos(psiLast));
    relativeField.rate.x += relativeField.position.x - relativeField.positionLast.x;
    
    relativeField.rate.y += relativeField.position.y - relativeField.positionLast.y;
    
    relativeField.positionLast.x = relativeField.position.x;
    relativeField.positionLast.y = relativeField.position.y;
    
    printf("Accel X = %f\tY=%f\tZ=%f\r\n", accelerometerData.XAxis, accelerometerData.YAxis, 
            accelerometerData.ZAxis);
    psiLast = psi;
}
    
/*
 * relativeRobot()
 * returns the x,y, and psi values of position and rate for the robot,
 *  relative to a robot starting at (0,0,0)
 */
 
MedicINS::NavAxes MedicINS::getRelativeRobot()
{
    return relativeRobot;
}

/*
 * getRelativeField()
 * returns the x,y, and psi values of position and rate for the robot,
 *  relative to the robot's starting position on the field.
 */

MedicINS::NavData MedicINS::getRelativeField()
{
    return relativeField;
}

float MedicINS::getPsi()
{
    return psi;  
}

Gyro* MedicINS::getGyroINS()
{
    return gyroINS;
}

double MedicINS::PIDGet()
{
    return psi;  
}


