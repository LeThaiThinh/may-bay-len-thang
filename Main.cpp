#include "stdafx.h"
#include "CommonFunction.h"
#include "BaseObject.h"
#include "gamemap.h"
#include "Plane.h"
#include "Bullet.h"
#include "TextObject.h"
#include "obstacles.h"

BaseObject g_background ;
BaseObject g_menu_background;
BaseObject g_menu_background_endgame;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;
TTF_Font* font_score = NULL;
Mix_Chunk* chunk = NULL;
Mix_Chunk* chunk2 = NULL;
Mix_Chunk* chunk3 = NULL;
Mix_Chunk* chunk4 = NULL;

Mix_Music* music = NULL;
Mix_Music* music_menu = NULL;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if ( ret < 0 ) return false;

	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Ngoc HD =))))))))))))))) ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	if (g_window == NULL )
	{
		success = false ;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if ( g_screen == NULL )
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if ( !(IMG_Init(imgFlags) && imgFlags) )
				success= false;
		}
		if (TTF_Init() == -1)
		{
			success = false;
		}

		font_time = TTF_OpenFont("font/Blazed.ttf", 27);
		if ( font_time == NULL)
		{
			std::cout << SDL_GetError();
			success = false;
		}

		font_menu = TTF_OpenFont("font/Blazed.ttf", 50);
		if ( font_menu == NULL)
		{
			std::cout << SDL_GetError();
			success = false;
		}
		font_score = TTF_OpenFont("font/BLKCHCRY.TTF", 50);
		if ( font_score == NULL)
		{
			std::cout << SDL_GetError();
			success = false;
		}
	
	}
	return success;
}


bool CheckFocus( int& x, int& y, SDL_Rect& rect )
{
	if ( (x >= rect.x) && (x <= rect.x + rect.w) && ( y >= rect.y) && (y<= rect.y + rect.h) )
	{
		return true;
	}
	return false;
}

 
void ShowMenu(SDL_Renderer* g_screen)
{
	
	Mix_PlayMusic(music_menu, -1 );
	g_menu_background.loadImage("image/Menugame.png", g_screen);
	g_menu_background.Render(g_screen );
	
	SDL_RenderPresent(g_screen);
}

void ShowMenu_endgame(SDL_Renderer* g_screen, std::string score, std::string highscore)
{
	SDL_Rect scoregamerect;
	scoregamerect.x= 880;
	scoregamerect.y= 280;
	TextObject scoregame;
	std::string showscore ="Your score : "+ score;
	scoregame.SetColor(RED_TEXT);
	scoregame.SetText(showscore, font_score, g_screen);
	scoregame.SetRect(scoregamerect.x, scoregamerect.y );

	SDL_Rect highscoregamerect;
	highscoregamerect.x= 800;
	highscoregamerect.y= 220;
	TextObject highscoregame;
	std::string showhighscore ="HIGH SCORE : "+ highscore;
	highscoregame.SetColor(RED_TEXT);
	highscoregame.SetText(showhighscore, font_score, g_screen);
	highscoregame.SetRect(highscoregamerect.x, highscoregamerect.y );

	g_menu_background_endgame.loadImage("image/Menugame.png", g_screen);
	g_menu_background_endgame.Render(g_screen );
	scoregame.Render(g_screen);
	highscoregame.Render(g_screen);
	SDL_RenderPresent(g_screen);
}

