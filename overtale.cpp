
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

   
    //floor texture
    if (!floorTexture.initialize(graphics, FLOOR_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing floor texture"));

    //crate texture
    if (!crateTexture.initialize(graphics, CRATE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing crate texture"));

    // main game textures
    if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // ship
    if (!ship1.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(playerNS::SHIP1_START_FRAME, playerNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(playerNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH / 2 - playerNS::WIDTH / 2); //Set ship to center 
    ship1.setY(GAME_HEIGHT / 2 - playerNS::HEIGHT / 2); //Set ship to center 

    //floor object initialization 
    if (!floorEnvironment.initialize(this, floorEnvironmentNS::WIDTH, floorEnvironmentNS::HEIGHT, 0, &floorTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing floor"));

    if (!crateEnvironment.initialize(this, boundaryEnvironmentNS::WIDTH, boundaryEnvironmentNS::HEIGHT, 0, &crateTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error intialzing boundary crates"));

    generateFloor();

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

    for (Environment e : fullFloor)
    {
        e.draw();
    }
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

void Overtale::generateFloor()
{
    fullFloorRow[0] = floorEnvironment; //fullFloor [0] refers to center of the square. We start to generate more textures from this center point

//Create one row
    for (int i = 1; i < FLOOR_ROW_LENGTH; ++i)
    {
        fullFloorRow[i] = floorEnvironment;
        if (i % 2 != 0)
        {
            fullFloorRow[i].setX(fullFloorRow[0].getX() + (floorEnvironmentNS::WIDTH / 2 * i));
        }
        else
        {
            fullFloorRow[i].setX(fullFloorRow[0].getX() - (floorEnvironmentNS::WIDTH / 2 * i));
        }
    }
    //Copy row and generate more copies
    int block = 0; //Refers to which position in array to store the block in, multiplied by i 
    for (Environment floorTile : fullFloorRow)
    {
        for (int i = 0; i < FLOOR_COLUMN_LENGTH;++i)
        {
            fullFloor[i + block] = floorTile;
            if (i % 2 != 0)
            {
                fullFloor[i + block].setY(fullFloor[i + block].getY() + 8 * i);
            }
            else
            {
                fullFloor[i + block].setY(fullFloor[i + block].getY() - 8 * i);
            }


        }
        block += FLOOR_COLUMN_LENGTH; //Move onto the next column 

    }


}

void Overtale::generateBoundary()
{

}
