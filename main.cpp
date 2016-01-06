//Dependencies for static libraries: winmm;gdi32;opengl32;libfreetype;libjpeg;s

#include <iostream>
#include "Logic.h"


int main(int argc, char **argv) {
	sf::RenderWindow window(sf::VideoMode(asd::WORLD_WIDTH, asd::WORLD_HEIGHT),
		"MilleniumTEKNoobleSnakeBIT-E", sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	sf::Clock clock;

	asd::Logic manager(window);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) 
					{ manager.set_direction(asd::Direction::UP); }
				if (event.key.code == sf::Keyboard::A) 
					{ manager.set_direction(asd::Direction::LEFT); }
				if (event.key.code == sf::Keyboard::S) 
					{ manager.set_direction(asd::Direction::DOWN); }
				if (event.key.code == sf::Keyboard::D) 
					{ manager.set_direction(asd::Direction::RIGHT); }
				if (event.key.code == sf::Keyboard::E) 
					{ manager.eat(); }
			}
		}

		manager.move_snake();
		window.clear();
		manager.draw();
		window.display();
	}
	return 0;
}
