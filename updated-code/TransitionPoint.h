#pragma once

#include "constants.h"

class TransitionPoint
{
private:
	unsigned int index;
public:
	mass weight;
	velocity speed = 0;
	acceleration point_acceleration = 0;

	TransitionPoint(unsigned int Index) : index(Index), weight(spring_mass / spring_parts) {
		// If the first point is fixed, it doesn`t require any weight to calculate acceleration (it always will be zero)
		if (fix_first_point && (Index == 0)) weight = 0;
		// Make the last point heavier if this option is enabled in constants.h
		if (use_weight_on_the_end && (Index == spring_parts)) weight += weight_on_the_end;
	};

	force get_force();

	acceleration get_acceleration();

	void update_acceleration();
};

