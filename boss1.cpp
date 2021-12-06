#include "boss1.h"
#include<iostream>

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
	timer = 0;
	spawnTimer = 0;
	waveValue = Wave::wave1;
	activeProjectiles = 0;
	spawnBool = true;


	
	

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
	updateAbilities(projectiles, frameTime);
	spawnProjectiles(projectiles,frameTime,ship);
	
	
}
void Boss1::projectileInitialization(Projectile *projectile)//Initialize projectiles
{
	projectile->setWidth(boss1ProjectileNS::WIDTH);
	projectile->setHeight(boss1ProjectileNS::HEIGHT);
	projectile->setX(getX());
	projectile->setX(getY());
	projectile->setFrameDelay(boss1ProjectileNS::ANIMATION_DELAY);
	projectile->setStartFrame(boss1ProjectileNS::START_FRAME);
	projectile->setEndFrame(boss1ProjectileNS::END_FRAME);
	projectile->setRectBottom(boss1ProjectileNS::HEIGHT);
	projectile->setRectRight(boss1ProjectileNS::WIDTH);
	projectile->setCurrentFrame(startFrame);
	projectile->setCollisionType(entityNS::CIRCLE);
	projectile->setLoop(false);
	projectile->setProjectileDamage(0);
	projectile->setFrames(boss1ProjectileNS::START_FRAME, boss1ProjectileNS::END_FRAME);
	projectile->setCurrentFrame(boss1ProjectileNS::START_FRAME);
	projectile->setActive(false);
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
	for (int i = 0; i < activeProjectiles; ++i)
	{
		if (projectiles[i].getActive())
		{
			if (projectiles[i].getX() > boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH)    //if touching boundary      
			{
				projectiles[i].setActive(false);
				activeProjectiles -= 1;
				break;
			}


			if (projectiles[i].getX() < boundaryEnvironmentNS::MIN_X)

			{
				projectiles[i].setActive(false);
				activeProjectiles -= 1;
				break;
			}


			if (projectiles[i].getY() > boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT)
			{
				projectiles[i].setActive(false);
				activeProjectiles -= 1;
				break;
			}

		}
			
	}
}
void Boss1::spawnProjectiles(Projectile projectiles[], float frameTime, Player ship)
{
	
	if (spawnBool)
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
					activeProjectiles += 1;

					break;
				}
			}
			spawnTimer -= spawnRate;
		}

	}
}

void Boss1::updateAbilities(Projectile projectiles[], float frameTime)
{
	timer += frameTime;
	if (timer > 30.f & timer < 35.0f )
	{
		resetSpawn();
		projectiles->clearProjectiles(projectiles);
	}
	if (timer > 60.0f & timer <65.0f)
	{
		resetSpawn();
		projectiles->clearProjectiles(projectiles);
	}
	if (timer > 65.0f)
	{
		if (!spawnBool)
		{
			spawnBool = true;
		}
		waveValue = wave3;
	}
	else if (timer > 35.0f & timer < 60.0f)
	{
		if (!spawnBool)
		{
			spawnBool = true;
		}
		waveValue = wave2;
	}

	
	switch (waveValue)
	{
	case wave1:
		projectileSpeed = boss1ProjectileNS::PROJECTILE_EASY_SPEED;
		spawnRate = boss1ProjectileNS::PROJECTILE_EASY_SPAWN;
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			projectiles[i].setProjectileDamage(5);
		}
		bounceOff(projectiles);
		break;
		
	case wave2:
		projectileSpeed = boss1ProjectileNS::PROJECTILE_MEDIUM_SPEED;
		spawnRate = boss1ProjectileNS::PROJECTILE_MEDIUM_SPAWN;
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			projectiles[i].setProjectileDamage(10);
		}
		startBounce(projectiles);
		break;

	case wave3:
		projectileSpeed = boss1ProjectileNS::PROJECTILE_HARD_SPEED;
		spawnRate = boss1ProjectileNS::PROJECTILE_HARD_SPAWN;
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			projectiles[i].setProjectileDamage(15);
		}
		startBounce(projectiles);
		break;
	}
	

}

void Boss1::startBounce(Projectile projectiles[]) //bounces projectiles
{
	/*for (int i = 0; i < activeProjectiles; ++i)
	{
		if (projectiles[i].getX() > boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH)
		{
			projectiles[i].setX(boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH);
			VECTOR2 vel = projectiles[i].getVelocity();
			vel.x = -vel.x;
			projectiles[i].setVelocity(vel);
		}
		if (projectiles[i].getX() < boundaryEnvironmentNS::MIN_X)
		{

			projectiles[i].setX(boundaryEnvironmentNS::MIN_X);
			VECTOR2 vel = projectiles[i].getVelocity();
			vel.x = -vel.x;
			projectiles[i].setVelocity(vel);
		}
		if (projectiles[i].getY() > boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT)
		{

			projectiles[i].setY(boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT);
			VECTOR2 vel = projectiles[i].getVelocity();
			vel.y = -vel.y;
			projectiles[i].setVelocity(vel);
		}
		if (projectiles[i].getY() < boundaryEnvironmentNS::MIN_Y)
		{

			projectiles[i].setY(boundaryEnvironmentNS::MIN_Y);
			VECTOR2 vel = projectiles[i].getVelocity();
			vel.y = -vel.y;
			projectiles[i].setVelocity(vel);
		}



	}*/




	
	
}
void Boss1::resetSpawn()
{
	spawnBool = false;
	spawnTimer = 0;
	activeProjectiles = 0;
}


