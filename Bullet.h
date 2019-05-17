#ifndef BULLET_H
#define BULLET_H
#include "BaseObject.h"

class Bullet : public BaseObject
{
public:
	Bullet(SDL_Renderer* des, std::string path);
	~Bullet();
	bool Collision_obs( const Map& map);
	void update();
	//bool exist;

private:
	

};
#endif 