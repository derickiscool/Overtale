
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

    //boss 1 textures
    if (!boss1Texture.initialize(graphics, BOSS1_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    if (!boss1.initialize(this, boss1NS::WIDTH, boss1NS::HEIGHT, boss1NS::TEXTURE_COLS, &boss1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss1"));
    boss1.setFrames(boss1NS::START_FRAME, boss1NS::END_FRAME);
    boss1.setCurrentFrame(boss1NS::START_FRAME);

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
    generateBoundary();

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

    if (ship1.getX() > boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH)    //if touching boundary      
        ship1.setX(boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH);
                                                                                       
    if (ship1.getX() < boundaryEnvironmentNS::MIN_X)        
        ship1.setX((float)boundaryEnvironmentNS::MIN_X); 



    if (ship1.getY() > boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT)              
        ship1.setY((float)boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT);     
    if (ship1.getY() < boundaryEnvironmentNS::MIN_Y)        
        ship1.setY((float)boundaryEnvironmentNS::MIN_Y);          
    ship1.update(frameTime);
    boss1.update(frameTime);
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
{

    
}

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
    for (Environment e : fullCrateEnvironment)
    {
        e.draw();
    }
    ship1.draw();                           //add ship to scene
    boss1.draw();
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
    fullFloor[0] = floorEnvironment;
//Create one row
    for (int i = 1; i < FLOOR_ROW_LENGTH; ++i)
    {
        fullFloorRow[i] = fullFloorRow[i - 1];
        if (i % 2 != 0)
        {
            fullFloorRow[i].setX(fullFloorRow[i].getX() + (floorEnvironmentNS::WIDTH * i ));
            fullFloor[i] = fullFloorRow[i];
        }
        else
        {
            fullFloorRow[i].setX(fullFloorRow[i].getX() - (floorEnvironmentNS::WIDTH * i));
            fullFloor[i] = fullFloorRow[i];
        }
    }
   

    int counter = FLOOR_COLUMN_LENGTH;
   for (Environment e : fullFloorRow)
   {
       int multiply = 1;
       for (int i = 0; i < FLOOR_COLUMN_LENGTH - 1; ++i)// -1 as the center column is already filled
       {

           fullFloor[counter + i] = e;

           if (i % 2 == 0)
           {
               fullFloor[counter + i].setY(fullFloor[counter + i].getY() + 16 * multiply);
           }
           else
           {
               fullFloor[counter + i].setY(fullFloor[counter + i].getY() - 16 * multiply);
               multiply++;
           }



       }
       counter += FLOOR_COLUMN_LENGTH-1;
   }
}

void Overtale::generateBoundary()
{
    crateEnvironment.setX(boundaryEnvironmentNS::MIN_X - boundaryEnvironmentNS::WIDTH/2); //Set position at minimum x position, left most boundary
    crateEnvironment.setY(boundaryEnvironmentNS::MIN_Y - boundaryEnvironmentNS::HEIGHT/2);
    crateEnvironment.updateBlockMovement(true);
    fullCrateEnvironment[0] = crateEnvironment; //Start from top left, min x, min y ;
    int counter = 0; //array counter
    //Generate from top left to bottom left

    for (int i = 1; i < FLOOR_COLUMN_LENGTH + 2; ++i) // loop until you reach the total length of column, +2 as there is 1 extra crate in the corner
    {
        fullCrateEnvironment[i] = fullCrateEnvironment[i - 1];
        fullCrateEnvironment[i].setY(fullCrateEnvironment[i].getY() + boundaryEnvironmentNS::HEIGHT);
        
    }
    counter += FLOOR_COLUMN_LENGTH + 2;
    //generate from bottom left to bottom right
    for (int i = counter; i < counter + FLOOR_ROW_LENGTH + 1; ++i) // loop until you reach the total length of the row, +1 as there is 1 crate in the corner
    {
        fullCrateEnvironment[i] = fullCrateEnvironment[i - 1];
        fullCrateEnvironment[i].setX(fullCrateEnvironment[i].getX() + boundaryEnvironmentNS::WIDTH);
        

    }
    counter += FLOOR_ROW_LENGTH + 1;
    //generate from bottom right to top right
    for (int i = counter; i < counter + FLOOR_COLUMN_LENGTH + 1; ++i) // loop until you reach the total length of the row, +1 as there is 1 crate in the corner
    {
        fullCrateEnvironment[i] = fullCrateEnvironment[i - 1];
        fullCrateEnvironment[i].setY(fullCrateEnvironment[i].getY() - boundaryEnvironmentNS::HEIGHT);

        
    }
    counter += FLOOR_COLUMN_LENGTH + 1 ;
    //generate from top right to top left
    for (int i = counter; i < counter + FLOOR_ROW_LENGTH; ++i) // loop until you reach the total length of the row
    {
        fullCrateEnvironment[i] = fullCrateEnvironment[i - 1];
        fullCrateEnvironment[i].setX(fullCrateEnvironment[i].getX() - boundaryEnvironmentNS::WIDTH);


    }
    

}
