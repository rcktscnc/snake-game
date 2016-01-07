#ifndef _LOGIC_H
#define _LOGIC_H

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Snake.h"
#include <random>
#include <ctime>

namespace asd {

	const int DELAY = 150;

	class Logic {
	private:
		Snake snake;
		Character food;
		sf::Clock timer;
		sf::Clock last_turn;
		sf::SoundBuffer song_sound_buffer;
		sf::Sound song_sound;
		sf::RenderWindow& window;
	public:
		Logic(sf::RenderWindow& _window);
		bool move_snake();
		void draw();
		void set_direction(Direction direction);
		void eat();
		void move_food();
		bool collision();
		void play_music();
		void stop_music();
		bool check_win();
	};

	Logic::Logic(sf::RenderWindow& _window):
		snake("snake-block.png",
			sf::Vector2f((float)asd::BODY_SCALE, (float)asd::BODY_SCALE),
			sf::Vector2f(0, 0)),
		food("snake-block.png", 
			sf::Vector2f((float)asd::BODY_SCALE, (float)asd::BODY_SCALE),
			sf::Vector2f(0, 0)),
		window(_window)
	{
		food.color(255, 50, 50);
		move_food();
		song_sound_buffer.loadFromFile("tetris-song.ogg");
		song_sound.setBuffer(song_sound_buffer);
	}

	bool Logic::move_snake() {
		if (timer.getElapsedTime().asMilliseconds() >= DELAY) {
			snake.move();
			timer.restart();
			if (collision()) return false;
		}
		return true;
	}

	void Logic::draw() {
		snake.draw(window);
		food.draw(window);
	}

	void Logic::set_direction(Direction direction) {
		if (last_turn.getElapsedTime().asMilliseconds() >= DELAY &&
			direction != snake.get_direction())
		{
			snake.set_direction(direction);
			last_turn.restart();
		}
	}
	
	void Logic::eat() { snake.eat(); }

	void Logic::move_food() {
		int x, y;
		std::srand((unsigned int)std::time(0));
		while (true) {
			do {
				x = (std::rand() % (int)(WORLD_WIDTH - BODY_SCALE));
			} while (x % BODY_SCALE != 0);

			do {
				y = (std::rand() % (int)(WORLD_HEIGHT - BODY_SCALE));
			} while (y % BODY_SCALE != 0);

			if (snake.body_collision(sf::Vector2f((float)x, (float)y)) == false &&
				food.get_pos() != sf::Vector2f((float)x, (float)y))
				break;
		}
		food.new_location(x, y);
	}

	bool Logic::collision() {
		if (snake.get_pos() == food.get_pos()) {
			move_food();
			snake.eat();
		}
		return snake.collision(); 
	}

	void Logic::play_music() { 
		song_sound.setLoop(true);
		song_sound.setPitch(0.8f);
		song_sound.setVolume(5);
		song_sound.play();
	}

	void Logic::stop_music() { song_sound.pause(); }

	bool Logic::check_win() {
		return snake.get_size() == (WORLD_WIDTH / BODY_SCALE) * (WORLD_HEIGHT / BODY_SCALE) ? true : false;
	}
}
#endif // _LOGIC_H