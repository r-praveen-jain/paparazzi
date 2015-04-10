#include "my_autopilot.h"
#include "state.h"
//#include "math/pprz_algebra_float.h"
#include "subsystems/commands.h"
#include "subsystems/actuators.h"
#include "subsystems/electrical.h"
#include "firmwares/rotorcraft/stabilization.h"
//#include "firmwares/rotorcraft/stabilization/stabilization_none.h"
//#include "firmwares/rotorcraft/stabilization/stabilization_rate.h"
#include "firmwares/rotorcraft/stabilization/stabilization_attitude.h"
#include "firmwares/rotorcraft/autopilot.h"
#include "Communication/Control_COMport.h"
#include "parameters.h"
#include <stdio.h>

bool my_autopilot_motors_on = 1;
bool my_autopilot_in_flight = 1;
double optitrack_heading = MY_DEG2RAD(-122.35); 


void my_autopilot_init(){
	// Initialize stabilization loops
	stabilization_init();		// Sets the variable stabilization_cmd[COMMANDS_NB] to zero in {stabilization.h}
	stabilization_attitude_init();
}

void my_autopilot_periodic(){

	if(control_cmd_flag == 1){
		struct FloatQuat my_quat_setpoint = {0};
		struct FloatEulers my_euler_setpoint = {.phi = myrefcommand.phi, .theta = myrefcommand.theta, .psi = 0};
		float_quat_of_eulers(&my_quat_setpoint, &my_euler_setpoint);
		QUAT_BFP_OF_REAL(stab_att_sp_quat, my_quat_setpoint);
		stabilization_cmd[COMMAND_THRUST] = myrefcommand.thrust; 
		//stab_att_sp_euler.phi   = myrefcommand.phi;
		//stab_att_sp_euler.theta = myrefcommand.theta;
		//stab_att_sp_euler.psi   = 0;
		control_cmd_flag = 0;
	}
	
	printf("%f %f %f\n", stateGetNedToBodyEulers_f()->phi,stateGetNedToBodyEulers_f()->theta,stateGetNedToBodyEulers_f()->psi);	
	stabilization_attitude_run(my_autopilot_in_flight); // [arg]: bool in_flight = 1
	SetRotorcraftCommands(stabilization_cmd, my_autopilot_in_flight, my_autopilot_motors_on);
}





