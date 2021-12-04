#include "boss1.h"

Boss1::Boss1()
{
	//animation
	spriteData.width = boss1NS::WIDTH;           // size of boss1
	spriteData.height = boss1NS::HEIGHT;
	spriteData.x = boss1NS::X;                   // location on screen
	spriteData.y = boss1NS::Y;
	frameDelay = boss1NS::ANIMATION_DELAY;
	startFrame = boss1NS::START_FRAME;     // first frame of boss1 animation
	endFrame = boss1NS::END_FRAME;     // last frame of boss1 animation
	spriteData.rect.bottom = boss1NS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = boss1NS::WIDTH;
	currentFrame = startFrame;

	//boss variables
	bounce = false;

	
	

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

void Boss1::update(float frameTime, Projectile projectiles[])
{
	Entity::update(frameTime);
	if (!bounce)
	{
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			if (projectiles[i].getX() > boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH)    //if touching boundary      
				projectiles[i].setActive(false);

			if (projectiles[i].getX() < boundaryEnvironmentNS::MIN_X)
				projectiles[i].setActive(false);


			if (projectiles[i].getY() > boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT)
				projectiles[i].setActive(false);
		}
	}
	
}

void Boss1::setupProjectile(Projectile *projectile, Player ship) //setup projectiles to shoot towards the player
{


	
	//angle facing is determined by the angle between the player and the boss at any given time , use dot product
	/*D3DXVECTOR2 bossVector = VECTOR2(30,50);
	D3DXVECTOR2 shipVector = VECTOR2(30,50);
	graphics->Vector2Normalize(&bossVector);
	graphics->Vector2Normalize(&shipVector);
	angleFacing = graphics->Vector2Dot(&bossVector, &shipVector);*/
	angleFacing = 110;
	projectileAngle = roundf((90 - angleFacing) * (PI / 180.0) * 100) / 100; //need to round to two decimal places as cos is dumb on c++
	projectileYSpeed = boss1ProjectileNS::PROJECTILE_EASY_SPEED; 
	projectileXSpeed = projectileYSpeed * tan(projectileAngle);//use pythagoras to determine x speed
	D3DXVECTOR2 velocity = VECTOR2(projectileXSpeed, projectileYSpeed);
	projectile->setAngle(angleFacing * (PI/180));
	projectile->setVelocity(velocity);
}



