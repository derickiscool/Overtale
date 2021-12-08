//  Module:             Gameplay Programming
//  Assignment1:        Overtale
//  Student Name:       Derick Lee 
//  Student Number:     S10196689
#ifndef _OVERTALE_H             // prevent multiple definitions if this 
#define _OVERTALE_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "player.h"
#include "environment.h"
#include "boss1.h"
#include "projectile.h"
#include "textDX.h"
//=============================================================================
// Create game class
//=============================================================================
class Overtale : public Game
{
private:

    enum BossType
    {
        bossType1,
        bossType2,
        bossType3
    };
    BossType bossType;

    //text variables
    TextDX* dxFontSmall;       // DirectX fonts


    // variables
    TextureManager gameTextures;    // game texture
    TextureManager floorTexture;    //floor texture
    TextureManager crateTexture;    //crate texture
    TextureManager boss1Texture;    //boss1 texture 
    TextureManager boss1ProjectileTexture; //projectile texture for boss1
    Player    ship1;          // spaceship
    Environment floorEnvironment; //floor tile environment placeholder
    Environment fullFloorRow[FLOOR_ROW_LENGTH];  //Creating Singular Row
    Environment fullFloor[FLOOR_ROW_LENGTH*FLOOR_COLUMN_LENGTH]; //Creating whole floor
    Environment crateEnvironment; //Crate environment placeholder
    Environment fullCrateEnvironment[CRATES_NEEDED]; //Create array of crate environment;
    Projectile projectiles[MAX_PROJECTILES];
    

   

    //Boss 1
    Projectile boss1Projectile;
    Boss1 boss1;
    

    
    

public:
    // Constructor
    Overtale();

    // Destructor
    virtual ~Overtale();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
    void generateFloor(); //used to generate the floor of the game
    void generateBoundary(); //generating the boundaries of the box
    void boss1Setup();     //setup first boss
};

#endif
