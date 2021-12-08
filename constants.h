
#ifndef _CONSTANTS_H            // prevent multiple definitions if this 
#define _CONSTANTS_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>



//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Overtale";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1920;               // width of game in pixels
const UINT GAME_HEIGHT = 1080;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const double NINETY_DEGREE_RAD = 90 * (PI / 180);  //90 degrees in radian
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const int MAX_PROJECTILES = 100;


// graphic images
const char NEBULA_IMAGE[] = "pictures\\orion.jpg";     // placeholder for background
const char TEXTURES_IMAGE[] = "pictures\\textures.png";  // placeholder for ship
const char FLOOR_IMAGE[] = "pictures\\floor.png";
const char CRATE_IMAGE[] = "pictures\\crate.png";
const char BOSS1_IMAGE[] = "pictures\\boss1.png";
const char BOSS1Projectile_IMAGE[] = "pictures\\boss1Projectile.png";
const char MENU_BACKGROUND_IMAGE[] = "pictures\\menuBackground.png";
const char MENU_ARROW_IMAGE[] = "pictures\\menuArrow.png";


//ENVIRONMENT 
const int FLOOR_ROW_LENGTH = 31; //Must be odd numbers for true center square value
const int FLOOR_COLUMN_LENGTH = 31;
const int CRATES_NEEDED = (8 * (FLOOR_ROW_LENGTH / 2 + 1));


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR SHIP1_LEFT_KEY = 'A';
const UCHAR SHIP1_RIGHT_KEY = 'D';
const UCHAR SHIP1_UP_KEY = 'W';
const UCHAR SHIP1_DOWN_KEY = ' S';


#endif
