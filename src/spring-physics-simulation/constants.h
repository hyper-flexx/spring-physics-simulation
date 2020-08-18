#pragma once
typedef double mass, force, acceleration, velocity, length, time;

// !!! WARNING: DO NOT CHANGE A CONSTANT BELOW !!!
// Decreasing it will make simulation extremely slow, while increasing will cause calculation errors and even program crashes!
const time tick = 0.0000001;				// Amount of time to be simulated in one iteration (seconds)

// Next constants can be freely changed
const mass spring_mass = 2;					// Weight of the spring (kilograms)
const length spring_shrunk = 2;				// Length of the shrunk spring (meters)
const length spring_start_length = 1;		// Length of the spring at the simulation`s beginning (meters)
const unsigned int spring_parts = 500;		// Number of segments
const double spring_coefficient = 10000;	// Coefficient of elasticity (Newtons per meter)
const bool fix_first_point = false;			// If true, the first point will ignore the force acting on it
const bool use_weight_on_the_end = true;	// Enable this to simulate a spring with a weight on the last segment
const mass weight_on_the_end = 2;			// Weight on last segment (kilograms)