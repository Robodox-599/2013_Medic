#ifndef MEDICPIDOUTPUT_H
#define MEDICPIDOUTPUT_H
#include "WPILib.h"

class MedicPIDOutput : public PIDOutput
{
public:
	MedicPIDOutput();
	virtual ~MedicPIDOutput();
	
	/*
	 * void PIDWrite
	 * Parameters: float output - the PID output
	 * Summary: Sets the output as the result
	 */
	void PIDWrite(float output);
	
	/*
	 * double readOutput
	 * Parameters: N/A
	 * Summary: Returns the output of the PID.
	 */
	double readOutput();
	double result;
};

#endif
