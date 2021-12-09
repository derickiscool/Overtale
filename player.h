#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "environment.h"

namespace playerNS
{
    const int WIDTH = 32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
    const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
    const float ROTATION_RATE = (float)PI / 4; // radians per second
    const float SPEED = 1;                // 1 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 1;           // texture has 1 columns
    const int   SHIP1_START_FRAME = 4;      // ship1 starts at frame 4
    const int   SHIP1_END_FRAME = 7;        // ship1 animation frames 4,5,6,7
    const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames

}

// inherits from Entity class
class Player : public Entity
{
private:



public:
    // constructor
    Player();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
        TextureManager* textureM);
    void update(float frameTime);

    //Get Setters

};
#endif

