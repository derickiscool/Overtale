#ifndef _ARROW_H             // prevent multiple definitions if this 
#define _ARROW_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN







namespace arrowNS {
    const int PLAY_OPTION_POSITON_X = 700;
    const int PLAY_OPTION_POSITON_Y = 500;
    const int OPTIONS_OPTION_POSITON_X = 600;
    const int OPTIONS_OPTION_POSITON_Y = 625;
    const int QUIT_OPTION_POSITON_X = 700;
    const int QUIT_OPTION_POSITON_Y = 765;
    const int BOSS1_OPTION_POSITION_X = 270;
    const int BOSS1_OPTION_POSITION_Y = 900;
    const int BOSS2_OPTION_POSITION_X = 925;
    const int BOSS2_OPTION_POSITION_Y = 900;
    const int BOSS3_OPTION_POSITION_X = 1575;
    const int BOSS3_OPTION_POSITION_Y = 900;
    const int GAME_OVER_RETRY_OPTION_POSITION_X = 700;
    const int GAME_OVER_RETRY_OPTION_POSITION_Y = 420;
    const int GAME_OVER_LEVEL_SELECT_OPTION_POSITION_X = 540;
    const int GAME_OVER_LEVEL_SELECT_OPTION_POSITION_Y = 575;
    const int GAME_OVER_MAIN_MENU_OPTION_POSITION_X = 580;
    const int GAME_OVER_MAIN_MENU_OPTION_POSITION_Y = 720;
    const int GAME_OVER_QUIT_OPTION_POSITION_X = 700;
    const int GAME_OVER_QUIT_OPTION_POSITION_Y = 880;



    
}

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
#endif