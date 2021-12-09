#include "gameOver.h"




GameOver::GameOver()
{
	
	counter = 0;
	gameOutcome = true;
}
GameOver::~GameOver()
{

}

void GameOver::initialize(Graphics* g, Game* ptr)
{


	graphics = g;
	gamePtr = ptr;

	//Background texture
	if (!gameLostTexture.initialize(g, GAME_LOST_BACKGROUND))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game lost texture"));
	if (!gameWonTexture.initialize(g, GAME_LOST_BACKGROUND))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game won texture"));

	//arrow texture
	if (!arrowTexture.initialize(g, MENU_ARROW_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing GameOver arrow texture"));

	if (!gameWonBackground.initialize(g, 0, 0, 0, &gameWonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game won image texture"));

	if (!gameLostBackground.initialize(g, 0, 0, 0, &gameLostTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game lost image texture"));

	if (!arrow.initialize(g, 0, 0, 0, &arrowTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing arrow image texture"));





	//initialize ArrowPositions
	arrowPositions[0] = new ArrowXY(arrowNS::GAME_OVER_RETRY_OPTION_POSITION_X, arrowNS::GAME_OVER_RETRY_OPTION_POSITION_Y);
	arrowPositions[1] = new ArrowXY(arrowNS::GAME_OVER_LEVEL_SELECT_OPTION_POSITION_X, arrowNS::GAME_OVER_LEVEL_SELECT_OPTION_POSITION_Y);
	arrowPositions[2] = new ArrowXY(arrowNS::GAME_OVER_MAIN_MENU_OPTION_POSITION_X, arrowNS::GAME_OVER_MAIN_MENU_OPTION_POSITION_Y);
	arrowPositions[3] = new ArrowXY(arrowNS::GAME_OVER_QUIT_OPTION_POSITION_X, arrowNS::GAME_OVER_QUIT_OPTION_POSITION_Y);
	placeAssets();
}


void GameOver::placeAssets()
{

	arrow.setScale(0.1f);
	arrow.setX(arrowPositions[0]->getX());
	arrow.setY(arrowPositions[0]->getY());



}

int GameOver::update(Input* input)
{

	if (input->isKeyDown('S') && counter < 3)
	{
		counter++;
		input->clearAll();
	}
	if (input->isKeyDown('W') && counter > 0)
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
void GameOver::render()
{
	graphics->spriteBegin();
	switch (gameOutcome)
	{
	case 0:
		gameLostBackground.draw();
	case 1:
		gameWonBackground.draw();
	default:
		break;
	}
	arrow.draw();
	graphics->spriteEnd();
}