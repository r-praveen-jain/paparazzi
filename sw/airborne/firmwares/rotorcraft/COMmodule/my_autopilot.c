#include "my_autopilot.h"
#include "susbsystems/commands.h"
#include "subsystems/actuators.h"
#include "subsystems/electrical.h"
#include "firmwares/rotorcraft/stabilization.h"
//#include "firmwares/rotorcraft/stabilization/stabilization_none.h"
//#include "firmwares/rotorcraft/stabilization/stabilization_rate.h"
#include "firmwares/rotorcraft/stabilization/stabilization_attitude.h"
#include "Communication/Control_COMport.h"
#include "parameters.h"

bool autopilot_motors_on = 1;
bool autopilot_in_flight = 1;

void my_autopilot_init(){
	// Initialize stabilization loops
	stabilization_init();		// Sets the variable stabilization_cmd[COMMANDS_NB] to zero in {stabilization.h}
	stabilization_attitude_init();
}


void my_autopilot_periodic(){

	if(control_cmd_flag == 1){
		stab_att_sp_euler.phi   = myrefcommand.phi;
		stab_att_sp_euler.theta = myrefcommand.theta;
		stab_att_sp_euler.psi   = 0;
		control_cmd_flag = 0;
	}
	stabilization_attitude_run(autopilot_in_flight); // [arg]: bool in_flight = 1
	SetRotorcraftCommands(stabilization_cmd, autopilot_in_flight, autopilot_motors_on);
}