int ControlMenu(SDL_Renderer* g_screen, TTF_Font* font, bool& mouseclick)
{
	SDL_Rect luachon[2];
	luachon[0].x= 830;
	luachon[0].y= 400;
	luachon[1].x= 830;
	luachon[1].y= 520;
	
	

	TextObject text_menu[4]; 
	text_menu[0].SetColor(RED_TEXT);
	text_menu[0].SetText("Play Game", font_menu, g_screen);
	text_menu[0].SetRect(luachon[0].x, luachon[0].y);

	text_menu[2].SetColor(BLACK_TEXT);
	text_menu[2].SetText("Play Game", font_menu, g_screen);
	text_menu[2].SetRect(luachon[0].x, luachon[0].y);

	text_menu[1].SetColor(RED_TEXT);
	text_menu[1].SetText("Exit", font_menu, g_screen);
	text_menu[1].SetRect(luachon[1].x, luachon[1].y);

	text_menu[3].SetColor(BLACK_TEXT);
	text_menu[3].SetText("Exit", font_menu, g_screen);
	text_menu[3].SetRect(luachon[1].x, luachon[1].y);

	bool selected[2] = {0,0};
	int x_mouse =0;
	int y_mouse =0;
	SDL_Event m_event;

	text_menu[2].Render(g_screen);
	text_menu[3].Render(g_screen);
	SDL_RenderPresent(g_screen);

	while(true)
	{	
		while (SDL_PollEvent(&m_event))
		{

			switch(m_event.type)
			{
				case SDL_QUIT:
				{
					return 1;
				}					
				case SDL_MOUSEMOTION:
				{
					x_mouse = m_event.motion.x;
					y_mouse = m_event.motion.y;

					for ( int i=0; i<2; i++)
					{
						if ( CheckFocus( x_mouse, y_mouse, text_menu[i].GetRect()) )
						{
							if ( selected[i] == false)
							{
							selected[i] = 1;
							text_menu[i].Render(g_screen);
							}
						}
						else
						{
							if ( selected[i] == true)
							{
								selected[i] =0;
								text_menu[i+2].Render(g_screen);
							}
						}
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					x_mouse = m_event.button.x;
					y_mouse = m_event.button.y;

					for ( int i=0; i<2; i++)
					{
						if ( CheckFocus( x_mouse, y_mouse, text_menu[i].GetRect() ))
						{
							return i;
							mouseclick = true;
						}
					}
					break;
				}
				case SDL_KEYDOWN:
				{
					if (m_event.key.keysym.sym == SDLK_ESCAPE )
						return 1;
						mouseclick = true;
					break;
				}
			default:
				break;
			}
		SDL_RenderPresent(g_screen);
		}
	}
}

int ControlMenu_endgame(SDL_Renderer* g_screen, TTF_Font* font, bool& mouseclick)
{
	SDL_Rect luachon[2];
	luachon[0].x= 830;
	luachon[0].y= 400;
	luachon[1].x= 830;
	luachon[1].y= 520;

	TextObject text_menu[4]; 
	text_menu[0].SetColor(RED_TEXT);
	text_menu[0].SetText("Play Again", font_menu, g_screen);
	text_menu[0].SetRect(luachon[0].x, luachon[0].y);

	text_menu[2].SetColor(BLACK_TEXT);
	text_menu[2].SetText("Play Again", font_menu, g_screen);
	text_menu[2].SetRect(luachon[0].x, luachon[0].y);

	text_menu[1].SetColor(RED_TEXT);
	text_menu[1].SetText("Exit", font_menu, g_screen);
	text_menu[1].SetRect(luachon[1].x, luachon[1].y);

	text_menu[3].SetColor(BLACK_TEXT);
	text_menu[3].SetText("Exit", font_menu, g_screen);
	text_menu[3].SetRect(luachon[1].x, luachon[1].y);

	bool selected[2] = {0,0};
	int x_mouse =0;
	int y_mouse =0;
	SDL_Event m_event;

	text_menu[2].Render(g_screen);
	text_menu[3].Render(g_screen);
	SDL_RenderPresent(g_screen);

	while(true)
	{		
		while (SDL_PollEvent(&m_event))
		{
			switch(m_event.type)
			{
				case SDL_QUIT:
				{
					return 1;
				}
				case SDL_MOUSEMOTION:
				{
					x_mouse = m_event.motion.x;
					y_mouse = m_event.motion.y;

					for ( int i=0; i<2; i++)
					{
						if ( CheckFocus( x_mouse, y_mouse, text_menu[i].GetRect()) )
						{
							if ( selected[i] == false)
							{
							selected[i] = 1;					
							text_menu[i].Render(g_screen);
							}
						}
						else
						{
							if ( selected[i] == true)
							{
								selected[i] =0;								
								text_menu[i+2].Render(g_screen);
							}
						}
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					x_mouse = m_event.button.x;
					y_mouse = m_event.button.y;

					for ( int i=0; i<2; i++)
					{
						if ( CheckFocus( x_mouse, y_mouse, text_menu[i].GetRect() ))
						{
							return i;
							mouseclick = true;
						}
					}
					break;
				}
				case SDL_KEYDOWN:
				{
					if (m_event.key.keysym.sym == SDLK_ESCAPE )
						return 1;
					    mouseclick = true;
					break;
				}
			    default:
					break;
			}
		SDL_RenderPresent(g_screen);
		}
	}
}

bool LoadBackground()
{
	bool ret = g_background.loadImage("image//background.png", g_screen);
	if ( ret == false )
		return false;
	else
	return true;
}


void close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window =NULL;
	IMG_Quit();
	SDL_Quit();
}



int main(int argc, char* argv[])
{
	if (InitData() == false )
		return -1;

	if ( LoadBackground() == false )
		return -1;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		{
			printf("%s", Mix_GetError());
		}
	
	//Load Sound Effect
	chunk = Mix_LoadWAV("audio/sound_shoot.wav");
	chunk2 = Mix_LoadWAV("audio/sound_explosion.wav");
	chunk3 = Mix_LoadWAV("audio/newgame_effect.wav");
	chunk4 = Mix_LoadWAV("audio/playagain_effect.wav");
	

	if (chunk == NULL)
	{
	printf("%s", Mix_GetError());
	return -1;
	}
 
	//Load Music
	music = Mix_LoadMUS("audio/background_music.mp3");
	music_menu = Mix_LoadMUS("audio/nhacmenu.mp3");
	if (music == NULL)
	{
	printf("%s", Mix_GetError());
    }

	TextObject score_game;
	score_game.SetColor(WHITE_TEXT);

	BaseObject fire;
	fire.loadImage("image/fire.png", g_screen);

	bool is_quit = false;
	bool mouseclick = false;
	std::string str_val;
	std::string str_high_val;

	ShowMenu(g_screen);
	int ret_menu = ControlMenu(g_screen , font_menu, mouseclick) ;
	if ( mouseclick =true )
	{
		Mix_PlayChannel (-1, chunk3, 0);
		mouseclick = false;
	}
	if (ret_menu == 1 ) is_quit = true;

	bool exit_game = false;

    Uint32 score_val[100] ;
			score_val[0] = 0;
	Uint32 scorehigh =0;
	int dem = 1;

	while (!exit_game)
	{
		GameMap game_map;
		game_map.LoadMap("mapmahoa.txt");
		game_map.LoadTiles(g_screen);

		ObstaclesMap game_Obstaclesmap;
		game_Obstaclesmap.LoadObstaclesMap("mapmahoa.txt");
		game_Obstaclesmap.LoadObstacles(g_screen);

		Plane plane;
		plane.loadImage("image/plane.png", g_screen);
		plane.SetRect(10, SCREEN_HEIGHT / 2);
	
		std::vector<Bullet*> Ammo;
		is_quit = false;
		
	
	
	
		Mix_PlayMusic(music, -1 );
	
		while (!is_quit)
		{			
			while ( SDL_PollEvent(&g_event) != 0 )
			{
				if ( g_event.type == SDL_QUIT)
				{
					is_quit = true;					
				}
				plane.HandleInput(g_event);

				if(g_event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) 
				{
					Mix_PlayChannel (-1, chunk, 0);
					Bullet* newBullet = new Bullet(g_screen, "image/bullet.png");
					newBullet->SetRect(plane.GetRect().x ,plane.GetRect().y+20);
					Ammo.push_back(newBullet);
				}
			}
		
			if (is_quit == true) continue;
			is_quit =  plane.Update(game_map.get_game_map());	
			if (is_quit == true)
			{
				
				//SDL_Rect* a; 
				fire.SetRect(plane.GetRect().x+50 ,plane.GetRect().y+15);
				fire.Render(g_screen);
				Mix_PlayChannel (-1, chunk2, 0);
			}
			for(int i = 0; i < (int) Ammo.size(); i++)
			{
				Ammo[i]->update();
			}
			game_map.Update();
			game_Obstaclesmap.Update();

			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );
			SDL_RenderClear(g_screen);

			g_background.Render(g_screen);
			game_map.DrawMap(g_screen);
			
			game_Obstaclesmap.DrawObstaclesMap(g_screen);
			for(int i = 0; i < (int) Ammo.size(); i++)
			{
				if (Ammo[i]->Collision_obs(game_map.get_game_map()) != false )
				{
					delete Ammo[i];
					Ammo.erase(Ammo.begin() + i--);
				}
			}
			for(int i = 0; i < (int) Ammo.size(); i++)
			{				
					Ammo[i]->Render(g_screen);
			}
			plane.Render(g_screen);

			// Show score game
			std::string str_score = " SCORE: ";
			score_val[dem] = SDL_GetTicks() / 1000;
			Uint32 val_score = score_val[dem]-score_val[dem-1];
			if ( val_score > scorehigh ) scorehigh = val_score;
		    str_val = std::to_string(val_score);
			str_high_val = std::to_string(scorehigh);
			str_score += str_val;
			
			score_game.SetRect(950, 20);
			score_game.SetText(str_score, font_time, g_screen);
			score_game.Render(g_screen);


			SDL_RenderPresent(g_screen); 

		
			SDL_Delay(30);
		}
		dem++;

		//SDL_Delay(200);
		ShowMenu_endgame(g_screen, str_val, str_high_val);
		
	    
		int kt = ControlMenu_endgame(g_screen, font_menu, mouseclick);
		if ( mouseclick =true )
		{
			Mix_PlayChannel (-1, chunk4 , 0);
			mouseclick = false;
		}
		if ( kt == 1 ) exit_game = true;
		else exit_game = false;

	
	}
	close();
    return 0;
}