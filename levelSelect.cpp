#include "levelSelect.h"

LevelSelect::LevelSelect()
{

}
LevelSelect::~LevelSelect()
{

}

int LevelSelect::update(Input* input)
{
	if (input->getMouseLButton())
	{
		if (input->getMouseY() > 259 && input->getMouseY() < 468) 
		{
			if (input->getMouseX() > 406 && input->getMouseX() < 569) 
			{
				return 1;
			}
			else if (input->getMouseX() > 613 && input->getMouseX() < 783)
			{
				return 2;
			}
			else if (input->getMouseX() > 807 && input->getMouseX() < 972)
			{
				return 3;
			}

		}

	}
	return 0;

}

void LevelSelect::render(Graphics* graphics, TextDX* dxFont, Image background)
{

	graphics->spriteBegin();
	dxFont->setFontColor(graphicsNS::WHITE);
	dxFont->print("Level Select", GAME_WIDTH / 2 - 130.0f, GAME_HEIGHT / 8);
	background.setY(GAME_HEIGHT / 2 - background.getHeight() / 2);
	background.setX(GAME_WIDTH / 2 - background.getWidth() / 2);
	background.draw();



	graphics->spriteEnd();
}