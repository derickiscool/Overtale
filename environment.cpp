#include "environment.h"


Environment::Environment():Entity()
{
    blockMovement = false;
	spriteData.width = floorEnvironmentNS::WIDTH;           // size of tiles
	spriteData.height = floorEnvironmentNS::HEIGHT;		 
    spriteData.x = floorEnvironmentNS::START_LOCATION_X;                   // location on screen
    spriteData.y = floorEnvironmentNS::START_LOCATION_Y;

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

void Environment::updateBlockMovement(bool move)
{
    blockMovement = move;
}

