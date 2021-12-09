//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Fong Kai Liang
//  Student Number:     S10196491


#include "boss2.h"
#include<iostream>
#include <random>

using namespace std;

int main()
{
	//random number for coordinate X
	srand(time(NULL));

	cout << rand() % 1920;

	//random number for cooardinate Y
	srand(time(NULL));

	cout << rand() % 1080;
}

Boss2::Boss2()
{
	//animation
	spriteData.width = boss2NS::WIDTH;           // size of boss2
	spriteData.height = boss2NS::HEIGHT;
	spriteData.x = boss2NS::X;                   // location on screen
	spriteData.y = boss2NS::Y;
	frameDelay = boss2NS::ANIMATION_DELAY;
	startFrame = boss2NS::START_FRAME;     // first frame of boss1 animation
	endFrame = boss2NS::END_FRAME;     // last frame of boss1 animation
	spriteData.rect.bottom = boss2NS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = boss2NS::WIDTH;
	currentFrame = startFrame;

	//boss variables
	projectileSpeed = boss2ProjectileNS::PROJECTILE_EASY_SPEED;
	spawnRate = boss2ProjectileNS::PROJECTILE_EASY_SPAWN;
	timer = 0;
	spawnTimer = 0;
	waveValue = Wave::wave1;
	activeProjectiles = 0;
	spawnBool = true;
	bossSpeed = 2.0f;
	bossMovementEnum = 3;
}

bool Boss2::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Boss2::draw()
{
	Image::draw();
}


void Boss2::update(float frameTime, Projectile* projectiles[], Player ship)
{
	Entity::update(frameTime);
	updateAbilities(projectiles, frameTime);
	spawnProjectiles(projectiles, frameTime, ship);
}

void Boss2::projectileInitialization(Projectile* projectile)//Initialize projectiles
{
	projectile->setWidth(boss1ProjectileNS::WIDTH);
	projectile->setHeight(boss1ProjectileNS::HEIGHT);
	projectile->setX(getX());
	projectile->setX(getY());
	projectile->setFrameDelay(0.2f);
	projectile->setStartFrame(boss1ProjectileNS::START_FRAME);
	projectile->setEndFrame(boss1ProjectileNS::END_FRAME);
	projectile->setRectBottom(boss1ProjectileNS::HEIGHT);
	projectile->setRectRight(boss1ProjectileNS::WIDTH);
	projectile->setCurrentFrame(startFrame);
	projectile->setCollisionType(entityNS::CIRCLE);
	projectile->setLoop(false);
	projectile->setCollisionRadius(boss1ProjectileNS::WIDTH / 4);
	projectile->setProjectileDamage(0);
	projectile->setFrames(boss1ProjectileNS::START_FRAME, boss1ProjectileNS::END_FRAME);
	projectile->setCurrentFrame(boss1ProjectileNS::START_FRAME);
	projectile->setActive(false);
	projectile->setMass(300.0f);
}

void Boss2::setupProjectile(Projectile* projectile, Player ship) //setup projectiles to shoot towards the player
{
	projectile->setX(getX());
	projectile->setY(getY());
	D3DXVECTOR2 shipVector = VECTOR2(ship.getX(), ship.getY());
	D3DXVECTOR2 bossVector = VECTOR2(getX(), getY());
	D3DXVECTOR2 lineVector = VECTOR2(getX() - 1, getY());
	D3DXVECTOR2 horizontalVector = VECTOR2(lineVector - bossVector);
	D3DXVECTOR2 diagonalVector = VECTOR2(shipVector - bossVector);
	graphics->Vector2Normalize(&horizontalVector);
	graphics->Vector2Normalize(&diagonalVector);
	float dotProduct = graphics->Vector2Dot(&horizontalVector, &diagonalVector);
	float angle = acos(dotProduct);
	projectileAngle = (360 * (PI / 180)) - angle;


	D3DXVECTOR2 velocity = VECTOR2(ship.getX() - getX(), ship.getY() - getY());
	projectile->setVelocity(velocity * projectileSpeed);
	projectile->setAngle(projectileAngle);
}

