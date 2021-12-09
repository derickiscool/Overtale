#include "levelSelect.h"


LevelSelect::LevelSelect()
{
	counter = 0;
}

LevelSelect::~LevelSelect()
{

}


void LevelSelect::initialize(Graphics* g, Game* ptr)
{
	graphics = g;
	gamePtr = ptr;

	//Background texture
	if (!levelSelectBackgroundTexture.initialize(g, LEVEL_SELECT_BACKGROUND))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu background texture"));

	//arrow texture
	if (!arrowTexture.initialize(g, MENU_ARROW_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu arrow texture"));

	if (!levelSelectBackground.initialize(g, 0, 0, 0, &levelSelectBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu image texture"));

	if (!arrow.initialize(g, 0, 0, 0, &arrowTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing arrow image texture"));




	//initialize ArrowPositions
	arrowPositions[0] = new ArrowXY(arrowNS::BOSS1_OPTION_POSITION_X, arrowNS::BOSS1_OPTION_POSITION_Y);
	arrowPositions[1] = new ArrowXY(arrowNS::BOSS2_OPTION_POSITION_X, arrowNS::BOSS2_OPTION_POSITION_Y);
	arrowPositions[2] = new ArrowXY(arrowNS::BOSS3_OPTION_POSITION_X, arrowNS::BOSS3_OPTION_POSITION_Y);
	placeAssets();
}



void LevelSelect::placeAssets()
{
	arrow.setScale(0.1f);
	arrow.setAngle(4.71239);
	arrow.setX(arrowPositions[0]->getX());
	arrow.setY(arrowPositions[0]->getY());


}
int LevelSelect::update(Input *input)
{
	
	if (input->isKeyDown('D') && counter < 2)
	{
		counter++;
		input->clearAll();
	}
	if (input->isKeyDown('A') && counter > 0)
	{

		counter--;
		input->clearAll();



	}
	arrow.setX(arrowPositions[counter]->getX());
	arrow.setY(arrowPositions[counter]->getY());
	if (input->isKeyDown(VK_SPACE))
	{
		input->clearAll();
		return counter + 1;
	}


}

void LevelSelect::render()
{
	graphics->spriteBegin();
	levelSelectBackground.draw();
	arrow.draw();

	graphics->spriteEnd();
}

