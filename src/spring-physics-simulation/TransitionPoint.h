#pragma once

#include "constants.h"

class TransitionPoint
{
private:
	unsigned int index;
public:
	mass weight;
	length coordinate;
	velocity speed = 0;
	acceleration point_acceleration = 0;

	TransitionPoint(unsigned int Index) : coordinate((double)Index* spring_start_length / spring_parts), index(Index), weight(spring_mass / spring_parts) {
		if (fix_first_point && (Index == 0)) weight = 0;
		if (use_weight_on_the_end && (Index == spring_parts)) weight = weight_on_the_end;
	};

	force get_force();

	acceleration get_acceleration();

	void update_acceleration();

	void update_position(time t);
};

