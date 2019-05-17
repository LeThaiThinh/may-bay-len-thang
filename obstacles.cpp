
#include "stdafx.h"
#include "obstacles.h"
#include <fstream>

void ObstaclesMap::LoadObstaclesMap(char* name)
{
	
	std::ifstream file;
	file.open(name, std::ios::in);

	game_Obstaclesmap_.max_x_ =0;
	game_Obstaclesmap_.max_y_ =0;

	for (int i=0; i< MAX_MAP_Y; i++)
	{
		for (int j=0; j< MAX_MAP_X; j++)
		{
			file >> game_Obstaclesmap_.tile[i][j];
			int val = game_Obstaclesmap_.tile[i][j];
			if ( val < 0 )
			{
				if ( j > game_Obstaclesmap_.max_x_ )
					game_Obstaclesmap_.max_x_ = j;
				if ( i > game_Obstaclesmap_.max_y_ )
					game_Obstaclesmap_.max_y_ = i;
			}
		}
	}

	game_Obstaclesmap_.max_x_ = (game_Obstaclesmap_.max_x_ +1) *TILE_SIZE;
	game_Obstaclesmap_.max_y_ = (game_Obstaclesmap_.max_y_ +1) *TILE_SIZE;

	game_Obstaclesmap_.start_x_ =0;
	game_Obstaclesmap_.start_y_ =0;

	game_Obstaclesmap_.file_name_ = name;


}

void ObstaclesMap::LoadObstacles(SDL_Renderer* screen)
{
	

		Obstacles_mat.loadImage("image/-1.png", screen);



}
//
void ObstaclesMap::DrawObstaclesMap(SDL_Renderer* screen)
{
	int x1 =0;
	int x2 =0;

	int y1 =0;
	int y2 =0;

	int map_x =0;
	int map_y =0;

	map_x = game_Obstaclesmap_.start_x_/TILE_SIZE;
	x1 = (game_Obstaclesmap_.start_x_%TILE_SIZE)*-1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0  ? 0 : TILE_SIZE); 
                        
	
	map_y = game_Obstaclesmap_.start_y_/TILE_SIZE;
	y1 = (game_Obstaclesmap_.start_y_%TILE_SIZE)*-1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for ( int i = y1; i < y2 ; i+= TILE_SIZE )
	{
		map_x = game_Obstaclesmap_.start_x_/TILE_SIZE;
		for( int j = x1; j < x2; j+= TILE_SIZE)
		{
			int val = game_Obstaclesmap_.tile[map_y][map_x];
			if ( val < 0)
			{
				Obstacles_mat.SetRect(j, i);
				Obstacles_mat.Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}



void ObstaclesMap::Update()
{
	
	
		if(game_Obstaclesmap_.start_x_ + SCREEN_WIDTH < TILE_SIZE * MAX_MAP_X)
			game_Obstaclesmap_.start_x_ += 16;
		else game_Obstaclesmap_.start_x_ = 0;
	
}
