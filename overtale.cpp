
#include "overtale.h"

//=============================================================================
// Constructor
//=============================================================================
Overtale::Overtale()
{}

//=============================================================================
// Destructor
//=============================================================================
Overtale::~Overtale()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Overtale::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError


    // nebula texture
    if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // floor texture
    
    if (!floorTexture.initialize(graphics, FLOOR_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing floor texture"));

    // main game textures
    if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // nebula image
    if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
    //floor image


    // ship
    if (!ship1.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(playerNS::SHIP1_START_FRAME, playerNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(playerNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH / 4);
    ship1.setY(GAME_HEIGHT / 4);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Overtale::update()
{
    if (input->isKeyDown(SHIP1_RIGHT_KEY))            // if move right
    {
        ship1.setX(ship1.getX() + playerNS::SPEED);
    }

    if (input->isKeyDown(SHIP1_LEFT_KEY))            // if move left
    {
        ship1.setX(ship1.getX() - playerNS::SPEED);
    }

    if (input->isKeyDown(SHIP1_UP_KEY))            // if move up
    {
        ship1.setY(ship1.getY() - playerNS::SPEED);
    }

    if (input->isKeyDown(SHIP1_DOWN_KEY))            // if move down
    {
        ship1.setY(ship1.getY() + playerNS::SPEED);
    }

    if (ship1.getX() > GAME_WIDTH)               // if off screen right
        ship1.setX((float)-ship1.getWidth());     // position off screen left
    if (ship1.getX() < -ship1.getWidth())         // if off screen left
        ship1.setX((float)GAME_WIDTH);           // position off screen right
    if (ship1.getY() > GAME_HEIGHT)               // if off screen right
        ship1.setX((float)-ship1.getHeight());     // position off screen left
    if (ship1.getY() < -ship1.getHeight())         // if off screen left
        ship1.setY((float)GAME_HEIGHT);           // position off screen right
    ship1.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Overtale::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Overtale::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Overtale::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    
    nebula.draw();                          // add the orion nebula to the scene
    ship1.draw();                           //add ship to scene

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Overtale::releaseAll()
{
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Overtale::resetAll()
{
    Game::resetAll();
    return;
}
