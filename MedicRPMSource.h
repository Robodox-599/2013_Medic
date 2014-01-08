#ifndef MEDIC_RPM_SOURCE_H
#define MEDIC_RPM_SOURCE_H
#include "WPILib.h"

class MedicRPMSource : public PIDSource
{
public:
	MedicRPMSource(Encoder *source);
	virtual ~MedicRPMSource();
	
	/*
	 * void inputRPM
	 * Paramaters: double input - the input RPM speed
	 * Summary: Sets the RPM of input.
	 */
	void inputRPM(double input);
	
	/*
	 * double PIDGet
	 * Paramaters: N/A
	 * Summary: Gets the RPM.
	 */
	double PIDGet();
	Encoder *rpmSource;
private:
	double rpm;
};
#endif
