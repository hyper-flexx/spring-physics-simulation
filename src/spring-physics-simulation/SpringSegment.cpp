#include "SpringSegment.h"
#include "global.h"

force SpringSegment::get_force() {
	// Calculate force of a section using Hooke`s law
	return (part_current - (spring_shrunk / spring_parts)) * spring_coefficient;
}

void SpringSegment::update_length() {
	// Get the length by substracting coordinates of 2 near points
	part_current = points[index + 1]->coordinate - points[index]->coordinate;
}