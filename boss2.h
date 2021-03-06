// Module: Gameplay Programming
// Assignment1: Overtale
// Student Name: Fong Kai Liang
// Student Number: S10196491



#ifndef _BOSS2_H // Prevent multiple definitions if this
#define _BOSS2_H // file is included in more than one place
#define WIN32_LEAN_AND_MEAN



#include "entity.h"
#include "constants.h"
#include "projectile.h"
#include "environment.h"
#include "player.h"



namespace boss2NS
{
	const int WIDTH = 126; // image width
	const int HEIGHT = 85; // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int Y = boss2NS::HEIGHT;
	const int MAX_X = boundaryEnvironmentNS::MAX_X + boss2NS::WIDTH;
	const int MAX_Y = boundaryEnvironmentNS::MAX_Y + boss2NS::HEIGHT;
	const int MIN_X = boundaryEnvironmentNS::MIN_X - boss2NS::WIDTH;
	const int MIN_Y = boss2NS::HEIGHT;
	const int TEXTURE_COLS = 0; // texture has 8 columns
	const int START_FRAME = 0; // starts at frame 0
	const int END_FRAME = 5; // animation frames 0,1,2,3,4
	const float ANIMATION_DELAY = 0.2f; // time between frames
	const float wave2Time = 30.0f; //When should wave 2 start

}

// inherits from Entity class
class Boss2 : public Entity
{
protected:

	enum Wave
	{
		wave1,
		wave2
	};



	Wave waveValue; //current wave
	float projectileAngle; //angle the projectile needs to curve, to hit the player
	float projectileSpeed; //speed of projectile
	float spawnRate; //spawnRate of projectiles in seconds
	float spawnTimer; //timer to track spawning
	float timer; //timer to keep track of boss;
	int activeProjectiles; //Number of active projectiles;
	bool spawnBool; //true if want to spawn projectiles, false if projectiles should not spawn


public:
	// constructor
	Boss2();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
		TextureManager* textureM);
	void update(float frameTime, Projectile* projectiles[], Player ship);
	void projectileInitialization(Projectile* projectile);
	void setupProjectile(Projectile* projectile, Player ship);//Setting up velocity + angle of projectiles
	void bounceOff(Projectile* projectiles[]); //removes entities when touching boundaries
	void spawnProjectiles(Projectile* projectiles[], float frameTime, Player ship);
	void updateAbilities(Projectile* projectiles[], float frameTime);
	void resetSpawn();


	//get setters
	void setX(float x) { spriteData.x = x; };



	float getX() { return spriteData.x; };



	void setY(float y) { spriteData.y = y; };



	float getY() { return spriteData.y; };



	float getSpawnTimer() { return spawnTimer; };



	float getTimer() { return timer; };

	void setTimer(float t) { timer = t; };

	int getWaveValue() { return waveValue; };



	void setActiveProjectiles(int newActiveProjectiles) { activeProjectiles = newActiveProjectiles; };



	int getActiveProjectiles() { return activeProjectiles; };



};
#endif