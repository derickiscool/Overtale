#include "projectile.h"

Projectile::Projectile()
{
	spriteData.width = boss1ProjectileNS::WIDTH;           // size of tiles
	spriteData.height = boss1ProjectileNS::HEIGHT;
	spriteData.x = boss1ProjectileNS::X;                   // location on screen
	spriteData.y = boss1ProjectileNS::Y;
	frameDelay = boss1ProjectileNS::ANIMATION_DELAY;
	startFrame = boss1ProjectileNS::START_FRAME;     // first frame of ship animation
	endFrame = boss1ProjectileNS::END_FRAME;     // last frame of ship animation
	spriteData.rect.bottom = boss1ProjectileNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = boss1ProjectileNS::WIDTH;
	currentFrame = startFrame;
	collisionType = entityNS::CIRCLE;
	loop = false;


}
bool Projectile::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Projectile::draw()
{
	Image::draw();
}

void Projectile::update(float frameTime)
{

	Entity::update(frameTime);
}

