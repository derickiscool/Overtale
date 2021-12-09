//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Derick Lee 
//  Student Number:     S10196689
#ifndef _GAMEOVER_H             // prevent multiple definitions if this 
#define _GAMEOVER_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "image.h"
#include "textureManager.h"
#include "arrow.h"


class GameOver
{

private:
    Graphics* graphics;
    Game* gamePtr;
    
    bool gameOutcome;  //true if win, false if lost 
    int counter;
    ArrowXY* arrowPositions[4];
    TextureManager gameWonTexture;
    TextureManager gameLostTexture;
    TextureManager arrowTexture;
    Image arrow;
    Image gameWonBackground;
    Image gameLostBackground;
    TextDX* menuText;

public:
    // Constructor
    GameOver();

    // Destructor
    virtual ~GameOver();

    // Initialize 
    void initialize(Graphics* g, Game* ptr);
    void placeAssets();
    int update(Input* input);
    void render();

    void setGameOutcome(bool b) { gameOutcome = b; };


};

#endif
