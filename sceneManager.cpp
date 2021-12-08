
#include "sceneManager.h"

//=============================================================================
// Constructor
//=============================================================================
SceneManager::SceneManager()
{
    overtale = new Overtale();
    text = new TextDX();     // DirectX fonts
    currentScene = Scene::menu; //Set starting screen to be the current scene 



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
    



}

//=============================================================================
// Update all game items
//=============================================================================
void SceneManager::update()
{
    switch (gameScene)
    {
    case SceneManager::menu:
        break;
    case SceneManager::options:
        break;
    case SceneManager::levelSelect:
        break;
    case SceneManager::gameScene:
        overtale->update(frameTime);
        break;
    case SceneManager::gameWin:
        break;
    case SceneManager::gameLost:
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
    switch (gameScene)
    {
    case SceneManager::menu:
        break;
    case SceneManager::options:
        break;
    case SceneManager::levelSelect:
        break;
    case SceneManager::gameScene:
        overtale->collisions();
        break;
    case SceneManager::gameWin:
        break;
    case SceneManager::gameLost:
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
    switch (gameScene)
    {
    case SceneManager::menu:
        break;
    case SceneManager::options:
        break;
    case SceneManager::levelSelect:
        break;
    case SceneManager::gameScene:
        overtale->render();
        break;
    case SceneManager::gameWin:
        break;
    case SceneManager::gameLost:
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
