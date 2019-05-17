
#ifndef GAME_MAP_H
#define GAME_MAP_H


#include "BaseObject.h"

#define MAX_TILES 6

class TileMat : public BaseObject 
{
public:
	TileMat() {;}
	~TileMat() {;}
};

class GameMap
{
public:
	GameMap() {;}
	~GameMap() {;}

	void LoadMap(char* name);               
	void LoadTiles(SDL_Renderer* screen ); 
	void DrawMap(SDL_Renderer* screen );

	void Update();
	Map get_game_map() const {return game_map_;}

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};




#endif