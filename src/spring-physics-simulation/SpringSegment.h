#pragma once
#include "constants.h"

class SpringSegment
{
private:
	unsigned int index;
public:
	length part_current;

	SpringSegment(unsigned int Index) : part_current(spring_start_length / spring_parts), index(Index) {}

	force get_force();

	void update_length();
};

