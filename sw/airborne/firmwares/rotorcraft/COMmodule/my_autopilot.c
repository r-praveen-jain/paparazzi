#include "my_autopilot.h"
#include "state.h"
//#include "math/pprz_algebra_float.h"
#include "subsystems/commands.h"
#include "subsystems/actuators.h"
#include "subsystems/electrical.h"
#include "subsystems/ahrs.h"
#include "subsystems/gps.h"
#include "subsystems/imu.h"
#include "firmwares/rotorcraft/stabilization.h"
//#include "firmwares/rotorcraft/stabilization/stabilization_none.h"
//#include "firmwares/rotorcraft/stabilization/stabilization_rate.h"
#include "firmwares/rotorcraft/stabilization/stabilization_attitude.h"
#include "firmwares/rotorcraft/autopilot.h"
#include "Communication/Control_COMport.h"
#include "parameters.h"
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <string.h>

bool my_autopilot_motors_on = 1;
bool my_autopilot_in_flight = 1;
double desired_heading = MY_DEG2RAD(-7); // -122.35 + 90 = -32.35
const struct FloatVect3 my_zaxis = {0., 0., 1.};

//-------------------------------------------------------------------------------------------
struct timeval timestamp;
// This function can be somewhere else, not a very good place to define this function
unsigned long my_GetTimeStamp(){
	gettimeofday(&timestamp,NULL);
	unsigned long time_in_micros = 1000000 * timestamp.tv_sec + timestamp.tv_usec;
	return time_in_micros;
}
//----------------------------------------------------------------------------------------------

void my_autopilot_init(){
	// Initialize stabilization loops
	stabilization_init();		// Sets the variable stabilization_cmd[COMMANDS_NB] to zero in {stabilization.h}
	stabilization_attitude_init();
}

void my_autopilot_periodic(){

	if(control_cmd_flag == 1){
		//--------------------------------------------------------------------------------------------------------------
		// Implementation 1: works only with zero heading
		//--------------------------------------------------------------------------------------------------------------
		//struct FloatQuat my_quat_setpoint = {0};
		//struct FloatEulers my_euler_setpoint = {.phi = myrefcommand.phi, .theta = myrefcommand.theta, .psi = 0};
		//float_quat_of_eulers(&my_quat_setpoint, &my_euler_setpoint);
		//QUAT_BFP_OF_REAL(stab_att_sp_quat, my_quat_setpoint);
		//--------------------------------------------------------------------------------------------------------------
		// Implementation 2: works with heading control (sometimes, some problem with yaw still exists)
		//--------------------------------------------------------------------------------------------------------------
		//gps.course = myrefcommand.psi * 1e7;
	
		struct FloatQuat my_quat_rp = {0};
		struct FloatQuat my_quat_setpoint = {0};
		struct FloatQuat my_quat_yaw = {0};	
		
		struct FloatEulers my_euler_setpoint = {.phi = myrefcommand.phi, .theta = myrefcommand.theta, .psi = 0};
		float_quat_of_eulers(&my_quat_rp, &my_euler_setpoint);
		float_quat_of_axis_angle(&my_quat_yaw, &my_zaxis, desired_heading);
		float_quat_comp(&my_quat_setpoint, &my_quat_yaw, &my_quat_rp);
		float_quat_normalize(&my_quat_setpoint);
		QUAT_BFP_OF_REAL(stab_att_sp_quat, my_quat_setpoint);
		//This one needed. Why? Not sure, maybe for telemetry and heading reference of some kind
		stab_att_sp_euler.phi   = ANGLE_BFP_OF_REAL(myrefcommand.phi);
		stab_att_sp_euler.theta = ANGLE_BFP_OF_REAL(myrefcommand.theta);
		stab_att_sp_euler.psi   = ANGLE_BFP_OF_REAL(desired_heading);
		//-------------------------------------------------------------------------------------------------------------
		stabilization_cmd[COMMAND_THRUST] = myrefcommand.thrust; 
		control_cmd_flag = 0;
	}
	//gps.fix = GPS_FIX_3D;
	stabilization_attitude_run(my_autopilot_in_flight); // [arg]: bool in_flight = 1
        //printf("phi: %f theta: %f psi: %f\n", MY_RAD2DEG(stateGetNedToBodyEulers_f()->phi), MY_RAD2DEG(stateGetNedToBodyEulers_f()->theta), MY_RAD2DEG(stateGetNedToBodyEulers_f()->psi));
	printf("mag: %f mag scaled x: %d y: %d z: %d\n",MY_RAD2DEG(stateGetNedToBodyEulers_f()->psi), imu.mag.x, imu.mag.y, imu.mag.z);
	SetRotorcraftCommands(stabilization_cmd, my_autopilot_in_flight, my_autopilot_motors_on);
}

#ifdef USE_MYTELEMETRY
void my_telemetry_periodic(){
	char telemetry_packet[1024] = {0}; // TODO: Remove the hard coding of array size
	sprintf(telemetry_packet, "%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f",
				 //my_GetTimeStamp(),
				 electrical.vsupply,
				 stabilization_cmd[COMMAND_ROLL],
				 stabilization_cmd[COMMAND_PITCH],
				 stabilization_cmd[COMMAND_YAW],
				 ANGLE_FLOAT_OF_BFP(stab_att_sp_euler.phi),
				 ANGLE_FLOAT_OF_BFP(stab_att_sp_euler.theta),
				 ANGLE_FLOAT_OF_BFP(stab_att_sp_euler.psi),
				 stateGetNedToBodyEulers_f()->phi,
				 stateGetNedToBodyEulers_f()->theta,
 				 stateGetNedToBodyEulers_f()->psi,
				 stateGetBodyRates_f()->p,
				 stateGetBodyRates_f()->q,
			         stateGetBodyRates_f()->r);
	my_SendPacket(telemetry_packet, strlen(telemetry_packet));
}
#endif

