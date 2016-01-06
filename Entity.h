#ifndef _ENTITY_H
#define _ENTITY_H

namespace asd {
	class Entity {
	public:
		virtual int get_id() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void spawn() = 0;
		virtual void destroy() = 0;
		virtual void move(int x, int y) = 0;
		//virtual ~Entity() = 0;
	};
}
#endif // _ENTITY_H