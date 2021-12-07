//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Derick Lee 
//  Student Number:     S10196689
#ifndef _MENU_H             // prevent multiple definitions if this 
#define _MENU_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "image.h"


class Menu 
{

public:
    // Constructor
    Menu();

    // Destructor
    virtual ~Menu();

    // Initialize 
    bool update(Input * input, Image menuBackground);      // must override pure virtual from Game
    void render(Graphics* graphics, TextDX* dxFont, Image menuBackground);

};

#endif

