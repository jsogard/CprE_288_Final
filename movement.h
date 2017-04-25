/*
 * Ethan Wieczorek
 * Josh Rolles
 *
 * Created 1/25/17
 *
 *
 */

#ifndef MOVEMENT_H_
#include "open_interface.h";
#define MOVEMENT_H_

void move_forward(oi_t *sensor, int centimeters);
void move_backward(oi_t *sensor, int centimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void turn_counter_clockwise(oi_t *sensor, int degrees);
void maneuver(oi_t *sensor_data);

#endif
