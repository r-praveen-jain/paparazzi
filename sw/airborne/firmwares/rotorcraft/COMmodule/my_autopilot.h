#ifndef MY_AUTOPILOT_H
#define MY_AUTOPILOT_H

#include <stdbool.h>
#include "generated/airframe.h"

extern bool control_cmd_flag;
extern bool my_autopilot_motors_on;
extern bool my_autopilot_in_flight;
extern double desired_heading;

extern void my_autopilot_init(void);
extern void my_autopilot_periodic(void);
extern void my_telemetry_periodic(void);
extern unsigned long my_GetTimeStamp(void);
extern void update_heading_from_optitrack(double optitrack_heading);

/** Set Rotorcraft commands.
 *  Limit thrust and/or yaw depending of the in_flight
 *  and motors_on flag status
 */
#ifndef ROTORCRAFT_COMMANDS_YAW_ALWAYS_ENABLED
#define SetRotorcraftCommands(_cmd, _in_flight,  _motor_on) { \
    if (!(_in_flight)) { _cmd[COMMAND_YAW] = 0; }               \
    if (!(_motor_on)) { _cmd[COMMAND_THRUST] = 0; }             \
    commands[COMMAND_ROLL] = _cmd[COMMAND_ROLL];                \
    commands[COMMAND_PITCH] = _cmd[COMMAND_PITCH];              \
    commands[COMMAND_YAW] = _cmd[COMMAND_YAW];                  \
    commands[COMMAND_THRUST] = _cmd[COMMAND_THRUST];            \
  }
#else
#define SetRotorcraftCommands(_cmd, _in_flight,  _motor_on) { \
    if (!(_motor_on)) { _cmd[COMMAND_THRUST] = 0; }             \
    commands[COMMAND_ROLL] = _cmd[COMMAND_ROLL];                \
    commands[COMMAND_PITCH] = _cmd[COMMAND_PITCH];              \
    commands[COMMAND_YAW] = _cmd[COMMAND_YAW];                  \
    commands[COMMAND_THRUST] = _cmd[COMMAND_THRUST];            \
  }
#endif


#endif /* MY_AUTOPILOT_H */


