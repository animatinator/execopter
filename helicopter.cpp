// Helicopter

#include "helicopter.h"


Helicopter::Helicopter(float initialpos):
	h(initialpos),
	startpos(initialpos),
	v(0.0f),
	up(false),
	trail(HELIPOSX - (HELIWIDTH / 2) - 25, (int)h, -HVELOCITY, -1, SMOKESIZE, SMOKESPACING)
{}

void Helicopter::Restart()
{
	h = startpos;
	v = 0.0f;
	trail.Clear();
	trail.Start();
}

void Helicopter::Die()
{
	trail.Die();
	trail.Stop();
}

void Helicopter::Update()
{
	h -= v;  // Negative v as up is down in computer science 8D
	
	if (up) v += UPACCELERATION;
	else v -= DOWNACCELERATION;
	
	if ((int)v > MAXUPVELOCITY) v = MAXUPVELOCITY;
	else if ((int)v < MAXDOWNVELOCITY) v = MAXDOWNVELOCITY;
	
	trail.SetY((int)h - (HELIHEIGHT / 2));
	trail.Update();
}

void Helicopter::UpdateParticles()
{
	trail.SetY((int)h - (HELIHEIGHT / 2));
	trail.Update();
}

void Helicopter::Draw(SDL_Surface* screen) const
{
	int xpos = HELIPOSX - (HELIWIDTH / 2);
	int ypos = (int)h - (HELIHEIGHT / 2);
	Draw_Rect(screen, xpos, ypos, HELIWIDTH, HELIHEIGHT, SDL_MapRGB(screen->format, 255, 255, 255));
	
	trail.Draw(screen);
}
