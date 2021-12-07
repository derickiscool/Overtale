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


class LevelSelect
{

public:
    // Constructor
    LevelSelect();

    // Destructor
    virtual ~LevelSelect();

    // Initialize 
    int update(Input* input);      // must override pure virtual from Game
    void render(Graphics* graphics, TextDX* dxFont, Image levelSelectBackground);

};

#endif

