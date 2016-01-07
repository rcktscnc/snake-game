#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

namespace asd {

	const int BODY_SCALE = 15;
	const int WORLD_WIDTH = BODY_SCALE * 20;
	const int WORLD_HEIGHT = BODY_SCALE * 20;

	class Character : public Entity {
	private:
		static int id_count;
		int id;
		sf::RectangleShape shape;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f pos;
	public:
		Character(const char* file_name, sf::Vector2f _shape, const sf::Vector2f& _pos);
		int get_id() override;
		void show() override;
		void hide() override;
		void spawn() override;
		void destroy() override;
		void move(int X, int Y) override;
		void draw(sf::RenderWindow& window);
		sf::RectangleShape get_shape();
		sf::Vector2f get_pos();
		void Character::new_location(int x, int y);
		void color(int r, int g, int b);
	};

	int Character::id_count = 0;

	Character::Character(const char* file_name, sf::Vector2f _shape, const sf::Vector2f& _pos)
		: pos(_pos), shape(_shape) {
		id = id_count++;
		texture.loadFromFile(file_name);
		sprite.setTexture(texture);
		shape.setTexture(&texture);
		shape.setPosition(pos);
	}

	int Character::get_id() {
		return id;
	}

	void Character::show() { }

	void Character::hide() { }

	void Character::spawn() { }

	void Character::destroy() { }

	void Character::move(int x, int y) { 
		pos.x += x;
		pos.y += y;
		shape.setPosition(pos);
	}

	void Character::new_location(int x, int y) {
		pos.x = (float)x;
		pos.y = (float)y;
		shape.setPosition(pos);
	}

	void Character::draw(sf::RenderWindow& window) { window.draw(shape); }
	sf::RectangleShape Character::get_shape() { return shape; }
	sf::Vector2f Character::get_pos() { return pos; }
	void Character::color(int r, int g, int b) { shape.setFillColor(sf::Color(r, g, b)); }

}
#endif // _CHARACTER_H