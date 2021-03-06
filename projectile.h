//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Derick Lee 
//  Student Number:     S10196689
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
    
    
    const float PROJECTILE_EASY_SPEED = 1.0f; //projectile speed rate 
    const float PROJECTILE_MEDIUM_SPEED = 1.0f;
    const float PROJECTILE_HARD_SPEED = 0.75f; 
    const float PROJECTILE_EASY_SPAWN = 0.25f; //projectile spawn rate
    const float PROJECTILE_MEDIUM_SPAWN = 0.5f;
    const float PROJECTILE_HARD_SPAWN = 0.75f;

}

namespace boss2ProjectileNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
    const int Y = GAME_HEIGHT / 4;
    const int   TEXTURE_COLS = 0;           // texture has 8 columns
    const int   START_FRAME = 0;      // starts at frame 0
    const int   END_FRAME = 4;        // animation frames 0,1,2,3,4
    const float ANIMATION_DELAY = 0.2f;    // time between frames


    const float PROJECTILE_EASY_SPEED = 1.0f; //projectile speed rate 
    const float PROJECTILE_MEDIUM_SPEED = 1.0f;
    const float PROJECTILE_HARD_SPEED = 0.75f;
    const float PROJECTILE_EASY_SPAWN = 0.25f; //projectile spawn rate
    const float PROJECTILE_MEDIUM_SPAWN = 0.5f;
    const float PROJECTILE_HARD_SPAWN = 0.75f;

}
namespace boss3ProjectileNS
{
    const int WIDTH = 32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
    const int Y = GAME_HEIGHT / 4;


    const float PROJECTILE_EASY_SPEED = 0.7f; //projectile speed rate 
    const float PROJECTILE_MEDIUM_SPEED = 0.5f;
    const float PROJECTILE_HARD_SPEED = 0.25f;
    const float PROJECTILE_EASY_SPAWN = 0.75f; //projectile spawn rate
    const float PROJECTILE_MEDIUM_SPAWN = 1.0f;
    const float PROJECTILE_HARD_SPAWN = 1.2f;

}

// inherits from Entity class
class Projectile : public Entity
{
private:
    int damage; //projectileDamage

public:
    // constructor
    Projectile();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
        TextureManager* textureM);
    void update(float frameTime);
    void spawnProjectiles(Projectile *projectiles[]);
    void clearProjectiles(Projectile *projectiles[]);


    //get set
    void setAngle(float angle) { spriteData.angle = angle; };
    float getAngle() { return spriteData.angle; };


    void setProjectileDamage(int newDamage) { damage = newDamage; };
    int getProjectileDamage() { return damage; };
};
#endif



