#include "statistics.h"

// ------------ LEVELS ------------ //

void initLevelsColors() {
    //initialyse the list of the levels bg colors
    levelColors[0] = colorRGBA(0.3,0.4,0.6,1);
    levelColors[1] = colorRGBA(0.5,0.7,1,1);
    levelColors[2] = colorRGBA(0.5,1,0.7,1);    
}

// ------------ PLAYER ------------ //

void initPlayerStats() {
    //initialize the player at the begining of a level
    Point2D anchor = pointXY(0,0);
    float tmpShootAngles[MAXSHOOTANGLES] = {0.0, M_PI/4, -M_PI/4};
    stats_player = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-1,1,1),   //BoundingBox spriteBox
        00,              //int textureID 
        boundingBoxSWNE(-0.6,-0.7,0.6,0.7),      //BoundingBox hitBox        
        TYPEPLAYER,     //int type
        0,              //int subType
        150,           //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        400,            //float shootDelay (in ms)
        450,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        1,              //int shootAnglesNb
        tmpShootAngles, //float* shootAngles
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );
}


// ------------ MOBS ------------ //

void initMobsStats() {
    //initialize the mob statistics array
    Point2D anchor = pointXY(0,0);
     

    //MOB 0 (LANTERN FISH)
    int tmpbehaviors0[MAXBEHAVIORS] = {AIMPLAYER,GOFWD, SINALPHA};
    stats_mobs[0] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.6,-0.7,0.6,0.7),   //BoundingBox spriteBox
        20,              //int textureID 
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),      //BoundingBox hitBox        
        TYPEMOB,        //int type
        1,              //int subType
        30,             //int hp
        1,              //int bulletType
        M_PI,           //float angle (radians)
        0.4,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles
        3,              //int behaviorsNb
        tmpbehaviors0   //int* behaviors
    );

    //MOB 1 - SHARK
    int tmpbehaviors1[MAXBEHAVIORS] = {YSINE,GOFWD};
    stats_mobs[1] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.8,-0.8,0.8,0.8),   //BoundingBox spriteBox
        21,              //int textureID 
        boundingBoxSWNE(-0.5,-0.7,0.4,0.6),      //BoundingBox hitBox        
        TYPEMOB,        //int type
        0,              //int subType
        30,             //int hp
        1,              //int bulletType
        M_PI,              //float angle (radians)
        0.2,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        2000,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,            //float* shootAngles
        3,              //int behaviorsNb
        tmpbehaviors1   //int* behaviors
    );

    //MOB 2 (SUBMARINE)
    float tmpShootAngles2[MAXSHOOTANGLES] = {0, 0.5, -0.8, 0.5, 0.8};
    
    int tmpbehaviors2[MAXBEHAVIORS] = {AIMPLAYER,YSINE};
    stats_mobs[2] =  *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1.2,-1.2,1.2,1.2),   //BoundingBox spriteBox
        22,              //int textureID 
        boundingBoxSWNE(-0.8,-0.8,0.8,0.8),      //BoundingBox hitBox        
        TYPEMOB,       //int type
        2,              //int subType
        70,             //int hp
        2,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1800,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        5,              //int shootAnglesNb
        tmpShootAngles2,//float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors2  //int* behaviors
    );

        //MOB 3 (SHOOTING CORAL)
    float tmpShootAngles3[MAXSHOOTANGLES] = {0, -0.2, 0.2};
    stats_mobs[3]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),   //BoundingBox spriteBox
        23,              //int textureID 
        boundingBoxSWNE(-0.4,-0.4,0.4,0.4),      //BoundingBox hitBox        
        TYPEMOB,        //int type
        3,              //int subType
        50,             //int hp
        1,              //int bulletType
        M_PI/2,         //float angle (radians)
        0.4,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        3,              //int shootAnglesNb
        tmpShootAngles3,//float* shootAngles
        0,              //int behaviorsNb
        NULL           //int* behaviors
    );
    
    //MOB 4 - SPONGE FISH
    int tmpbehaviors4[MAXBEHAVIORS] = {ROTATE,GOFWD, SINSCALE};    
    float tmpShootAngles4[MAXSHOOTANGLES] = {0, 1, 2, 3, 4, 5};
    stats_mobs[4] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.7,-0.8,0.7,0.8),   //BoundingBox spriteBox
        24,              //int textureID 
        boundingBoxSWNE(-0.6,-0.6,0.6,0.6),      //BoundingBox hitBox        
        TYPEMOB,        //int type
        1,              //int subType
        50,             //int hp
        3,              //int bulletType
        M_PI,           //float angle (radians)
        0.4,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        5000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        7,              //int shootAnglesNb
        tmpShootAngles4,//float* shootAngles
        4,              //int behaviorsNb
        tmpbehaviors4   //int* behaviors
    );

}

