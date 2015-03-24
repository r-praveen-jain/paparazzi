#include "my_autopilot.h"
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

bool my_autopilot_motors_on = 1;
bool my_autopilot_in_flight = 1;

void my_autopilot_init(){
	// Initialize stabilization loops
	stabilization_init();		// Sets the variable stabilization_cmd[COMMANDS_NB] to zero in {stabilization.h}
	stabilization_attitude_init();
}


void my_autopilot_periodic(){

	if(control_cmd_flag == 1){
		stabilization_cmd[COMMAND_THRUST] = myrefcommand.thrust; // modify 
		stab_att_sp_euler.phi   = myrefcommand.phi;
		stab_att_sp_euler.theta = myrefcommand.theta;
		stab_att_sp_euler.psi   = 0;
		control_cmd_flag = 0;
	}
	//printf("* %d %f %f %f\n",stabilization_cmd[COMMAND_THRUST], stab_att_sp_euler.phi, stab_att_sp_euler.theta, stab_att_sp_euler.psi);
	if (stabilization_cmd[COMMAND_THRUST] == 0){
		autopilot_motors_on = 0;
	} else { autopilot_motors_on = 1; }
	stabilization_attitude_run(my_autopilot_in_flight); // [arg]: bool in_flight = 1
	SetRotorcraftCommands(stabilization_cmd, my_autopilot_in_flight, my_autopilot_motors_on);
}





