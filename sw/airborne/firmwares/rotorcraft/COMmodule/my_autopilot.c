#include "my_autopilot.h"
#include "state.h"
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


void my_autopilot_init(){
	// Initialize stabilization loops
	stabilization_init();		// Sets the variable stabilization_cmd[COMMANDS_NB] to zero in {stabilization.h}
	stabilization_attitude_init();
}


void my_autopilot_periodic(){

	if(control_cmd_flag == 1){
		
		stabilization_cmd[COMMAND_THRUST] = myrefcommand.thrust; 
		stab_att_sp_euler.phi   = myrefcommand.phi;
		stab_att_sp_euler.theta = myrefcommand.theta;
		stab_att_sp_euler.psi   = 0;
		control_cmd_flag = 0;
	}
	//printf("* %f %f %f %d\n",myrefcommand.thrust, myrefcommand.phi, myrefcommand.theta, stab_att_sp_euler.psi);
	
	//printf("%d %d %d %d\n", stateGetNedToBodyQuat_i()->qi,stateGetNedToBodyQuat_i()->qx,stateGetNedToBodyQuat_i()->qy,stateGetNedToBodyQuat_i()->qz);
	stabilization_attitude_run(my_autopilot_in_flight); // [arg]: bool in_flight = 1
	SetRotorcraftCommands(stabilization_cmd, my_autopilot_in_flight, my_autopilot_motors_on);
}





