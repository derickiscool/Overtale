
#include "overtale.h"

//=============================================================================
// Constructor
//=============================================================================
Overtale::Overtale()
{

    dxFontSmall = new TextDX();     // DirectX fonts
}

//=============================================================================
// Destructor
//=============================================================================
Overtale::~Overtale()
{
    releaseAll();           // call onLostDevice() for every graphics item
    SAFE_DELETE(dxFontSmall);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Overtale::initialize(Graphics* g, Game* gPtr)
{
    graphics = g;
    gamePtr = gPtr;
       
    if (dxFontSmall->initialize(graphics, 50, true, true, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
    
    
    bossType = BossType::bossType1;  //Change me if you want to test out ur own project
   

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
    if (!ship1.initialize(gamePtr, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(playerNS::SHIP1_START_FRAME, playerNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(playerNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH / 2 - playerNS::WIDTH /2); //Set ship to center 
    ship1.setY(GAME_HEIGHT / 2 - playerNS::HEIGHT / 2); //Set ship to center 


    //floor object initialization 
    if (!floorEnvironment.initialize(gamePtr, floorEnvironmentNS::WIDTH, floorEnvironmentNS::HEIGHT, 0, &floorTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing floor"));

    if (!crateEnvironment.initialize(gamePtr, boundaryEnvironmentNS::WIDTH, boundaryEnvironmentNS::HEIGHT, 0, &crateTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error intialzing boundary crates"));

    //environment generation 
    generateFloor();
    generateBoundary();

    switch (bossType)
    {
    case Overtale::bossType1:
        boss1Setup();
        break;
    case Overtale::bossType2:
        break;
    case Overtale::bossType3:
        boss3Setup();
        break;
    default:
        break;
    }
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Overtale::update(float frameTime)
{
    

  
    ship1.update(frameTime);

    switch (bossType)
    {
    case BossType::bossType1:

        for (int i = 0; i < MAX_PROJECTILES; ++i)
        {
            projectiles[i]->update(frameTime);
        }
        boss1.update(frameTime,projectiles, ship1);
        break;
    case BossType::bossType2:
        break;
    case BossType::bossType3:
        for (int i = 0; i < MAX_PROJECTILES; i += 1)
        {
            projectiles[i]->update(frameTime);
        }
        boss3.update(frameTime, projectiles);
        asteroid1.update(frameTime);
        asteroid2.update(frameTime);
        asteroid3.update(frameTime);
        asteroid4.update(frameTime);
        break;
    default:
        break;
    }
    
    
    
   

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
    VECTOR2 collisionVector;
    for (int i = 0; i < boss1.getActiveProjectiles(); ++i)
    {
        if (projectiles[i]->collidesWith(ship1, collisionVector))
        {
            projectiles[i]->setActive(false);
            boss1.setActiveProjectiles(boss1.getActiveProjectiles() - 1);
            ship1.setHealth(ship1.getHealth() - projectiles[i]->getProjectileDamage());
            break;
        }
    }

    for (int i = 0; i < boss3.getActiveProjectiles(); ++i)
    {
        if (projectiles[i]->collidesWith(ship1, collisionVector))
        {
            projectiles[i]->setActive(false);
            ship1.setHealth(ship1.getHealth() - projectiles[i]->getProjectileDamage());
            break;
        }
    }

    if (ship1.collidesWith(boss3, collisionVector))
    {
        ship1.bounce(collisionVector, boss3);
        ship1.setHealth(ship1.getHealth() - boss3NS::DAMAGE);
    }

    if (ship1.collidesWith(asteroid1, collisionVector))
    {
        ship1.bounce(collisionVector, asteroid1);
        ship1.setHealth(ship1.getHealth() - asteroidNS::DAMAGE);
    }
    if (ship1.collidesWith(asteroid2, collisionVector))
    {
        ship1.bounce(collisionVector, asteroid2);
        ship1.setHealth(ship1.getHealth() - asteroidNS::DAMAGE);
    }
    if (ship1.collidesWith(asteroid3, collisionVector))
    {
        ship1.bounce(collisionVector, asteroid3);
        ship1.setHealth(ship1.getHealth() - asteroidNS::DAMAGE);
    }
    if (ship1.collidesWith(asteroid4, collisionVector))
    {
        ship1.bounce(collisionVector, asteroid4);
        ship1.setHealth(ship1.getHealth() - asteroidNS::DAMAGE);
    }

    if (ship1.collidesWith(healPowerup1, collisionVector))
    {
        healPowerup1.deletePowerup();
        ship1.setHealth(ship1.getHealth() + PowerUpNS::heal);
    }

    if (ship1.collidesWith(healPowerup2, collisionVector))
    {
        healPowerup2.deletePowerup();
        ship1.setHealth(ship1.getHealth() + PowerUpNS::heal);
    }

    switch (bossType)
    {
    case BossType::bossType1:
        switch (boss1.getWaveValue())
        {
        case 0:
            break;
        case 1:                                //Bounce Collisions
            boss1.startBounce(projectiles, fullCrateEnvironment);
            break;
        case 2:
            boss1.startBounce(projectiles, fullCrateEnvironment);
            break;
        default:
            break;
        }
        
        break;

    case BossType::bossType2:
        break;
    case BossType::bossType3:
        //no special collision methods
        break;
    default:
        break;
    }

  
    
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
    projectiles[0]->spawnProjectiles(projectiles);



    switch (bossType)
    {
    case BossType::bossType1:
        dxFontSmall->setFontColor(graphicsNS::WHITE);
        dxFontSmall->print("Wave " + std::to_string(boss1.getWaveValue() + 1), 0, 40);
        dxFontSmall->print("Timer: " + std::to_string(boss1.getTimer()), 0, 80);
        dxFontSmall->print("Active Projectiles : " + std::to_string(boss1.getActiveProjectiles()), 0, 120);
        dxFontSmall->print("Health : " + std::to_string(ship1.getHealth()), 0, 180);
        boss1.draw();
        break;

    case BossType::bossType2:
        break;
    case BossType::bossType3:
        dxFontSmall->setFontColor(graphicsNS::WHITE);
        dxFontSmall->print("Wave " + std::to_string(boss3.getWaveValue() + 1), 0, 40);
        dxFontSmall->print("Timer: " + std::to_string(boss3.getTimer()), 0, 80);
        dxFontSmall->print("Active Projectiles : " + std::to_string(boss3.getActiveProjectiles()), 0, 120);
        dxFontSmall->print("Health : " + std::to_string(ship1.getHealth()), 0, 180);
        boss3.draw();
        asteroid1.draw();
        asteroid2.draw();
        asteroid3.draw();
        asteroid4.draw();
        healPowerup1.draw();
        healPowerup2.draw();
        shieldPowerup.draw();
        break;
    default:
        break;
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
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Overtale::resetAll()
{
    return;
}

//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Derick Lee 
//  Student Number:     S10196689

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



void Overtale::boss1Setup()
{
    //boss 1 textures
    if (!boss1Texture.initialize(graphics, BOSS1_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));
    //Boss 1 projectile Textures
    if (!boss1ProjectileTexture.initialize(graphics, BOSS1Projectile_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss1projectile texture"));
    //boss1 initialization 
    if (!boss1.initialize(gamePtr, boss1NS::WIDTH, boss1NS::HEIGHT, boss1NS::TEXTURE_COLS, &boss1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss1"));
    boss1.setFrames(boss1NS::START_FRAME, boss1NS::END_FRAME);
    boss1.setCurrentFrame(boss1NS::START_FRAME);
    //boss1 projectile initialization 
    if (!boss1Projectile.initialize(gamePtr, boss1ProjectileNS::WIDTH, boss1ProjectileNS::HEIGHT, boss1ProjectileNS::TEXTURE_COLS, &boss1ProjectileTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss1"));
    boss1.projectileInitialization(&boss1Projectile);
   
    
    //projectile array initialization 
    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        Projectile projectile = boss1Projectile;
        tempProjectiles[i] = projectile;

        projectiles[i] = &tempProjectiles[i];

    }
    

}

void Overtale::boss3Setup()
{
    //boss 3 textures
    if (!boss3Texture.initialize(graphics, BOSS3_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss3 textures"));
    //Boss 3 projectile Textures
    if (!boss3ProjectileTexture.initialize(graphics, BOSS3Projectile_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss3projectile texture"));

    //asteroid textures
    if (!asteroidTexture.initialize(graphics, ASTEROID_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing asteroid textures"));


    //boss3 initialization 
    if (!boss3.initialize(gamePtr, boss3NS::WIDTH, boss3NS::HEIGHT, boss3NS::TEXTURE_COLS, &boss3Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss3"));
    boss3.setFrames(boss3NS::START_FRAME, boss3NS::END_FRAME);
    boss3.setCurrentFrame(boss3NS::START_FRAME);

    //boss3 projectile initialization 
    if (!boss3Projectile.initialize(gamePtr, boss3ProjectileNS::WIDTH, boss3ProjectileNS::HEIGHT, 0, &boss3ProjectileTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss3 projectiles"));
    boss3Projectile.setActive(false);

    boss3.projectileInitialization(&boss3Projectile);
 
      //asteroid1 initialization
    if (!asteroid1.initialize(gamePtr, asteroidNS::WIDTH, asteroidNS::HEIGHT, 0, &asteroidTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing asteroid1"));
    asteroid1.setX(GAME_WIDTH / 2 - GAME_WIDTH / 3);
    asteroid1.setY(GAME_HEIGHT / 3 - GAME_HEIGHT / 3);

    //asteroid2 initialization
    if (!asteroid2.initialize(gamePtr, asteroidNS::WIDTH, asteroidNS::HEIGHT, 0, &asteroidTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing asteroid2"));
    asteroid2.setX(GAME_WIDTH / 3 - GAME_WIDTH);
    asteroid2.setY(GAME_HEIGHT / 3 - GAME_HEIGHT / 2);

    //asteroid3 initialization
    if (!asteroid3.initialize(gamePtr, asteroidNS::WIDTH, asteroidNS::HEIGHT, 0, &asteroidTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing asteroid3"));

    //asteroid4 initialization
    if (!asteroid4.initialize(gamePtr, asteroidNS::WIDTH, asteroidNS::HEIGHT, 0, &asteroidTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing asteroid4"));
    
    //heal power up (copy paste to add to level)
    //healpowerup textures
    if (!healPowerupTexture.initialize(graphics, HEAL_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healpowerup textures"));

    //heal powerup1
    if (!healPowerup1.initialize(gamePtr, PowerUpNS::WIDTH, PowerUpNS::HEIGHT, 0, &healPowerupTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heal power up1"));
    healPowerup1.setX(GAME_WIDTH / 2.3);
    healPowerup1.setY(GAME_HEIGHT / 3);

    //heal powerup2
    if (!healPowerup2.initialize(gamePtr, PowerUpNS::WIDTH, PowerUpNS::HEIGHT, 0, &healPowerupTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heal power up2"));
    healPowerup2.setX(GAME_WIDTH / 1.7);
    healPowerup2.setY(GAME_HEIGHT / 2);

    //set velocity
    boss3.setVelocity(VECTOR2(boss3NS::SPEED, -boss3NS::SPEED));
    asteroid1.setVelocity(VECTOR2(-asteroidNS::SPEED, asteroidNS::SPEED));
    asteroid2.setVelocity(VECTOR2(asteroidNS::SPEED, -asteroidNS::SPEED));
    asteroid3.setVelocity(VECTOR2(-asteroidNS::SPEED, -asteroidNS::SPEED));
    asteroid4.setVelocity(VECTOR2(asteroidNS::SPEED, asteroidNS::SPEED));

    //projectile array initialization 
    for (int i = 0; i < MAX_PROJECTILES; i++)
    {
        Projectile projectile = boss3Projectile;
        tempProjectiles[i] = projectile;
        projectiles[i] = &tempProjectiles[i];

    }

}





