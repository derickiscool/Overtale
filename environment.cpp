#include "environment.h"


Environment::Environment():Entity()
{
	spriteData.width = floorEnvironmentNS::WIDTH;           // size of tiles
	spriteData.height = floorEnvironmentNS::HEIGHT;		 
    spriteData.x = floorEnvironmentNS::START_LOCATION_X;                   // location on screen
    spriteData.y = floorEnvironmentNS::START_LOCATION_Y;
    radius = boundaryEnvironmentNS::WIDTH;
    collisionType = entityNS::CIRCLE;
    mass = 500.0f;

}   


bool Environment::initialize(Game* gamePtr, int width, int height, int ncols,
    TextureManager* textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Environment::draw()
{
	Image::draw();
}
