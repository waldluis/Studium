#include <stdio.h>
#include "Park_Clarke.h"

int main()
{
	clarke_type_2 clarke2;
	park_type park;
	invpark_type inv_park;
	float_t Iq_ref =1;
	float_t Id_ref =1;

	clarke2.Ia = 230;
	clarke2.Ib = -230;

	Clarke_Lib_Do_2(&clarke2);

	park.motorAngle = M_PI;
	park.Ialpha = clarke2.Ialpha;
	park.Ibeta = clarke2.Ibeta;

	Park_Lib_Do(&park);

	//Initialyse PID-structure
	pid_type pidq;
	pidq.Kd = 1;
	pidq.Ki = 1;
	pidq.Kp = 1;
	Pid_init(&pidq);

	pid_type pidd = pidq;

	//PID to get start values for inverse Park transformation
	float_t pid_Iq = Iq_ref - park.Iq;
	float_t pid_Id = Id_ref - park.Iq;

	inv_park.Vd = Pid_Lib_Do(&pidd, pid_Id);
	inv_park.Vq = Pid_Lib_Do(&pidq, pid_Iq);
	inv_park.motorAngle = M_PI;

	InvPark_Lib_Do(&inv_park);
	//inv_park contains values for SVPWM generator

}
