#include "constants.h"
#include <iostream>
#include "TransitionPoint.h"
#include "SpringSegment.h"
#ifdef VISUALIZE
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <sstream>
sf::RectangleShape diagram[spring_parts];
#endif

SpringSegment* parts[spring_parts];
TransitionPoint* points[spring_parts + 1];

int main() {
#ifdef VISUALIZE
	// Initializing visualizer
	sf::RenderWindow window(sf::VideoMode(window_size_x, window_size_y), "Nya~", sf::Style::Close | sf::Style::Titlebar);
	sf::CircleShape s_center, s_end;
	sf::RectangleShape s_cover;
	s_cover.setFillColor(sf::Color(66, 135, 245, 100));
	const float positionindicator = 31;
	s_cover.setPosition(sf::Vector2f(0, positionindicator));
	s_cover.setSize(sf::Vector2f(window_size_x, 9));
	s_center.setFillColor(sf::Color(255, 0, 0));
	s_end.setFillColor(sf::Color(0, 255, 0));
	s_center.setRadius(3);
	s_end.setRadius(3);
	s_center.setPosition(sf::Vector2f(window_size_x / 2 - 3, positionindicator + 3));
	s_end.setPosition(sf::Vector2f(window_size_x - 3, positionindicator + 3));
	int prescaler = 1;

	sf::Font josefin;
	sf::Font josefin_bold;
	if (!josefin.loadFromFile("JosefinSans-SemiBold.ttf")) return 1;
	if (!josefin_bold.loadFromFile("JosefinSans-Bold.ttf")) return 1;
	sf::Text title = sf::Text("spring-physics-simulation", josefin_bold, 40);
	title.setPosition(sf::Vector2f(20, window_size_y - 130));
	sf::Text counter_text = sf::Text("", josefin, 24);
	counter_text.setPosition(sf::Vector2f(4, 0));
	sf::Text copyright = sf::Text("https://github.com/hyper-flexx/spring-physics-simulation \nCopyright © marchie\nGNU General Public License v3.0", josefin, 20);
	copyright.setPosition(sf::Vector2f(20, window_size_y - 80));
	copyright.setFillColor(sf::Color(66, 135, 245, 100));
	title.setFillColor(sf::Color(50, 100, 255, 100));
	sf::Clock clock;

	for (unsigned int i = 0; i < spring_parts; i++) {
		diagram[i].setSize(sf::Vector2f((float)window_size_x / (spring_parts * 2 + 1), 1));
		diagram[i].setPosition(sf::Vector2f((((float)window_size_x) / (spring_parts * 2 + 1)) * (i * 2 + 1), window_size_y / 2));
		diagram[i].setFillColor(sf::Color(255, 255, 255));
	}
#endif

	// Initializing points[] and parts[], that must receive an ID for each element
	for (unsigned int i = 0; i < spring_parts + 1; i++) points[i] = (new TransitionPoint(i));
	for (unsigned int i = 0; i < spring_parts; i++) parts[i] = (new SpringSegment(i));

	// Initializing counters
	volatile simulation_time current_time = 0;
	unsigned long long iteration_counter = 0;

	// Variables used in overlap tracker
	bool side = true;
	simulation_time last_time = 0;
	
#ifndef VISUALIZE
	for (;;) {
#else
	while (window.isOpen()) {
#endif
		// Step 1. Recalculate forces and accelerations.
		for (unsigned int i = (fix_first_point ? 1 : 0); i < spring_parts + 1; i++) points[i]->update_acceleration();

		// Step 2. Move transition points
		for (unsigned int i = (fix_first_point ? 1 : 0); i < spring_parts + 1; i++) points[i]->update_position(tick);

		// Step 3. Calculate the length of each section
		for (unsigned int i = 0; i < spring_parts; i++) parts[i]->update_length();

		// Step 4. Increase the simulation time counter
		current_time += tick;

		// Step 5. Display results after each 10000 iterations
		iteration_counter++;
		if (iteration_counter % 1000 == 0) { 
#ifdef VISUALIZE
			// Render visualization
			window.clear();
			for (unsigned int i = 0; i < spring_parts; i++) {
				diagram[i].setSize(sf::Vector2f(diagram[i].getSize().x, parts[i]->part_current * spring_parts * 10 * prescaler));
				window.draw(diagram[i]);
			}
			window.draw(s_cover);
			s_end.setPosition(sf::Vector2f(window_size_x / 2 - 3 + points[spring_parts]->coordinate / 20 * window_size_x, positionindicator + 3));
			if (!fix_first_point) s_center.setPosition(sf::Vector2f(window_size_x / 2 - 3 + points[0]->coordinate / 20 * window_size_x, positionindicator + 3));
			window.draw(s_end);
			window.draw(s_center);

			int fps = (int)((double)1 / (clock.getElapsedTime().asSeconds()));
			clock.restart();
			std::stringstream fps_str;
			fps_str.precision(3);
			fps_str << "Simulated " << current_time << " seconds | Current FPS is " << fps - fps % 5 << ".";
			counter_text.setString(fps_str.str());

			window.draw(counter_text);
			window.draw(title);
			window.draw(copyright);

			window.display();
#endif
		}

		// Print time differences of moments when first and last points are overlapping
		if (points[spring_parts]->coordinate - points[0]->coordinate <= 0 && side) { std::cout << current_time - last_time << "\n"; last_time = current_time; side = false; }
		else if (points[spring_parts]->coordinate - points[0]->coordinate >= 0 && (!side)) { std::cout << current_time - last_time << "\n"; last_time = current_time; side = true; }
		

#ifdef VISUALIZE
		// Catch events from window
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			// Close it
			case sf::Event::Closed:
				window.close();
				break;
			// Rescale visualization
			case sf::Event::MouseWheelMoved:
				prescaler += (float)evnt.mouseWheel.delta;
				if (prescaler < 1) prescaler = 1;
				break;
			}
		}
#endif
	}
	return 0;
}