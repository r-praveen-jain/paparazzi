/*
 * Copyright (C) 2015 Felix Ruess <felix.ruess@gmail.com>
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file subsystems/ins/ins_gps_passthrough_utm.h
 *
 * Simply passes GPS UTM position and velocity through to the state interface.
 * For fixedwing firmware since it sets UTM pos only.
 */

#ifndef INS_GPS_PASSTHROUGH_UTM_H
#define INS_GPS_PASSTHROUGH_UTM_H

#define DefaultInsImpl ins_gps_utm

extern void ins_gps_utm_init(void);
extern void ins_gps_utm_register(void);

#endif /* INS_GPS_PASSTHROUGH_UTM_H */