void Boss2::bounceOff(Projectile* projectiles[]) //delete projectiles when hit on wall
{
	for (int i = 0; i < activeProjectiles; ++i)
	{
		if (projectiles[i]->getActive())
		{
			if (projectiles[i]->getX() > boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH)    //if touching boundary      
			{
				projectiles[i]->setActive(false);
				activeProjectiles -= 1;
				break;
			}


			if (projectiles[i]->getX() < boundaryEnvironmentNS::MIN_X)

			{
				projectiles[i]->setActive(false);
				activeProjectiles -= 1;
				break;
			}


			if (projectiles[i]->getY() > boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT)
			{
				projectiles[i]->setActive(false);
				activeProjectiles -= 1;
				break;
			}

		}

	}
}
void Boss2::spawnProjectiles(Projectile* projectiles[], float frameTime, Player ship) //projectile spawning
{

	if (spawnBool)
	{
		spawnTimer += frameTime;
		if (spawnTimer > spawnRate)
		{
			for (int i = 0; i < MAX_PROJECTILES; ++i)
			{
				if (projectiles[i]->getActive() == false)
				{
					setupProjectile(projectiles[i], ship);
					projectiles[i]->setActive(true);
					activeProjectiles += 1;

					break;
				}
			}
			spawnTimer -= spawnRate;
		}

	}
}

void Boss2::updateAbilities(Projectile* projectiles[], float frameTime)
{

	//timer
	timer += frameTime;
	if (timer > boss2NS::wave2Time - 5.0f & timer < boss2NS::wave2Time)
	{
		resetSpawn();
		projectiles[0]->clearProjectiles(projectiles);
	}
	
	else if (timer > boss2NS::wave2Time)
	{
		if (!spawnBool)
		{
			spawnBool = true;
		}
		waveValue = wave2;
	}


	switch (waveValue) //Setting projectile data and abilities based on wave
	{
	case wave1:
		projectileSpeed = boss2ProjectileNS::PROJECTILE_EASY_SPEED;
		spawnRate = boss2ProjectileNS::PROJECTILE_EASY_SPAWN;
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			projectiles[i]->setProjectileDamage(5);
		}
		bounceOff(projectiles);
		break;

	case wave2:
		projectileSpeed = boss2ProjectileNS::PROJECTILE_MEDIUM_SPEED;
		spawnRate = boss2ProjectileNS::PROJECTILE_MEDIUM_SPAWN;
		
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			projectiles[i]->setProjectileDamage(10);
		}
		bounceOff(projectiles);
		break;


	}


}

void Boss2::startBounce(Projectile* projectiles[], Environment crates[]) //bounces projectiles
{

	VECTOR2 collisionVector;
	for (int i = 0; i < activeProjectiles; ++i)
	{
		bool flag1 = (projectiles[i]->getY() >= boundaryEnvironmentNS::MIN_Y - boundaryEnvironmentNS::HEIGHT / 2); // inside box from top 
		bool flag2 = (projectiles[i]->getY() < boundaryEnvironmentNS::MAX_Y - boundaryEnvironmentNS::HEIGHT);
		bool flag3 = (projectiles[i]->getX() >= boundaryEnvironmentNS::MIN_X - boundaryEnvironmentNS::WIDTH / 2);
		bool flag4 = (projectiles[i]->getX() < boundaryEnvironmentNS::MAX_X - boundaryEnvironmentNS::WIDTH);
		if (flag1 && flag2 && flag3 && flag4) //check if projectile is current outside box
		{
			for (int j = 0; j < CRATES_NEEDED; ++j)
			{
				if (projectiles[i]->collidesWith(crates[j], collisionVector))
				{
					projectiles[i]->bounce(collisionVector, crates[j]);
					VECTOR2 normalVector = VECTOR2(collisionVector.x - 16, collisionVector.y);
					normalVector = normalVector - collisionVector;
					graphics->Vector2Normalize(&normalVector);
					graphics->Vector2Normalize(&collisionVector);

					float dotProduct = graphics->Vector2Dot(&normalVector, &collisionVector);
					float angle = acos(dotProduct);
					projectiles[i]->setAngle(projectiles[i]->getAngle() + angle);



				}
			}
		}

	}


}
void Boss2::resetSpawn()
{
	spawnBool = false;
	spawnTimer = 0;
	activeProjectiles = 0;
}

