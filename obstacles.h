
#ifndef OBSTACLES_H
#define OBSTACLES_H
#include "Bullet.h"

class Obstacles : public BaseObject 
{
public:
	Obstacles() {;}
	~Obstacles() {;}
};

class ObstaclesMap
{
public:
	ObstaclesMap() {;}
	~ObstaclesMap() {;}

	void LoadObstaclesMap(char* name);             
	void LoadObstacles(SDL_Renderer* screen ); 
	void DrawObstaclesMap(SDL_Renderer* screen );
	//bool Collision(Bullet&  bullet);

	void Update();
	Map get_game_Obstaclesmap() const {return game_Obstaclesmap_;}

private:
	Map game_Obstaclesmap_;
	Obstacles Obstacles_mat;
};

#endif