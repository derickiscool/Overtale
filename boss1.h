#ifndef _BOSS1_H                 // Prevent multiple definitions if this 
#define _BOSS1_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "projectile.h"
#include "environment.h"
#include "player.h"

namespace boss1NS
{
    const int WIDTH = 126;                   // image width
    const int HEIGHT = 85;                  // image height
    const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
    const int Y = GAME_HEIGHT / 6;
    const int   TEXTURE_COLS = 0;           // texture has 8 columns
    const int   START_FRAME = 0;      // starts at frame 0
    const int   END_FRAME = 5;        // animation frames 0,1,2,3,4
    const float ANIMATION_DELAY = 0.2f;    // time between frames
  
    
}

// inherits from Entity class
class Boss1 : public Entity
{
protected:
    float projectileAngle; //angle the projectile needs to curve, to hit the player
    float projectileSpeed; //speed of projectile 
    float spawnRate; //spawnRate of projectiles in seconds
    bool bounceBool; //bounce off the boundary if true

public:
    // constructor
    Boss1();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
        TextureManager* textureM);
    void update(float frameTime, Projectile projectiles[]);
    void setupProjectile(Projectile *projectile, Player ship);//Setting up velocity + angle of projectiles
    void bounceOff(Projectile projectiles[]); //removes entities when touching boundaries

    //get setters
    void setX(float x) { spriteData.x = x; };

    float getX() { return spriteData.x; };



    void setY(float y) { spriteData.y = y; };

    float getY() { return spriteData.y; };
};
#endif


