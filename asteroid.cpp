#include "asteroid.h"

//=============================================================================
// default constructor
//=============================================================================
Asteroid::Asteroid() : Entity()
{
	spriteData.width = asteroidNS::WIDTH;           // size of asteroid
	spriteData.height = asteroidNS::HEIGHT;
	spriteData.x = asteroidNS::X;              // location on screen
	spriteData.y = asteroidNS::Y;
	radius = asteroidNS::COLLISION_RADIUS;
	mass = asteroidNS::MASS;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
}

bool Asteroid::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Asteroid::draw()
{
	Image::draw();
}

void Asteroid::update(float frameTime)
{

	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move asteroid along X 
	spriteData.y += frameTime * velocity.y;         // move asteroid along Y

	// Bounce off walls
	if (spriteData.x > boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = (boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH);    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < boundaryEnvironmentNS::MIN_X)                    // else if hit left screen edge
	{
		spriteData.x = ((float)boundaryEnvironmentNS::MIN_X);                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = ((float)boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT);  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < boundaryEnvironmentNS::MIN_Y)                    // else if hit top screen edge
	{
		spriteData.y = ((float)boundaryEnvironmentNS::MIN_Y);                           // position at top screen edge
		velocity.y = -velocity.y;                  // reverse Y direction
	}

}
