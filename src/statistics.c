#include "statistics.h"

void initPlayerStats() {
    //initialize the player at the begining of a level
    Point2D anchor = pointXY(0,0);
    float tmpShootAngles[16] = {0.0, M_PI/4, -M_PI/4};
    stats_player = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-1,1,1),   //BoundingBox spriteBox
        00,              //int textureID 
         boundingBoxSWNE(-0.6,-0.7,0.6,0.7),      //BoundingBox hitBox        
        TYPEPLAYER,     //int type
        0,              //int subType
        1000,            //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        400,            //float shootDelay (in ms)
        450,            //float invDelay (in ms)
        1,              //int shootAnglesNb
        tmpShootAngles, //float* shootAngles
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );
}

void initMobsStats() {
    //initialize the mob statistics array
    Point2D anchor = pointXY(0,0);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-0.5,-0.5,0.5,0.5);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.4,-0.4,0.4,0.4);
    //MOB 0 - SHARK

    float tmpShootAngles0[16] = {0};
    stats_mobs[0] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-1,-1,1,1),   //BoundingBox spriteBox
        21,              //int textureID 
        boundingBoxSWNE(-0.9,-0.9,0.9,0.9),      //BoundingBox hitBox        
        TYPEMOB,        //int type
        0,              //int subType
        30,             //int hp
        1,              //int bulletType
        M_PI,              //float angle (radians)
        1.1,            //float speed
        1000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        1,              //int shootAnglesNb
        tmpShootAngles0, //float* shootAngles
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );

    //MOB 1 - SPONGE FISH
    int tmpbehaviors1[2] = {4,5};    
    float tmpShootAngles1[16] = {0, 1, 2, 3, 4, 5};
    stats_mobs[1] = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        24,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEMOB,        //int type
        1,              //int subType
        50,             //int hp
        3,              //int bulletType
        M_PI,           //float angle (radians)
        0.4,            //float speed
        7000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        7,              //int shootAnglesNb
        tmpShootAngles1,//float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors1   //int* behaviors
    );

    //MOB 2 (BOSS)
    float tmpShootAngles2[16] = {0, 0.5, -0.8, 0.5, 0.8};
    
    int tmpbehaviors2[2] = {3,0};
        stats_mobs[2] =  *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-10,-10,10,10),   //BoundingBox spriteBox
        22,              //int textureID 
        boundingBoxSWNE(-10,-10,10,10),      //BoundingBox hitBox        
        TYPEMOB,       //int type
        2,              //int subType
        500,             //int hp
        2,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        1000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        5,              //int shootAnglesNb
        tmpShootAngles2,//float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors2  //int* behaviors
    );

        //MOB 3 (MURAL FISH)
    stats_mobs[3]  = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        23,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEMOB,        //int type
        3,              //int subType
        50,             //int hp
        0,              //int bulletType
        M_PI/2,         //float angle (radians)
        0.4,            //float speed
        1000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors1   //int* behaviors
    );

    //MOB 4 (LANTERN FISH)
    int tmpbehaviors4[2] = {3,5};
    stats_mobs[4] = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        20,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEMOB,        //int type
        1,              //int subType
        50,             //int hp
        1,              //int bulletType
        M_PI,           //float angle (radians)
        0.4,            //float speed
        1000,           //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles
        2,              //int behaviorsNb
        tmpbehaviors4   //int* behaviors
    );
}


void initBonusesStats() {
    //initialize the bullets statistics array
    Point2D anchor = pointXY(0,0);
    float tmpShootAngles0[16] = {-0.8,0,0.8};
    //Bonus 0
    stats_bonuses[0]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),   //BoundingBox spriteBox
        50,              //int textureID 
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),      //BoundingBox hitBox        
        TYPEBONUS,      //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.7,            //float speed
        150,            //float shootDelay (in ms)
        450,            //float invDelay (in ms)
        3,              //int shootAnglesNb
        tmpShootAngles0,//float* shootAngles
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );
}

void initWallsStats() {
    //initialize the wall statistics array
    Point2D anchor = pointXY(0,0);
    //WALL 0 - GRASS
        stats_walls[0]  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),   //BoundingBox spriteBox
        41,              //int textureID 
        boundingBoxSWNE(-0.4,-0.4,0.4,0.4),      //BoundingBox hitBox        
        TYPEWALL,       //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL,//float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );


    //WALL 1 - ROCK UP
    stats_walls[1] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),   //BoundingBox spriteBox
        42,              //int textureID 
        boundingBoxSWNE(-0.4,-0.4,0.4,0.4),      //BoundingBox hitBox        
        TYPEWALL,        //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );

     //WALL 2 - ROCK DOWN
    stats_walls[2] = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.5,0.5,0.5),   //BoundingBox spriteBox
        43,              //int textureID 
        boundingBoxSWNE(-0.4,-0.4,0.4,-0.4),      //BoundingBox hitBox        
        TYPEWALL,        //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        -M_PI,        //float angle (radians)
        1.1,            //float speed
        0.5,            //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL,           //float* shootAngles -> walls need this (else, segfault but why ????)
        0,              //int behaviorsNb
        NULL            //int* behaviors
    );
}

void initBulletsStats() {
    //initialize the bullets statistics array
    Point2D anchor = pointXY(0,0);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-0.2,-0.3,0.2,0.3);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.2,-0.3,0.2,0.3);
    int tmpbehaviors[1] = {5};
    //BULLET 0 - (BUBBLES FOR PLAYER )
    Entity tmpEntity  = *instantiateEntity (
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
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );
    stats_bullets[0] = tmpEntity;

    //BULLET 1 - (BUBBLES FOR SOME MOBS)
    Entity tmpEntity2  = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        30,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        0,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.7,            //float speed
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );
    stats_bullets[1]=tmpEntity2;
    //BULLET  2 - (BULLETS FOR BOSS)
    Entity tmpEntity3  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.5,-0.6,0.5,0.6),   //BoundingBox spriteBox
        31,              //int textureID 
        boundingBoxSWNE(-0.5,-0.6,0.5,0.6),      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        0,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.7,            //float speed
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );
    stats_bullets[2]=tmpEntity3;


    //BULLET 3 - (PIKES FOR SPONGE FISH MOBS)
 Entity tmpEntity4  = *instantiateEntity (
        anchor,         //Point2D anchor
        boundingBoxSWNE(-0.2,-0.2,0.2,0.2),   //BoundingBox spriteBox
        32,              //int textureID 
        boundingBoxSWNE(-0.12,-0.12,0.12,0.12),      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        0,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        0.7,            //float speed
        1,              //float shootDelay (in ms)
        100,            //float invDelay (in ms)
        0,              //int shootAnglesNb
        NULL, //float* shootAngles
        1,              //int behaviorsNb
        tmpbehaviors    //int* behaviors
    );
    stats_bullets[3]=tmpEntity4;

}
