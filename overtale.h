
#ifndef _OVERTALE_H             // prevent multiple definitions if this 
#define _OVERTALE_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "player.h"

//=============================================================================
// Create game class
//=============================================================================
class Overtale : public Game
{
private:
    // variables
    TextureManager nebulaTexture;   // nebula texture
    TextureManager gameTextures;    // game texture
    TextureManager floorTexture;    //floor texture
    Player    ship1;          // spaceship
    Image   nebula;         // backdrop image
    

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
