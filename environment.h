#ifndef _ENVIRONMENT_H                 // Prevent multiple definitions if this 
#define _ENVIRONMENT_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace floorEnvironmentNS
{
    const int WIDTH = 16;                   // image width
    const int HEIGHT = 16;                  // image height
    const int START_LOCATION_X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen to start rendering
    const int START_LOCATION_Y = GAME_HEIGHT / 2 - HEIGHT / 2;


}

namespace boundaryEnvironmentNS
{
    const int WIDTH = 16;   //image width 
    const int HEIGHT = 16;  //image height
    const int MIN_X = (GAME_WIDTH / 2 - floorEnvironmentNS::WIDTH) - (floorEnvironmentNS::WIDTH * (FLOOR_ROW_LENGTH/2));   //left side coordinate of boundary 
    const int MAX_X = (GAME_WIDTH /2 ) + (floorEnvironmentNS::WIDTH * (FLOOR_ROW_LENGTH/2)) ;   //right side coordinate of boundary
    const int MIN_Y = (GAME_HEIGHT /2 - floorEnvironmentNS::HEIGHT ) - (floorEnvironmentNS::HEIGHT * (FLOOR_COLUMN_LENGTH/2)) ;   //top side coordinate of boundary 
    const int MAX_Y = (GAME_HEIGHT / 2) + (floorEnvironmentNS::HEIGHT * (FLOOR_COLUMN_LENGTH/2));   //bottom side cooardinate of boundary 

}

// inherits from Entity class
class Environment : public Entity
{

protected:

public:
    // constructor
    Environment();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
        TextureManager* textureM);
};
#endif

