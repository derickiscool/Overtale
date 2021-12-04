#include "boss1.h"

Boss1::Boss1()
{
	spriteData.width = boss1NS::WIDTH;           // size of tiles
	spriteData.height = boss1NS::HEIGHT;
	spriteData.x = boss1NS::X;                   // location on screen
	spriteData.y = boss1NS::Y;
	frameDelay = boss1NS::ANIMATION_DELAY;
	startFrame = boss1NS::START_FRAME;     // first frame of ship animation
	endFrame = boss1NS::END_FRAME;     // last frame of ship animation
	spriteData.rect.bottom = boss1NS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = boss1NS::WIDTH;
	currentFrame = startFrame;
}
bool Boss1::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Boss1::draw()
{
	Image::draw();
}

void Boss1::update(float frameTime)
{

	Entity::update(frameTime);
}

