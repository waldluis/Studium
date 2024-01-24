/*
* This headerfile provides basic functions to create a torque driven PMSM control
* the generation of the space vector modeling is located in a different headerfile,
* here are only the functions to create the controll structure
*/

#ifndef Park_Clarke
#define Park_Clarke

#include <stdint.h>
#include <math.h>
#include <string.h>

#define _USE_MATH_DEFINES // for C
#include <math.h>

//Clarke struct with 2 input currents
typedef struct {
	float_t Ia;			//Input
	float_t Ib;			//Input
	float_t Ialpha;		//Output
	float_t Ibeta;		//Output
}clarke_type_2;

//Clarke struct with 3 input currents
typedef struct {
	float_t Ia;			//Input
	float_t Ib;			//Input
	float_t Ic;			//Input
	float_t Ialpha;		//Output
	float_t Ibeta;		//Output
}clarke_type_3;

//Park struct
typedef struct {
	float_t Ialpha;		//Input
	float_t Ibeta;		//Input
	float_t Id;		//Output
	float_t Iq;		//Output
	float_t motorAngle;	//Input
}park_type;


//Inverse Park structs
typedef struct {
	float_t Vd;			//Input
	float_t Vq;			//Input
	float_t Valpha;		//Output
	float_t Vbeta;		//Output
	float_t motorAngle;  //Input
}invpark_type;


//PID struct
typedef struct {
	float_t Kp;			//Proportional gain
	float_t Ki;			//Integral gain
	float_t Kd;			//Derivative gain
	float_t state[3];	//states: [0] = x[n], [1] = x[n-1], [2] = y[n-1]
	float_t A0;			//A0 = Kp + Ki + Kd
	float_t A1;			//A1 = -Kp - 2Kd
	float_t A2;			//A2 = Kd
}pid_type;



//Functions
void Clarke_Lib_Do_2(clarke_type_2* clarke_ptr);
void Clarke_Lib_Do_3(clarke_type_3* clarke_ptr);
void Park_Lib_Do(park_type* park_ptr);
void InvPark_Lib_Do(invpark_type* invpark_ptr);
float_t Pid_Lib_Do(pid_type* pid_ptr, float_t in);
void Pid_init(pid_type* pid_ptr);
void Pid_reset(pid_type* pid_ptr);


#endif // !Park_Clarke