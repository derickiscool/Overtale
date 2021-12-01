#include "player.h"

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
    spriteData.width = playerNS::WIDTH;           // size of Ship1
    spriteData.height = playerNS::HEIGHT;
    spriteData.x = playerNS::X;                   // location on screen
    spriteData.y = playerNS::Y;
    spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = playerNS::WIDTH;
    //velocity.x = 0;                             // velocity X
    //velocity.y = 0;                             // velocity Y
    frameDelay = playerNS::SHIP_ANIMATION_DELAY;
    startFrame = playerNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame = playerNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    shieldOn = false;
   /* radius = playerNS::WIDTH / 2.0;
    mass = playerNS::MASS;
    collisionType = entityNS::CIRCLE;*/
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game* gamePtr, int width, int height, int ncols,
    TextureManager* textureM)
{
    //code for shield from practical
    //shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
    //shield.setFrames(playerNS::SHIELD_START_FRAME, playerNS::SHIELD_END_FRAME);
    //shield.setCurrentFrame(playerNS::SHIELD_START_FRAME);
    //shield.setFrameDelay(playerNS::SHIELD_ANIMATION_DELAY);
    //shield.setLoop(false);                  // do not loop animation
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{
    Image::draw();              // draw ship
    //code for shield from practical
    //if (shieldOn)
    //    // draw shield using colorFilter 50% alpha
    //    shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y

   //code for shield from practical
   /* if (shieldOn)
    {
        shield.update(frameTime);
        if (shield.getAnimationComplete())
        {
            shieldOn = false;
            shield.setAnimationComplete(false);
        }
    }*/
}
