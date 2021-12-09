#include "menu.h";


Menu::Menu()
{
	menuText = new TextDX();
	counter = 0;
}
Menu::~Menu()
{
	
}

void Menu::initialize(Graphics *g, Game* ptr)
{


	graphics = g;
	gamePtr = ptr;

	//Background texture
	if (!menuBackgroundTexture.initialize(g, MENU_BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu background texture"));

	//arrow texture
	if (!arrowTexture.initialize(g,MENU_ARROW_IMAGE ))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu arrow texture"));

	if (!menuBackground.initialize(g,0,0,0,&menuBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu image texture"));

	if (!arrow.initialize(g, 0, 0, 0, &arrowTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing arrow image texture"));

	if (!menuText->initialize(g, 100,0,0,"Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing arrow image texture"));
	


	//initialize ArrowPositions
	arrowPositions[0] = new ArrowXY(arrowNS::PLAY_OPTION_POSITON_X, arrowNS::PLAY_OPTION_POSITON_Y);
	arrowPositions[1] = new ArrowXY(arrowNS::OPTIONS_OPTION_POSITON_X, arrowNS::OPTIONS_OPTION_POSITON_Y);
	arrowPositions[2] = new ArrowXY(arrowNS::QUIT_OPTION_POSITON_X, arrowNS::QUIT_OPTION_POSITON_Y);
	placeAssets();
}


void Menu::placeAssets()
{
	
	arrow.setScale(0.1f);
	arrow.setX(arrowPositions[0]->getX());
	arrow.setY(arrowPositions[0]->getY());


}

int Menu::update(Input *input)
{
	
	if (input->isKeyDown('S') && counter <2)
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
		return counter+1;
	}
	
}
void Menu::render()
{
	graphics->spriteBegin();
	menuBackground.draw();
	arrow.draw();
	graphics->spriteEnd();
}