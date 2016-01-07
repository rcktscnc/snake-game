#ifndef _SNAKE_H
#define _SNAKE_H

#include "Character.h"
#include <SFML/Audio.hpp>
#include <vector>

namespace asd {

	enum Direction {
		UP = 1,
		LEFT = 2,
		DOWN = 3,
		RIGHT = 4
	};

	class Snake : public Character {
	private:
		Direction direction;
		int size;
		std::vector<sf::RectangleShape> body_position;
		sf::SoundBuffer eat_sound_buffer;
		sf::Sound eat_sound;
		sf::SoundBuffer death_sound_buffer;
		sf::Sound death_sound;
	public:
		Snake(const char* file_name, sf::Vector2f _shape, const sf::Vector2f& _pos);
		void move();
		void draw(sf::RenderWindow& window);
		void set_direction(Direction _direction);
		Direction get_direction();
		void eat();
		bool collision();
		bool body_collision(const sf::Vector2f& _pos);
		int get_size();
	};

	Snake::Snake(const char* file_name, sf::Vector2f _shape, const sf::Vector2f& _pos):
		Character(file_name, _shape, _pos),
		direction(Direction::RIGHT),
		size(3)		
	{
		for (int i = 0; i < size; i++) {
			body_position.push_back(sf::RectangleShape(sf::Vector2f((float)BODY_SCALE, (float)BODY_SCALE)));
			body_position[i].setPosition(_pos.x - ((i+1) * BODY_SCALE), _pos.y);
		}
		eat_sound_buffer.loadFromFile("eat-sound.ogg");
		eat_sound.setBuffer(eat_sound_buffer);
		eat_sound.setVolume(10);
		eat_sound.setPitch(1.5);

		death_sound_buffer.loadFromFile("snake-death-no-scream.ogg");
		death_sound.setBuffer(death_sound_buffer);
		death_sound.setVolume(10);
	}

	void Snake::move() {
		int b_size = body_position.size() - 1;
		for (int i = b_size; i > 0; i--) {
			body_position[i] = body_position[i-1];
		}
		body_position[0] = Character::get_shape();

		switch (direction) {
		case Direction::UP:
			Character::move(0, -BODY_SCALE); break;
		case Direction::LEFT:
			Character::move(-BODY_SCALE, 0); break;
		case Direction::DOWN:
			Character::move(0, BODY_SCALE); break;
		case Direction::RIGHT:
			Character::move(BODY_SCALE, 0); break;
		}
	}

	void Snake::draw(sf::RenderWindow& window) {
		for (auto& e : body_position)
			window.draw(e);
		Character::draw(window);
	}

	void Snake::set_direction(Direction _direction) {
		if (direction == Direction::UP && _direction != Direction::DOWN ||
			direction == Direction::LEFT && _direction != Direction::RIGHT || 
			direction == Direction::DOWN && _direction != Direction::UP || 
			direction == Direction::RIGHT && _direction != Direction::LEFT) 
		{
			direction = _direction;
		}
		
	}

	Direction Snake::get_direction() { return direction; }

	void Snake::eat() {
		++size;
		body_position.push_back(body_position.back());
		eat_sound.play();
	}

	bool Snake::collision() {
		for (auto& e : body_position) {
			if (e.getPosition() == Character::get_pos()) {
				death_sound.play();
				return true;
			}
		}
		if (Character::get_pos().x > WORLD_WIDTH - BODY_SCALE ||
			Character::get_pos().x < 0 ||
			Character::get_pos().y > WORLD_HEIGHT - BODY_SCALE ||
			Character::get_pos().y < 0)
		{
			death_sound.play();
			return true;
		}
		return false;
	}

	bool Snake::body_collision(const sf::Vector2f& _pos) {
		for (auto& e : body_position)
			if (e.getPosition() == _pos) return true;
		return false;
	}

	int Snake::get_size() { return size; }
}
#endif // _SNAKE_H
