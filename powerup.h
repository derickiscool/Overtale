#ifndef _POWERUP_H                 // Prevent multiple definitions if this 
#define _POWERUP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "player.h"
#include "projectile.h"

namespace PowerUpNS
{
    const int   WIDTH = 23;                // image width
    const int   HEIGHT = 23;               // image height
    const int   X = GAME_WIDTH / 3; // location on screen
    const int   Y = GAME_HEIGHT / 2;
    const float heal = 25;

}

// inherits from Entity class
class Powerup : public Entity
{
protected:
    bool check; //bounce off the boundary if true

public:
    // constructor
    Powerup();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
        TextureManager* textureM);
    void deletePowerup();


    //get setters
    void setX(float x) { spriteData.x = x; };

    float getX() { return spriteData.x; };

    void setY(float y) { spriteData.y = y; };

    float getY() { return spriteData.y; };

};
#endif

