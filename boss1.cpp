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
	bounceBool = false;
	projectileSpeed = boss1ProjectileNS::PROJECTILE_EASY_SPEED;
	spawnRate = boss1ProjectileNS::PROJECTILE_EASY_SPAWN;
	spawnTimer = 0;

	
	

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

void Boss1::update(float frameTime, Projectile projectiles[], Player ship)
{
	Entity::update(frameTime);

	spawnProjectiles(projectiles,frameTime,ship);
	if (!bounceBool)
	{
		bounceOff(projectiles);
	}
	
}

void Boss1::setupProjectile(Projectile *projectile, Player ship) //setup projectiles to shoot towards the player
{
	projectile->setX(getX());
	projectile->setY(getY());
	D3DXVECTOR2 shipVector = VECTOR2(ship.getX(),ship.getY());
	D3DXVECTOR2 bossVector = VECTOR2(getX(), getY());
	D3DXVECTOR2 lineVector = VECTOR2(getX() - 1, getY());
	D3DXVECTOR2 horizontalVector = VECTOR2(lineVector - bossVector);
	D3DXVECTOR2 diagonalVector = VECTOR2(shipVector - bossVector);
	graphics->Vector2Normalize(&horizontalVector);
	graphics->Vector2Normalize(&diagonalVector);
	float dotProduct = graphics->Vector2Dot(&horizontalVector, &diagonalVector);
	float angle = acos(dotProduct);
	projectileAngle = (360 * (PI / 180)) - angle;


	D3DXVECTOR2 velocity = VECTOR2(ship.getX()-getX(),ship.getY()-getY());
	projectile->setVelocity(velocity * projectileSpeed);
	projectile->setAngle(projectileAngle);
}

void Boss1::bounceOff(Projectile projectiles[])
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
void Boss1::spawnProjectiles(Projectile projectiles[], float frameTime, Player ship)
{
	spawnTimer += frameTime;
	if (spawnTimer > spawnRate)
	{
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			if (projectiles[i].getActive() == false)
			{
				setupProjectile(&projectiles[i], ship);
				projectiles[i].setActive(true);
				break;
			}
		}
		spawnTimer -=spawnRate;
	}
}

