#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* des, std::string path)
{
	loadImage(path,  des);
}


Bullet::~Bullet()
{
	SDL_DestroyTexture(p_object_);
}

bool Bullet::Collision_obs(const Map& map ){


	int offset = 8;
	SDL_Rect collision_rect = { rect_.x, rect_.y + offset, rect_.w, rect_.h - offset };

	
	int x1 =0; 
	int x2 =0; 

	int y1 =0; 
	int y2 =0;

	int map_x =0;  
	int map_y =0;

	map_x = map.start_x_/TILE_SIZE;   
	x2 = x1 + SCREEN_WIDTH + (x1 == 0  ? 0 : TILE_SIZE); 
	                   
	map_y = map.start_y_/TILE_SIZE;
	y1 = (map.start_y_%TILE_SIZE)*-1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for ( int i = y1; i < y2 ; i+= TILE_SIZE )
	{
		map_x = map.start_x_/TILE_SIZE;
		for( int j = x1; j < x2; j+= TILE_SIZE)
		{
			int val = map.tile[map_y][map_x];
			if ( val < 0 )
			{
				SDL_Point tile_BotRight = { j + TILE_SIZE, i + TILE_SIZE };
				if ( SDL_PointInRect(&tile_BotRight, &collision_rect) ) 
				{
					return 1;
				}
			}
			map_x++;
		}
		map_y++;
	}
	return 0;	
}


void Bullet::update()
{   	
		rect_.x += 20;
}
   