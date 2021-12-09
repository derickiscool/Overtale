//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Derick Lee 
//  Student Number:     S10196689
#ifndef _LEVELSELECT_H             // prevent multiple definitions if this 
#define _LEVELSELECT_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "image.h"
#include "textureManager.h"
#include "arrow.h";

class LevelSelect
{

private:
    Graphics* graphics;
    Game* gamePtr;




    int counter;
    ArrowXY* arrowPositions[3];
    TextureManager levelSelectBackgroundTexture;
    TextureManager arrowTexture;
    Image arrow;
    Image levelSelectBackground;

public:
    // Constructor
    LevelSelect();

    // Destructor
    virtual ~LevelSelect();

    // Initialize 
    void initialize(Graphics* g, Game* ptr);
    void placeAssets();
    int update(Input* input);
    void render();


};

#endif
