#ifndef _BOSS1PROJECTILE_H                // Prevent multiple definitions if this 
#define _BOSS1PROJECTILE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace boss1ProjectileNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
    const int Y = GAME_HEIGHT / 4;
    const int   TEXTURE_COLS = 0;           // texture has 8 columns
    const int   START_FRAME = 0;      // starts at frame 0
    const int   END_FRAME = 4;        // animation frames 0,1,2,3,4
    const float ANIMATION_DELAY = 0.2f;    // time between frames
    const float PROJECTILE_EASY_SPEED = 100.0f;
    const float PROJECTILE_MEDIUM_SPEED = 150.0f;
    const float PROJECTILE_HARD_SPEED = 200.0f;


}

// inherits from Entity class
class Projectile : public Entity
{


public:
    // constructor
    Projectile();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
        TextureManager* textureM);
    void update(float frameTime);
    void spawnProjectiles(Projectile projectiles[]);


    //get set
    void setAngle(float angle) { spriteData.angle = angle; };
    float getAngle() { return spriteData.angle; };


};
#endif



