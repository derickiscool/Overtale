
#ifndef _OVERTALE_H             // prevent multiple definitions if this 
#define _OVERTALE_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "player.h"
#include "environment.h"

//=============================================================================
// Create game class
//=============================================================================
class Overtale : public Game
{
private:
    // variables
    TextureManager gameTextures;    // game texture
    TextureManager floorTexture;    //floor texture
    Player    ship1;          // spaceship
    Environment floorEnvironment; //floor environment
    Environment fullFloorRow[ENVIRONMENT_ROW_LENGTH];  //Creating Singular Row
    Environment fullFloor[ENVIRONMENT_ROW_LENGTH*ENVIRONMENT_COLUMN_LENGTH]; //Creating whole floor
    

public:
    // Constructor
    Overtale();

    // Destructor
    virtual ~Overtale();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
