
#include "sceneManager.h"

//=============================================================================
// Constructor
//=============================================================================
SceneManager::SceneManager()
{
    menu = new Menu();
    overtale = new Overtale();
    text = new TextDX();     // DirectX fonts
    currentScene = Scene::menuScene; //Set starting screen to be the current scene 



}

//=============================================================================
// Destructor
//=============================================================================
SceneManager::~SceneManager()
{
    releaseAll();           // call onLostDevice() for SceneManager graphics item

}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void SceneManager::initialize(HWND hwnd)
{

    //initialize main game
    Game::initialize(hwnd); // throws GameError

    if (text->initialize(graphics, 50, true, true, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font")); //initialize text for debugging purposes 


    overtale->initialize(graphics, this); //initialize different scenes
    menu->initialize(graphics, this);
    



}

//=============================================================================
// Update all game items
//=============================================================================
void SceneManager::update()
{
    switch (currentScene)
    {
    case SceneManager::menuScene:
        switch (menu->update(input))
        {
        case 1:
            currentScene = Scene::gameScene;
            break;
        case 2:
            currentScene = Scene::optionsScene;
            break;
        case 3:
            exitGame();
            break;
        default:
            break;
        }
        break;
    case SceneManager::optionsScene:
        break;
    case SceneManager::levelSelectScene:
        break;
    case SceneManager::gameScene:
        overtale->update(frameTime);
        break;
    case SceneManager::gameWinScene:
        break;
    case SceneManager::gameLostScene:
        break;
    default:
        break;
    }
    


}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void SceneManager::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void SceneManager::collisions()
{
    switch (currentScene)
    {
    case SceneManager::menuScene:
        break;
    case SceneManager::optionsScene:
        break;
    case SceneManager::levelSelectScene:
        break;
    case SceneManager::gameScene:
        overtale->collisions();
        break;
    case SceneManager::gameWinScene:
        break;
    case SceneManager::gameLostScene:
        break;
    default:
        break;
    }
    

}

//=============================================================================
// Render game items
//=============================================================================
void SceneManager::render()
{
    switch (currentScene)
    {
    case SceneManager::menuScene:
        menu->render();
        break;
    case SceneManager::optionsScene:
        break;
    case SceneManager::levelSelectScene:
        break;
    case SceneManager::gameScene:
        overtale->render();
        break;
    case SceneManager::gameWinScene:
        break;
    case SceneManager::gameLostScene:
        break;
    default:
        break;
    }
 
    

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void SceneManager::releaseAll()
{
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void SceneManager::resetAll()
{
    Game::resetAll();
    return;
}
