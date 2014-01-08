#include "MedicRPMSource.h"

MedicRPMSource::MedicRPMSource(Encoder *source)
{
	rpmSource = source;
}

MedicRPMSource::~MedicRPMSource()
{
	delete rpmSource;
	
	rpmSource = NULL;
}

/*
 * void inputRPM
 * Paramaters: double input - the input RPM speed
 * Summary: Sets the RPM of input.
 */
void MedicRPMSource::inputRPM(double input)
{
	rpm =  input;
}

/*
 * double PIDGet
 * Paramaters: N/A
 * Summary: Gets the RPM.
 */
double MedicRPMSource::PIDGet()
{
	return rpm;
}