// ------------ WALLS ------------ // 

void initWallsStats() {
    //initialize the wall statistics array
    Point2D anchor = pointXY(0,0);
    //WALL 0 - ALGAE
    int tmpbehaviors0[MAXBEHAVIORS] = {SINSCALE};
        stats_walls[0]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.8,-1,1.8,1),   //BoundingBox spriteBox
        40,              //int textureID 
        boundingBoxSWNE(-0.7,-0.4,0.7,0.7),      //BoundingBox hitBox        
        TYPEWALL,       //int type
        0,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        4000,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,//float* shootAngles -> walls need this (else, segfault but why ????)
        1,              //int behaviorsNb
        tmpbehaviors0   //int* behaviors
    );


    //WALL 1 - HIGH ROCK WALL
    stats_walls[1] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.7,-0.6,0.7,0.6),   //BoundingBox spriteBox
        41,              //int textureID 
        boundingBoxSWNE(-0.6,-0.5,0.6,0.5),      //BoundingBox hitBox        
        TYPEWALL,        //int type
        1,              //int subType
        5,              //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );

//WALL 2 - WIDE ROCK WALL
    stats_walls[2] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.6,-0.9,0.6,0.9),   //BoundingBox spriteBox
        42,              //int textureID 
        boundingBoxSWNE(-0.5,-0.8,0.5,0.8),      //BoundingBox hitBox        
        TYPEWALL,        //int type
        2,              //int subType
        5,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );

//WALL 3 - ROCK PANEL
    stats_walls[3] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.8,-0.7,0.8,0.7),   //BoundingBox spriteBox
        43,              //int textureID 
        boundingBoxSWNE(-0.6,-0.5,0.6,0.5),      //BoundingBox hitBox        
        TYPEWALL,        //int type
        3,              //int subType
        5,              //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );

//WALL 4 - ROCK STUMP
    stats_walls[4] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.7,-0.7,0.7,0.7),   //BoundingBox spriteBox
        44,              //int textureID 
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),      //BoundingBox hitBox        
        TYPEWALL,        //int type
        4,              //int subType
        5,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );

//WALL 5 - ROCK CIELING
    stats_walls[5] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-4,1,4),   //BoundingBox spriteBox
        45,              //int textureID 
        boundingBoxSWNE(-0.8,-3.8,0.8,3.8),      //BoundingBox hitBox        
        TYPEWALL,        //int type
        5,              //int subType
        5,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );

//WALL 6 - ROCK FLOOR
    stats_walls[6] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-4,1,4),   //BoundingBox spriteBox
        45,              //int textureID 
        boundingBoxSWNE(-0.8,-3.8,0.8,3.8),      //BoundingBox hitBox        
        TYPEWALL,        //int type
        6,              //int subType
        5,             //int hp
        0,              //int bulletType
        M_PI,           //float angle (radians)
        1.1,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );

}


// ------------ BONUSES ------------ //

