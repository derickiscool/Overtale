//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Derick Lee 
//  Student Number:     S10196689
#ifndef _SCENEMANAGER_H             // prevent multiple definitions if this 
#define _SCENEMANAGER_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN


#include "overtale.h"
#include "game.h"
#include "textDX.h"

//=============================================================================
// Create game class 
//=============================================================================
class SceneManager : public Game //meant for managing between scenes 
{
protected:  
    enum Scene
    {
        menu,
        options,
        levelSelect,
        gameScene,
        gameWin,
        gameLost,
    };


    Scene currentScene;
    Overtale* overtale;
    TextDX* text;

public:
    // Constructor
    SceneManager();

    // Destructor
    virtual ~SceneManager();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
   
};

#endif
