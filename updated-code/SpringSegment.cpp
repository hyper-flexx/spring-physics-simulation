#include "SpringSegment.h"
#include "global.h"
#include <cmath>

force SpringSegment::get_force() {
	// Calculate force of a section using Hooke`s law
	return (part_current - (spring_shrunk / spring_parts)) * spring_coefficient;
}

void SpringSegment::update_length(simulation_time t) {
	// Get the length by substracting coordinates of 2 near points
	length delta = (((points[index + 1]->speed * t) + ((points[index + 1]->point_acceleration * t * t) / 2))) - (((points[index]->speed * t) + ((points[index]->point_acceleration * t * t) / 2)));
	if (std::abs(delta) <= 10E-10) return;
	if (part_current + delta > minimum_spring_length / spring_parts) {
		part_current += delta;
		points[index + 1]->speed += points[index + 1]->point_acceleration * t;
		points[index]->speed += points[index]->point_acceleration * t;
		return;
	}
	else {
		length recursive_delta = minimum_spring_length / spring_parts - part_current;
		double a = (points[index + 1]->point_acceleration - points[index]->point_acceleration) / 2;
		double b = (points[index + 1]->speed - points[index]->speed);
		double c = -recursive_delta;
		double acnb = (a * c) / (b * b);
		simulation_time recursive_time = -(((1 + acnb + 2 * acnb * acnb + 5 * acnb * acnb * acnb) * c) / b);
		part_current = minimum_spring_length / spring_parts;
		points[index + 1]->speed += points[index + 1]->point_acceleration * recursive_time;
		points[index]->speed += points[index]->point_acceleration * recursive_time;
		if (index == 0) points[index + 1]->speed += ((-points[index + 1]->speed) * (cor + 1));
		else {
			velocity v1 = points[index]->speed - ((points[index]->speed - points[index + 1]->speed) * points[index + 1]->weight * (cor + 1) / (points[index]->weight + points[index + 1]->weight));
			velocity v2 = points[index + 1]->speed + ((points[index]->speed - points[index + 1]->speed) * points[index]->weight * (cor + 1) / (points[index]->weight + points[index + 1]->weight));
			points[index + 1]->speed = v2;
			points[index]->speed = v1;
		}
		return update_length(t - recursive_time);
	}
}