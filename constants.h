// Constants


#ifndef CONSTANTS
#define CONSTANTS

// Screen constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// Terrain constants
const int RES = 120;  // Number of slices into which to split the screen
const int SLICEWIDTH = SCREEN_WIDTH / RES;  // Width of an individual slice
const int TERRAINBASEHEIGHT = 380;  // Initial tunnel height
const int TERRAINBASEOFFSET = 50;  // Initial (vertical) offset of the tunnel from the top of the screen
const int TERRAINKEYFRAMEDIST = 20;  // Distance between keyframes in terrain offset
const float TERRAINSMOOTHNESS = 1.5f;  // Restricts potential jaggedness (1.0 = unrestricted, 20.0 = effectively a pipe)
const float TERRAINDECAYSPEED = 2.0f;  // Multiplier for tunnel height decay
const float TERRAINHEIGHTPERSISTENCE = 10000.0f;  // Makes the terrain height shrink more slowly
// (Essentially, when t = TERRAINHEIGHTPERSISTANCE,
// height = TERRAINBASEHEIGHT * TERRAINDECAYSPEED^(time / TERRAINHEIGHTPERSISTENCE).)

// Helicopter motion constants
const float UPACCELERATION = 0.3f;
const float DOWNACCELERATION = 0.5f;
const float MAXUPVELOCITY = 4.0f;
const float MAXDOWNVELOCITY = -4.0f;

const int HVELOCITY = SLICEWIDTH;  // Horizontal velocity of game

// Helicopter drawing constants
const int HELIPOSX = 200;  // X-position on screen
const int HELIWIDTH = 50;
const int HELIHEIGHT = 30;

// Helicopter collision constants - range of slices occupied by helicopter body
const int HELILEFTSLICE = (HELIPOSX - (HELIWIDTH / 2)) / SLICEWIDTH;
const int HELIRIGHTSLICE = (HELIPOSX + (HELIWIDTH / 2)) / SLICEWIDTH;

// Block constants
const int BLOCKSPACING = 5;  // Number of keyframes between each newly-added block
const int BLOCKHEIGHT = 100;
const int BLOCKWIDTH = 30;

// Smoke trail constants
const int SMOKESIZE = 10;
const int SMOKESPACING = 3;  // Game time between each smoke particle emission
const int SMOKEFRAMELENGTH = 2;  // Number of game time ticks for which an animation frame is shown
const int NUMSMOKEFRAMES = 20;  // Number of animation frames (in build\\img\\smoke)

#endif
