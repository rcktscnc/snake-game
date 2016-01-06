#ifndef _LOGIC_H
#define _LOGIC_H

#include "Snake.h"
#include <random>
#include <ctime>

namespace asd {

	const int SPEED = 200;

	class Logic {
	private:
		Snake snake;
		Character food;
		sf::Clock timer;
		sf::Clock last_turn;
		sf::RenderWindow& window;
	public:
		Logic(sf::RenderWindow& _window);
		void move_snake();
		void draw();
		void set_direction(Direction direction);
		void eat();
		void move_food();
		bool collision();
	};

	Logic::Logic(sf::RenderWindow& _window):
		snake("snake-block.png",
			sf::Vector2f(asd::BODY_SCALE, asd::BODY_SCALE),
			sf::Vector2f(0, 0)),
		food("snake-block.png", 
			sf::Vector2f(asd::BODY_SCALE, asd::BODY_SCALE),
			sf::Vector2f(0, 0)),
		window(_window)
	{
		food.color(255, 50, 50);
		move_food();
	}

	void Logic::move_snake() {
		if (timer.getElapsedTime().asMilliseconds() >= SPEED) {
			snake.move();
			timer.restart(); 
			if (collision()) { std::cout << "COLLISION!" << std::endl; }
		}
	}

	void Logic::draw() {
		snake.draw(window);
		food.draw(window);
	}

	void Logic::set_direction(Direction direction) {
		if (last_turn.getElapsedTime().asMilliseconds() >= SPEED &&
			direction != snake.get_direction())
		{
			snake.set_direction(direction);
			last_turn.restart();
		}
	}
	
	void Logic::eat() { snake.eat(); }

	void Logic::move_food() {
		int x, y;
		std::srand(std::time(0));
		while (true) {
			do {
				x = (std::rand() % (int)(WORLD_WIDTH - BODY_SCALE));
			} while (x % BODY_SCALE != 0);

			do {
				y = (std::rand() % (int)(WORLD_HEIGHT - BODY_SCALE));
			} while (y % BODY_SCALE != 0);

			if (snake.body_collision(sf::Vector2f(x, y)) == false)
				break;
		}
		food.new_location(x, y);
	}

	bool Logic::collision() {
		if (snake.get_pos() == food.get_pos()) {
			std::cout << snake.get_pos().x << "\n";
			move_food();
			snake.eat();
		}
		return snake.collision(); 
	}

}
#endif // _LOGIC_H