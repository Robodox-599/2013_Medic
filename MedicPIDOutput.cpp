#include "MedicPIDOutput.h"

MedicPIDOutput::MedicPIDOutput()
{
	
}

MedicPIDOutput::~MedicPIDOutput()
{
	
}

/*
 * void PIDWrite
 * Parameters: float output - the PID output
 * Summary: Sets the output as the result
 */
void MedicPIDOutput::PIDWrite(float output)
{
	result = output;
}

/*
 * double readOutput
 * Parameters: N/A
 * Summary: Returns the output of the PID.
 */
double MedicPIDOutput::readOutput()
{
	return result;
}
