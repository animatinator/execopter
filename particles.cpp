// Particles


#include "particles.h"


Particle::Particle(int xpos, int ypos, int xmotion, int ymotion, int sidelength, vector<SDL_Surface*> animframes):
	x(xpos),
	y(ypos),
	xmot(xmotion),
	ymot(ymotion),
	size(sidelength),
	frames(animframes),
	curframe(0)
{}

void Particle::Update(bool xmove)
{
	if (xmove) x += xmot;
	y += ymot;
	++curframe;
}

void Particle::Draw(SDL_Surface* screen) const
{
	//Draw_Rect(screen, x, y, size, size, SDL_MapRGB(screen->format, 255, 255, 255));
	
	SDL_Rect position;
	position.x = x; position.y = y;
	if ((curframe / SMOKEFRAMELENGTH) < NUMSMOKEFRAMES)
	{
		SDL_BlitSurface(frames.at((curframe / SMOKEFRAMELENGTH) % NUMSMOKEFRAMES), NULL, screen, &position);
	}
}


ParticleTrail::ParticleTrail(int xpos, int ypos, int xmotion, int ymotion, int sidelength, int particlespacing):
	x(xpos),
	y(ypos),
	xmot(xmotion),
	ymot(ymotion),
	size(sidelength),
	time(0),
	parspace(particlespacing),
	running(true),
	xmoving(false)
{
	ParticleTrail::InitImages();
}

void ParticleTrail::InitImages()
{
	string name;
	
	for (int i = 0; i < NUMSMOKEFRAMES; ++i)
	{
		int j = i + 1;
		name = "img\\cloud\\0000";
		if (j < 10) name += "0";
		stringstream jstring;
		jstring << j;
		name += jstring.str();
		name += ".png";
		
		SDL_Surface* newimg = IMG_Load(name.c_str());
		frames.push_back(newimg);
	}
}

void ParticleTrail::Update()
{
	++time;
	
	int deletei = -1;
	int i = 0;
	
	for (vector<Particle>::iterator iter = particles.begin(); iter != particles.end(); ++iter, ++i)
	{
		iter->Update(xmoving);
		
		if (iter->GetX() < 0)
		{
			deletei = i;
		}
	}
	
	if (deletei != -1)
	{
		vector<Particle>::iterator del = particles.begin();
		advance(del, deletei);
		particles.erase(del);
	}
	
	if ((time % parspace == 0) && running)
	{
		ParticleTrail::AddParticle();
	}
}

void ParticleTrail::Draw(SDL_Surface* screen) const
{
	for (vector<Particle>::const_iterator iter = particles.begin(); iter != particles.end(); ++iter)
	{
		iter->Draw(screen);
	}
}

void ParticleTrail::AddParticle()
{
	particles.push_back(Particle(x, y, xmot, ymot, size, frames));
}
