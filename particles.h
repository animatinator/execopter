// Particles (header)


#ifndef PARTICLES_H
#define PARTICLES_H

#include "constants.h"
#include "SDL/SDL_draw.h"
#include "SDL/SDL_image.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct SDL_Surface;

class Particle
{
	public:
		Particle(int xpos, int ypos, int xmotion, int ymotion, int sidelength, vector<SDL_Surface*> animframes);
		~Particle() {};
		
		int GetX() const {return x;}
		int GetY() const {return y;}
		
		void Update(bool xmove = true);
		void Draw(SDL_Surface* screen) const;
	
	private:
		int x;
		int y;
		int xmot;
		int ymot;
		int size;
		
		vector<SDL_Surface*> frames;
		int curframe;
};

class ParticleTrail
{
	public:
		ParticleTrail(int xpos, int ypos, int xmotion, int ymotion, int sidelength, int particlespacing);
		~ParticleTrail() {};
		
		void Start() {running = true;}
		void Die() {running = false;}
		void Move() {xmoving = true;}
		void Stop() {xmoving = false;}
		
		void InitImages();
		
		void SetX(int newx) {x = newx;}
		void SetY(int newy) {y = newy;}
		
		void Update();
		void Draw(SDL_Surface* screen) const;
		
		void AddParticle();
		void Clear() {particles.clear();}
	
	private:
		int x;
		int y;
		int xmot;
		int ymot;
		int size;
		
		vector<SDL_Surface*> frames;
		
		vector<Particle> particles;
		
		int time;
		int parspace;
		
		bool running;
		bool xmoving;
};

#endif
