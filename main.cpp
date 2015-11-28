// ExeCopter - main file


#include <iostream>
#include <cstdio>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_TTF.h"

#include "helicopter.h"
#include "terrain.h"

class TerrainSlice;
class Block;

SDL_Surface* screen = NULL;
Terrain* level;

SDL_Surface* splash = IMG_Load("splash.png");
SDL_Surface* fail = IMG_Load("fail.png");

SDL_Surface* scoretext;
TTF_Font* scorefont;

int gametime = 0;
bool started = false;
bool finished = false;


void Restart(Helicopter& heli, Terrain&ter)
{
	heli.Restart();
	ter.Restart();
	gametime = 0;
	started = false;
}

bool GetWallCollision(Helicopter heli, Terrain ter)
{
	for (int i = HELILEFTSLICE; i <= HELIRIGHTSLICE; ++i)
	{
		TerrainSlice slice = ter.GetSlice(i);
		
		// Top wall
		if ((heli.GetHeight() - (HELIHEIGHT / 2)) < slice.GetOffset()) return true;
		
		// Bottom wall
		if ((heli.GetHeight() + (HELIHEIGHT / 2)) > (slice.GetOffset() + slice.GetHeight())) return true;
	}
	
		return false;
}

bool GetBlockCollision(Helicopter heli, Terrain ter)
{
	vector<Block> blocks = ter.GetBlocks();
	
	for (vector<Block>::const_iterator iter = blocks.begin(); iter != blocks.end(); ++iter)
	{
		Block block = *iter;
		
		// X-axis
		if (((HELIPOSX - (HELIWIDTH / 2)) < (block.GetX() + BLOCKWIDTH)) && ((HELIPOSX + (HELIWIDTH / 2)) > block.GetX()))
		{
			// Y-axis
			if (((heli.GetHeight() - (HELIHEIGHT / 2)) < (block.GetOffset() + BLOCKHEIGHT)) && ((heli.GetHeight() + (HELIHEIGHT / 2)) > block.GetOffset()))
			{
				return true;
			}
		}
	}
	
		return false;
}

void DrawText(SDL_Surface* screen)
{
	SDL_Color colour = {0, 0, 0, 0};
	
	// Create a char array for the score and a temporary one to hold the converted gametime
	char score[21] = "Distance:           ";
	char num[11] = {"0000000000"};
	sprintf(num, "%d", gametime);  // Convert the gametime into a char array and paste it into 'num'
	
	for (int i = 0; i < 10; ++i)  // Write the number into the score
	{
		score[i + 10] = num[i];
	}
	
	scoretext = TTF_RenderText_Blended(scorefont, score, colour);
	SDL_BlitSurface(scoretext, NULL, screen, NULL);
}

void Update(Helicopter& heli, Terrain& ter)
{
	heli.Update();
	ter.Update(gametime);
}

void Redraw(SDL_Surface* screen, Helicopter heli, Terrain ter)
{	
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 60, 50, 10));//77, 222, 255));
	heli.Draw(screen);
	ter.Draw(screen);
	
	if (!started) SDL_BlitSurface(splash, NULL, screen, NULL);
	else if (finished) SDL_BlitSurface(fail, NULL, screen, NULL);
	
	DrawText(screen);
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		cout << "SDL couldn't init, innit." << endl;
		
			return 1;
	}
	TTF_Init();
	scorefont = TTF_OpenFont("trebucbd.ttf", 24);
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	SDL_WM_SetCaption("ExeCopter", NULL);
	
	if (!screen)
	{
		cout << "Couldn't create screen surface" << endl;
		
			return 1;
	}
	
	Helicopter heli(240);
	Terrain ter;
	
	SDL_Event event;
	bool running = true;
	
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running = false;
					
						break;
				
				case SDL_MOUSEBUTTONDOWN:
					if (!started)
					{
						started = true;
						heli.GoUp();
						heli.StartParticles();
					}
					
					else if (finished)
					{
						finished = false;
						Restart(heli, ter);
					}
					
					else heli.GoUp();
					
						break;
				
				case SDL_MOUSEBUTTONUP:
					heli.GoDown();
					
						break;
				
				default:
					break;
			}
		}
		
		if (started && !finished)
		{
			++gametime;
			Update(heli, ter);
			
			if (GetWallCollision(heli, ter) || GetBlockCollision(heli, ter))
			{
				finished = true;
				heli.Die();
			}
		}
		else heli.UpdateParticles();
		
		Redraw(screen, heli, ter);
		
		SDL_Flip(screen);
		SDL_Delay(10);
	}
	
	SDL_FreeSurface(screen);
	SDL_FreeSurface(splash);
	SDL_FreeSurface(fail);
	
	TTF_CloseFont(scorefont);
	
	TTF_Quit();
	SDL_Quit();
	
		return 0;
}
