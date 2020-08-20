#include "TransitionPoint.h"
#include "global.h"

force TransitionPoint::get_force() {
	if (index == spring_parts) {
		return (-parts[index - 1]->get_force());
	}
	else if (index == 0) return (parts[index]->get_force());
	else {
		return (parts[index]->get_force() - parts[index - 1]->get_force());
	}
}

acceleration TransitionPoint::get_acceleration() {
	return ((get_force()) / weight);
}

void TransitionPoint::update_acceleration() {
	point_acceleration = get_acceleration();
}

void TransitionPoint::update_position(simulation_time t) {
	coordinate += ((speed * t) + ((point_acceleration * t * t) / 2));
	speed += point_acceleration * t;
}