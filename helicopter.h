// Helicopter (header)

#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "constants.h"
#include <cstdlib>
#include "SDL/SDL_draw.h"
#include "particles.h"

using namespace std;

struct SDL_Surface;


class Helicopter
{
	public:
		Helicopter(float initialpos);
		~Helicopter() {};
		
		void Restart();
		void Die();
		void StartParticles() {trail.Move();}
		void StopParticles() {trail.Stop();}
		
		void Update();
		void UpdateParticles();
		void Draw(SDL_Surface* screen) const;
		
		float GetHeight() const {return h;}
		
		void GoUp() {up = true;}
		void GoDown() {up = false;}
	
	private:
		float h;
		float startpos;
		float v;
		bool up;
		
		ParticleTrail trail;
};

#endif
