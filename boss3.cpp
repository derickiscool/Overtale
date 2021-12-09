#include "boss3.h"
#include<iostream>

//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Ben Chang
//  Student Number:     S10185167

Boss3::Boss3()
{
	//animation
	spriteData.width = boss3NS::WIDTH;           // size of boss3
	spriteData.height = boss3NS::HEIGHT;
	spriteData.x = boss3NS::X;                   // location on screen
	spriteData.y = boss3NS::Y;
	frameDelay = boss3NS::ANIMATION_DELAY;
	startFrame = boss3NS::START_FRAME;     // first frame of boss3 animation
	endFrame = boss3NS::END_FRAME;     // last frame of boss3 animation
	spriteData.rect.bottom = boss3NS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = boss3NS::WIDTH;
	currentFrame = startFrame;

	//boss variables
	projectileSpeed = boss3ProjectileNS::PROJECTILE_EASY_SPEED;
	spawnRate = boss3ProjectileNS::PROJECTILE_EASY_SPAWN;
	timer = 0;
	spawnTimer = 0;
	waveValue = Wave::wave1;
	activeProjectiles = 0;
	spawnBool = true;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y




}
bool Boss3::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Boss3::draw()
{
	Image::draw();
}

void Boss3::update(float frameTime, Projectile* projectiles[])
{

	Entity::update(frameTime);
	updateAbilities(projectiles, frameTime);

	spriteData.x += frameTime * velocity.x;         // move boss along X 
	spriteData.y += frameTime * velocity.y;         // move boss along Y

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

void Boss3::projectileInitialization(Projectile* projectile)//Initialize projectiles
{
	projectile->setWidth(boss3ProjectileNS::WIDTH);
	projectile->setHeight(boss3ProjectileNS::HEIGHT);
	projectile->setX(getX());
	projectile->setX(getY());
	projectile->setRectBottom(boss3ProjectileNS::HEIGHT);
	projectile->setRectRight(boss3ProjectileNS::WIDTH);
	projectile->setCurrentFrame(startFrame);
	projectile->setCollisionType(entityNS::CIRCLE);
	projectile->setLoop(false);
	projectile->setCollisionRadius(boss3ProjectileNS::WIDTH / 4);
	projectile->setProjectileDamage(0);
	projectile->setActive(false);
	projectile->setMass(300.0f);
}

void Boss3::setupProjectileLeftRight(Projectile* projectile1, Projectile* projectile2) //setup projectiles velocity
{
	projectile1->setX(getX());
	projectile1->setY(getY());
	projectile2->setX(getX());
	projectile2->setY(getY());
	
	D3DXVECTOR2 velocity1 = VECTOR2(-getX(), 0);
	D3DXVECTOR2 velocity2 = VECTOR2(getX(), 0);

	projectile1->setVelocity(velocity1 * projectileSpeed);
	projectile2->setVelocity(velocity2 * projectileSpeed);
	
}



void Boss3::setupProjectileUpDownLeftRight(Projectile* projectile1, Projectile* projectile2, Projectile* projectile3, Projectile* projectile4) //setup projectiles velocity 
{
	projectile1->setX(getX());
	projectile1->setY(getY());
	projectile2->setX(getX());
	projectile2->setY(getY());
	projectile3->setX(getX());
	projectile3->setY(getY());
	projectile4->setX(getX());
	projectile4->setY(getY());

	D3DXVECTOR2 velocity1 = VECTOR2(-getX(), 0);
	D3DXVECTOR2 velocity2 = VECTOR2(getX(), 0);
	D3DXVECTOR2 velocity3 = VECTOR2(0, -getY());
	D3DXVECTOR2 velocity4 = VECTOR2(0, getY());
	projectile1->setVelocity(velocity1 * projectileSpeed);
	projectile2->setVelocity(velocity2 * projectileSpeed);
	projectile3->setVelocity(velocity3 * projectileSpeed);
	projectile4->setVelocity(velocity4 * projectileSpeed);

}


void Boss3::setupProjectileAll(Projectile* projectile1, Projectile* projectile2, Projectile* projectile3, Projectile* projectile4,
	Projectile* projectile5, Projectile* projectile6, Projectile* projectile7, Projectile* projectile8) //setup projectiles velocity 
{
	projectile1->setX(getX());
	projectile1->setY(getY());
	projectile2->setX(getX());
	projectile2->setY(getY());
	projectile3->setX(getX());
	projectile3->setY(getY());
	projectile4->setX(getX());
	projectile4->setY(getY());
	projectile5->setX(getX());
	projectile5->setY(getY());


	projectile6->setX(getX());
	projectile6->setY(getY());
	projectile7->setX(getX());
	projectile7->setY(getY());
	projectile8->setX(getX());
	projectile8->setY(getY());

	D3DXVECTOR2 velocity1 = VECTOR2(-getX(), 0);
	D3DXVECTOR2 velocity2 = VECTOR2(getX(), 0);
	D3DXVECTOR2 velocity3 = VECTOR2(0, -getY());
	D3DXVECTOR2 velocity4 = VECTOR2(0, getY());

	//bottom right
	D3DXVECTOR2 velocity5 = VECTOR2(getX(), getY());

	//top right
	D3DXVECTOR2 velocity6 = VECTOR2(getX(), -getY());

	//bottom left
	D3DXVECTOR2 velocity7 = VECTOR2(-getX(), getY());

	//top left
	D3DXVECTOR2 velocity8 = VECTOR2(-getX(), -getY());


	projectile1->setVelocity(velocity1 * projectileSpeed);
	projectile2->setVelocity(velocity2 * projectileSpeed);
	projectile3->setVelocity(velocity3 * projectileSpeed);
	projectile4->setVelocity(velocity4 * projectileSpeed);

	projectile5->setVelocity(velocity5 * projectileSpeed);
	projectile6->setVelocity(velocity6 * projectileSpeed);
	projectile7->setVelocity(velocity7 * projectileSpeed);
	projectile8->setVelocity(velocity8 * projectileSpeed);

}

void Boss3::spawnProjectilesLeftRight(Projectile* projectiles[], float frameTime)
{

	if (spawnBool)
	{
		spawnTimer += frameTime;
		if (spawnTimer > spawnRate)
		{
			for (int i = 0; i < MAX_PROJECTILES; i += 2)
			{
				if (projectiles[i]->getActive() == false)
				{
					setupProjectileLeftRight(projectiles[i], projectiles[i + 1]);
					projectiles[i]->setActive(true);
					projectiles[i + 1]->setActive(true);
					activeProjectiles += 2;

					break;
				}
			}
			spawnTimer -= spawnRate;
		}

	}
}


void Boss3::spawnProjectilesUpDownLeftRight(Projectile* projectiles[], float frameTime)
{
	if (spawnBool)
	{
		spawnTimer += frameTime;
		if (spawnTimer > spawnRate)
		{
			for (int i = 0; i < MAX_PROJECTILES; i += 4)
			{
				if (projectiles[i]->getActive() == false)
				{
					setupProjectileUpDownLeftRight(projectiles[i], projectiles[i + 1], projectiles[i + 2], projectiles[i + 3]);
					projectiles[i]->setActive(true);
					projectiles[i + 1]->setActive(true);
					projectiles[i + 2]->setActive(true);
					projectiles[i + 3]->setActive(true);
					activeProjectiles += 4;

					break;
				}
			}
			spawnTimer -= spawnRate;
		}

	}
}

void Boss3::spawnProjectilesAll(Projectile* projectiles[], float frameTime)
{
	if (spawnBool)
	{
		spawnTimer += frameTime;
		if (spawnTimer > spawnRate)
		{
			for (int i = 0; i < MAX_PROJECTILES; i++)
			{
				if (projectiles[i]->getActive() == false)
				{
					setupProjectileAll(projectiles[i], projectiles[i + 1], projectiles[i + 2], projectiles[i + 3], projectiles[i + 4]
						, projectiles[i + 5], projectiles[i + 6], projectiles[i + 7]);
					projectiles[i]->setActive(true);
					projectiles[i + 1]->setActive(true);
					projectiles[i + 2]->setActive(true);
					projectiles[i + 3]->setActive(true);
					projectiles[i + 4]->setActive(true);
					projectiles[i + 5]->setActive(true);
					projectiles[i + 6]->setActive(true);
					projectiles[i + 7]->setActive(true);
					activeProjectiles += 8;

					break;
				}
			}
			spawnTimer -= spawnRate;
		}

	}
}

void Boss3::updateAbilities(Projectile* projectiles[], float frameTime)
{
	timer += frameTime;
	if (timer > 30.f & timer < 35.0f)
	{
		resetSpawn();
		projectiles[0]->clearProjectiles(projectiles);
	}
	if (timer > 60.0f & timer < 65.0f)
	{
		resetSpawn();
		projectiles[0]->clearProjectiles(projectiles);
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
		spawnProjectilesLeftRight(projectiles, frameTime);
		projectileSpeed = boss3ProjectileNS::PROJECTILE_EASY_SPEED;
		spawnRate = boss3ProjectileNS::PROJECTILE_EASY_SPAWN;
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			projectiles[i]->setProjectileDamage(10);
		}
		break;

	case wave2:
		spawnProjectilesUpDownLeftRight(projectiles, frameTime);
		projectileSpeed = boss3ProjectileNS::PROJECTILE_MEDIUM_SPEED;
		spawnRate = boss3ProjectileNS::PROJECTILE_MEDIUM_SPAWN;
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			projectiles[i]->setProjectileDamage(7);
		}
		break;

	case wave3:
		spawnProjectilesAll(projectiles, frameTime);
		projectileSpeed = boss3ProjectileNS::PROJECTILE_HARD_SPEED;
		spawnRate = boss3ProjectileNS::PROJECTILE_HARD_SPAWN;
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			projectiles[i]->setProjectileDamage(5);
		}
		break;
	}

}

void Boss3::resetSpawn()
{
	spawnBool = false;
	spawnTimer = 0;
	activeProjectiles = 0;
}


