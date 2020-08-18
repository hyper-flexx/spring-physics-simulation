#include <iostream>
#include "TransitionPoint.h"
#include "SpringSegment.h"

SpringSegment* parts[spring_parts];
TransitionPoint* points[spring_parts + 1];

void main() {
	// Initializing points[] and parts[], that must receive an ID for each element
	for (unsigned int i = 0; i < spring_parts + 1; i++) points[i] = (new TransitionPoint(i));
	for (unsigned int i = 0; i < spring_parts; i++) parts[i] = (new SpringSegment(i));

	// Initializing counters
	volatile time current_time = 0;
	unsigned long long iteration_counter = 0;
	
	for (;;) {
		// Step 1. Recalculate forces and accelerations.
		for (unsigned int i = (fix_first_point ? 1 : 0); i < spring_parts + 1; i++) points[i]->update_acceleration();

		// Step 2. Move centers of the spring sections
		for (unsigned int i = (fix_first_point ? 1 : 0); i < spring_parts + 1; i++) points[i]->update_position(tick);

		// Step 3. Calculate the length of each section
		for (unsigned int i = 0; i < spring_parts; i++) parts[i]->update_length();

		// Step 4. Increase the simulation time counter
		current_time += tick;

		// Step 5. Display results after each 10000 iterations
		iteration_counter++;
		if (iteration_counter % 10000 == 0) { 
			if (!fix_first_point) std::cout << points[0]->coordinate << " ";
			std::cout << points[spring_parts]->coordinate << " " << current_time << std::endl; 
		}
	}

}