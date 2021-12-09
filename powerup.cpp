#include "powerup.h"
#include<iostream>

Powerup::Powerup()
{
	//animation
	spriteData.width = PowerUpNS::WIDTH;           // size of power up
	spriteData.height = PowerUpNS::HEIGHT;
	spriteData.x = PowerUpNS::X;                   // location on screen
	spriteData.y = PowerUpNS::Y;
	spriteData.rect.bottom = PowerUpNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = PowerUpNS::WIDTH;
	currentFrame = startFrame;

	//powerup variables
	check = true;
}

bool Powerup::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Powerup::draw()
{
	Image::draw();
}

void Powerup::deletePowerup()
{
	Entity::setActive(false);
	Image::setVisible(false);
}

