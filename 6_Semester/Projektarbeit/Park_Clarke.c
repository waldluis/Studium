#include "Park_Clarke.h"


//Function to calculate Clarke transformation with 2 input currents
void Clarke_Lib_Do_2(clarke_type_2* clarke_ptr)
{
	clarke_ptr->Ialpha = clarke_ptr->Ia;
	clarke_ptr->Ibeta = 0.57735026919f * (clarke_ptr->Ia + 2 * clarke_ptr->Ib);
}

//Function to calculate Clarke transformation with 3 input currents
void Clarke_Lib_Do_3(clarke_type_3* clarke_ptr)
{
	clarke_ptr->Ialpha = (2 / 3) * clarke_ptr->Ia - (1 / 3) * (clarke_ptr->Ib - clarke_ptr->Ic);
	clarke_ptr->Ibeta = (2 / sqrt(3)) * (clarke_ptr->Ib - clarke_ptr->Ic);
}


//Function to calculate Park transformation
void Park_Lib_Do(park_type* park_ptr)
{
	park_ptr->Id = park_ptr->Ialpha * cos(park_ptr->motorAngle) + park_ptr->Ibeta * sin(park_ptr->motorAngle);
	park_ptr->Iq = park_ptr->Ibeta * cos(park_ptr->motorAngle) - park_ptr->Ialpha * sin(park_ptr->motorAngle);
}


//Function to calculate inverse Park transformation
void InvPark_Lib_Do(invpark_type* invpark_ptr)
{
	invpark_ptr->Valpha = invpark_ptr->Vd * cos(invpark_ptr->motorAngle) - invpark_ptr->Vq * sin(invpark_ptr->motorAngle);
	invpark_ptr->Vbeta = invpark_ptr->Vq * cos(invpark_ptr->motorAngle) + invpark_ptr->Vd * sin(invpark_ptr->motorAngle);
}


//Function to calculate value with PID-control
float_t Pid_Lib_Do(pid_type* pid_ptr, float_t in)
{
	float_t out;

	/* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
	out = (pid_ptr->state[2]) + (pid_ptr->A0 * in) + (pid_ptr->A1 * pid_ptr->state[0]) + (pid_ptr->A2 * pid_ptr->state[1]);

	/* Update state */
	pid_ptr->state[1] = pid_ptr->state[0];
	pid_ptr->state[0] = in;
	pid_ptr->state[2] = out;

	return out;
}


//Function to initialyse PID-structure
void Pid_init(pid_type* pid_ptr)
{
	//Calculating values 
	pid_ptr->A0 = pid_ptr->Kp + pid_ptr->Ki + pid_ptr->Kd;
	pid_ptr->A1 = -pid_ptr->Kp - 2.0f * pid_ptr->Kd;
	pid_ptr->A2 = pid_ptr->Kd;

	/* Reset state to zero, The size will be always 3 samples */
	memset(pid_ptr->state, 0, 3U * sizeof(float_t));
}


//Function to reset old states of PID-structure
void Pid_reset(pid_type* pid_ptr)
{
	/* Reset state to zero, The size will be always 3 samples */
	memset(pid_ptr->state, 0, 3U * sizeof(float_t));
}