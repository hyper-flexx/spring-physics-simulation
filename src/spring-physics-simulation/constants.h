#pragma once
typedef double mass, force, acceleration, velocity, length, simulation_time;

// WARNING: CHANGE THIS CONSTANT CAREFULLY
// !!!! READ IMPORTANT INFORMATION BEFORE CHANGING: https://github.com/hyper-flexx/spring-physics-simulation/wiki/Tick !!!!
const simulation_time tick = 0.0000001;		// Amount of time to be simulated in one iteration (seconds)

// Next constants can be freely changed
const mass spring_mass = 2;					// Weight of the spring (kilograms)
const length spring_shrunk = 0;				// Length of the shrunk spring (meters)
const length spring_start_length = 10;		// Length of the spring at the simulation`s beginning (meters)
const unsigned int spring_parts = 800;		// Number of segments
const double spring_coefficient = 10000;	// Coefficient of elasticity (Newtons per meter)
const bool fix_first_point = false;			// If true, the first point will ignore the force acting on it
const bool use_weight_on_the_end = true;	// Enable this to simulate a spring with an additional weight on the last segment
const mass weight_on_the_end = 1;			// Weight on last segment (kilograms)

/* --- SFML ---
	https://github.com/hyper-flexx/spring-physics-simulation/wiki/SFML
	In case of enabled visualisation, this project should be linked with SFML library, that requires following:
		Path for libraries
			\SFML-<version>\lib
		Path for include files
			\SFML-<version>\include
		Additional dependencies for static linking
			sfml-graphics-s.lib
			freetype.lib
			sfml-window-s.lib
			sfml-system-s.lib
			opengl32.lib
			winmm.lib
			gdi32.lib
		Additional dependencies for dynamic linking
			sfml-graphics.lib
			freetype.lib
			sfml-window.lib
			sfml-system.lib
			opengl32.lib
			winmm.lib
			gdi32.lib
			--- WARNING --- If you wanna use dynamic linking, remove "#define SFML_STATIC" from Source.cpp and DON`T FORGET ABOUT DLLs!
*/

#define VISUALIZE											// Put "//" before this line to disable result visualisation
const unsigned int window_size_x =
	(spring_parts >= 500) ? (spring_parts * 2 + 1) : 1000;	// Width of the visualizer`s window
const unsigned int window_size_y = 1000;					// Heigth of the visualizer`s window