void initBonusesStats() {
    //initialize the bullets statistics array
    Point2D anchor = pointXY(0,0);

    //Bonus 0 : CHEST POINTS
    int tmpbehaviors0[MAXBEHAVIORS] = {SINALPHA};
    stats_bonuses[0]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-1,1,1),   //BoundingBox spriteBox
        50,              //int textureID 
        boundingBoxSWNE(-0.6,-0.7,0.6,0.7),      //BoundingBox hitBox        
        TYPEBONUS,      //int type
        0,              //int subType
        200,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.7,            //float speed
        colorRGBA(1,1,1,1),//Color4f color
        150,            //float shootDelay (in ms)
        450,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors0   //int* behaviors
    );

    //Bonus 1 : HP BONUS
    int tmpbehaviors1[MAXBEHAVIORS] = {SINALPHA};
    stats_bonuses[1]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-1,1,1),   //BoundingBox spriteBox
        01,              //int textureID 
        boundingBoxSWNE(-0.6,-0.7,0.6,0.7),      //BoundingBox hitBox        
        TYPEBONUS,      //int type
        1,              //int subType
        100,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(0.8,1,0.9,1),   //Color4f color
        300,            //float shootDelay (in ms)
        450,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors1   //int* behaviors
    );

    //Bonus 2 : SIZE CHANGE !
    int tmpbehaviors2[MAXBEHAVIORS] = {SINALPHA, SINSCALE};
    stats_bonuses[2]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-1,1,1),   //BoundingBox spriteBox
        52,              //int textureID 
        boundingBoxSWNE(-0.6,-0.7,0.6,0.7),      //BoundingBox hitBox        
        TYPEBONUS,      //int type
        2,              //int subType
        0,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        colorRGBA(0.8,1,0.9,1),   //Color4f color
        300,            //float shootDelay (in ms)
        450,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors2 //int* behaviors
    );

    //Bonus 3 : BIG BOMBS
    int tmpbehaviors3[MAXBEHAVIORS] = {SINALPHA, YSINE};
    float tmpShootAngles3[MAXSHOOTANGLES] = {0};
    stats_bonuses[3]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-1,1,1),   //BoundingBox spriteBox
        53,              //int textureID 
        boundingBoxSWNE(-0.6,-0.7,0.6,0.7),      //BoundingBox hitBox        
        TYPEBONUS,      //int type
        3,              //int subType
        0,              //int hp
        4,              //int bulletType
        0,              //float angle (radians)
        0.9,            //float speed
        colorRGBA(0.8,1,0.9,1),   //Color4f color
        600,            //float shootDelay (in ms)
        450,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        1,              //int shootAnglesNb
        tmpShootAngles3,//float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors3 //int* behaviors
    );

    //Bonus 4 : SHOTGUN
    int tmpbehaviors4[MAXBEHAVIORS] = {SINALPHA, XSINE};
    float tmpShootAngles4[MAXSHOOTANGLES] = {0.1,0.5,-0.1,-0.5};
    stats_bonuses[4]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-1,1,1),   //BoundingBox spriteBox
        54,              //int textureID 
        boundingBoxSWNE(-0.6,-0.7,0.6,0.7),      //BoundingBox hitBox        
        TYPEBONUS,      //int type
        4,              //int subType
        0,              //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.9,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        200,            //float shootDelay (in ms)
        450,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        4,              //int shootAnglesNb
        tmpShootAngles4,//float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors4   //int* behaviors
    );
}


// ------------ BULLETS ------------ //

void initBulletsStats() {
    //initialize the bullets statistics array
    Point2D anchor = pointXY(0,0);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-0.2,-0.3,0.2,0.3);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.2,-0.3,0.2,0.3);
    int tmpbehaviors[MAXBEHAVIORS] = {5};
    //BULLET 0 - (BUBBLES FOR PLAYER )
    stats_bullets[0]   = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        30,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        0,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        5,              //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );

    //BULLET 1 - (BUBBLES FOR SOME MOBS)
    stats_bullets[1] = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        30,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        1,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.7,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );

    //BULLET  2 - (BOMBS FOR SUBMARINE)
    stats_bullets[2] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.6,0.5,0.6),   //BoundingBox spriteBox
        31,              //int textureID 
        boundingBoxSWNE(-0.3,-0.4,0.3,0.4),      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        2,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.7,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );

    //BULLET 3 - (SPIKES FOR SPONGE FISH MOBS)
    stats_bullets[3] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.2,-0.2,0.2,0.2),   //BoundingBox spriteBox
        32,              //int textureID 
        boundingBoxSWNE(-0.12,-0.12,0.12,0.12),      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        3,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.7,            //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );


    //BULLET  4 - (BOMBS FOR PLAYER)
    stats_bullets[4] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.7,-0.8,0.6,0.8),   //BoundingBox spriteBox
        31,              //int textureID 
        boundingBoxSWNE(-0.5,-0.6,0.5,0.6),      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        2,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        3,            //float speed
        colorRGBA(0.5,1,0.5,1),   //Color4f color
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1500,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );

}


// ------------ VFX ------------ //

void initVFXsStats() {
    //initialize the bullets statistics array
    Point2D anchor = pointXY(0,0);
    int tmpbehaviors[MAXBEHAVIORS] = {GROW, DISAPEAR};
    //VFX 0 - (BULLET HIT)
    
    stats_VFXs[0]   = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),   //BoundingBox spriteBox
        70,              //int textureID 
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),      //BoundingBox hitBox        
        6,     //int type
        0,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        5,              //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1,              //float shootDelay (in ms)
        800,            //float invDelay (in ms)
        800,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );

    //VFX 1 - (MOB KILLED)
    stats_VFXs[1] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),   //BoundingBox spriteBox
        71,              //int textureID 
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),      //BoundingBox hitBox        
        6,     //int type
        0,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        5,              //float speed
        colorRGBA(1,1,1,1),   //Color4f color
        1,              //float shootDelay (in ms)
        800,            //float invDelay (in ms)
        800,            //float animDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );
}