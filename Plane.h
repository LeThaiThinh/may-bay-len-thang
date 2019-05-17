#ifndef PLANE_H
#define PLANE_H

#include "BaseObject.h"

class Plane : public BaseObject{

public:
	Plane();
	~Plane();

	void HandleInput(SDL_Event e);
	bool Update(const Map &map);

	bool Collision(const Map& map);
	

private:
	int x_val_;
	int y_val_;
};

#endif