#include "menu.h";




Menu::Menu()
{
	menuText = new TextDX();
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

	if (!menuText->initialize(g, 15,0,0,"Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing arrow image texture"));

	placeAssets();

}


void Menu::placeAssets()
{


}

int Menu::update()
{
	return 0;
}
void Menu::render()
{
	graphics->spriteBegin();
	menuBackground.draw();
	
	graphics->spriteEnd();
}