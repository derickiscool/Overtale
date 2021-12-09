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
    frameDelay = playerNS::SHIP_ANIMATION_DELAY;
    startFrame = playerNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame = playerNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    health = 100;
    radius = playerNS::WIDTH / 2.0;
    collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game* gamePtr, int width, int height, int ncols,
    TextureManager* textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{
    Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
    Entity::update(frameTime);


    if (input->isKeyDown(SHIP1_RIGHT_KEY))            // if move right
    {
        spriteData.x = spriteData.x + playerNS::SPEED;
    }

    if (input->isKeyDown(SHIP1_LEFT_KEY))            // if move left
    {
        spriteData.x = spriteData.x - playerNS::SPEED;
    }

    if (input->isKeyDown(SHIP1_UP_KEY))            // if move up
    {
        spriteData.y = spriteData.y - playerNS::SPEED;
    }

    if (input->isKeyDown(SHIP1_DOWN_KEY))            // if move down
    {
        spriteData.y = spriteData.y + playerNS::SPEED;
    }


    if (spriteData.x > boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH)    //if touching boundary      
        spriteData.x = (boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH);

    if (spriteData.x < boundaryEnvironmentNS::MIN_X)
        spriteData.x = ((float)boundaryEnvironmentNS::MIN_X);

    if (spriteData.y > boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT)
        spriteData.y = ((float)boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT);
    if (spriteData.y < boundaryEnvironmentNS::MIN_Y)
        spriteData.y = ((float)boundaryEnvironmentNS::MIN_Y);

}
