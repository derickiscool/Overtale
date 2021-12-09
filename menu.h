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
#include "textureManager.h"


class ArrowXY
{
private:
    int xVal;
    int yVal;
public:

    ArrowXY();
    ArrowXY(int x, int y);

    int getX() { return xVal; };
    int getY() { return yVal; };

};


namespace arrowNS {
    const int PLAY_OPTION_POSITON_X = 700;
    const int PLAY_OPTION_POSITON_Y = 500;
    const int OPTIONS_OPTION_POSITON_X = 600;
    const int OPTIONS_OPTION_POSITON_Y = 625;
    const int QUIT_OPTION_POSITON_X = 700;
    const int QUIT_OPTION_POSITON_Y = 765;


    
}

class Menu
{

private:
    Graphics* graphics;
    Game* gamePtr;


   

    int counter;
    ArrowXY *arrowPositions[3];
    TextureManager menuBackgroundTexture;
    TextureManager arrowTexture;
    Image arrow;
    Image menuBackground;
    TextDX *menuText;

public:
    // Constructor
    Menu();

    // Destructor
    virtual ~Menu();

    // Initialize 
    void initialize(Graphics * g, Game* ptr);
    void placeAssets();
    int update(Input *input);      
    void render();


};

#endif
