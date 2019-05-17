
#include "stdafx.h"
#include "Plane.h"


Plane::Plane() {
	x_val_ = 0;
	y_val_ = 3;
}
Plane::~Plane() {

}
void Plane::HandleInput(SDL_Event e){
	if(e.type == SDL_KEYDOWN)
	{
	switch (e.key.keysym.sym)
		{
		case SDLK_w:
			y_val_ = -8;
			break;
		case SDLK_s:
			//todo
			y_val_ = 8;
			break;
		case SDLK_d:
			x_val_ = 8;
			break;
		case SDLK_a:
			x_val_ = -8;
			break;
		}
	}
	else if(e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			//to do
			y_val_ = 3;
			break;
		case SDLK_s:
			//todo
			y_val_ = 3;
			break;
		case SDLK_d:
			x_val_ = 0;
			break;
		case SDLK_a:
			x_val_ = 0;
			break;
		}
	}
		
}

bool Plane::Collision(const Map& map){


	int offset = 8;
	SDL_Rect collision_rect = { rect_.x, rect_.y + offset, rect_.w, rect_.h - offset };

	
	int x1 =0; 
	int x2 =0; 

	int y1 =0; 
	int y2 =0;

	int map_x =0;  
	int map_y =0;

	map_x = map.start_x_/TILE_SIZE;
	x1 = (map.start_x_%TILE_SIZE)*-1;
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
			if ( val>0 )
			{
				SDL_Point tile_TopLeft = { j, i };
				SDL_Point tile_TopRight = { j + TILE_SIZE, i };
				SDL_Point tile_BotLeft = { j, i + TILE_SIZE };
				SDL_Point tile_BotRight = { j + TILE_SIZE, i + TILE_SIZE };

				if (SDL_PointInRect(&tile_TopLeft, &collision_rect) ||
					SDL_PointInRect(&tile_TopRight, &collision_rect) ||
					SDL_PointInRect(&tile_BotLeft, &collision_rect) ||
					SDL_PointInRect(&tile_BotRight, &collision_rect)) 
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

bool Plane::Update(const Map& map)
{
	if (Collision(map)) {
		return 1;
	}

	if (!(rect_.x + x_val_ > 0 && rect_.x + x_val_ + rect_.w < SCREEN_WIDTH)) return 0;
	if (!(rect_.y + y_val_ > 0 && rect_.y + y_val_ + rect_.h < SCREEN_HEIGHT)) return 0;
	
	if (x_val_ || y_val_) {
		rect_.x += x_val_;
		rect_.y += y_val_;
	}

	return 0;
		
}