#include "menu.h"

Menu::Menu()
{

}
Menu::~Menu()
{

}

bool Menu::update(Input * input, Image menuBackground)
{
	
	if (input->getMouseLButton())
	{
		if (input->getMouseX() >  566 && input->getMouseX() < 766) //I had to manually check these values cause for some reason the mouse x values did not match the pixels size from the image, most likely cause i'm running on a lower resolution than the game width + height
		{
			if (input->getMouseY() > 254 && input->getMouseY() < 340) //I had to manually check these values cause for some reason the mouse x values did not match the pixels size from the image
			{
				return true;
			}

		}
		
	}
	return false;
	
}

void Menu::render(Graphics *graphics, TextDX *dxFont, Image menuBackground)
{

	graphics->spriteBegin();
	dxFont->setFontColor(graphicsNS::WHITE);
	dxFont ->print("OVERTALE" ,GAME_WIDTH/2 - 130.0f, GAME_HEIGHT / 8);
	menuBackground.setY(GAME_HEIGHT / 2 - menuBackground.getHeight() / 2);
	menuBackground.setX(GAME_WIDTH / 2 - menuBackground.getWidth() / 2);
	menuBackground.draw();
	


	graphics->spriteEnd();                  
}