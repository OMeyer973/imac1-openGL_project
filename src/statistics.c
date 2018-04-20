#include "statistics.h"

void initPlayer() {
    //initialize the player at the begining of a level
    Point2D anchor = pointXY(2,level_h/2);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-1,-1,1,1);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.6,-0.7,0.6,0.7);
    float tmpShootAngles[3] = {0.0, M_PI/4, -M_PI/4};
    Entity tmpEntity  = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        4,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEPLAYER,     //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        400,            //float delay (in ms)
        3,              //int shootAnglesNb
        tmpShootAngles);//float* shootAngles
    player = tmpEntity;
}

void initMobsStats() {
    //initialize the mob statistics array
    Point2D anchor = pointXY(0,0);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-0.5,-0.5,0.5,0.5);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.4,-0.4,0.4,0.4);
    //MOB 0
    float tmpShootAngles0[2] = {0,0.8};
    Entity tmpEntity  = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        0,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEMOB,        //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        1000,           //float delay (in ms)
        2,              //int shootAnglesNb
        tmpShootAngles0);//float* shootAngles
    stats_mobs[0] = tmpEntity;

    //MOB 1
    float tmpShootAngles1[3] = {0,0.5,-0.5};
    tmpEntity  = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        4,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEMOB,        //int type
        1,              //int subType
        50,             //int hp
        1,              //int bulletType
        M_PI,           //float angle (radians)
        0.4,            //float speed
        0.5,            //float delay (in ms)
        3,              //int shootAnglesNb
        tmpShootAngles1);//float* shootAngles
    stats_mobs[1] = tmpEntity;
}


void initBonusesStats();

void initWallsStats() {
    //initialize the wall statistics array
    Point2D anchor = pointXY(0,0);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-0.5,-0.5,0.5,0.5);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.4,-0.4,0.4,0.4);
    //MOB 0
    float tmpShootAngles0[2] = {0,0.8};
    Entity tmpEntity  = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        5,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEMOB,        //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        1.1,            //float speed
        0.5,            //float delay (in ms)
        2,              //int shootAnglesNb
        tmpShootAngles0);//float* shootAngles
    stats_walls[0] = tmpEntity;
}

void initBulletsStats() {
    //initialize the bullets statistics array
    Point2D anchor = pointXY(0,0);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-0.2,-0.3,0.2,0.3);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.2,-0.3,0.2,0.3);
    //BULLET 0
    Entity tmpEntity  = *instantiateEntity (
        anchor,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        5,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEBULLET,     //int type
        0,              //int subType
        10,             //int hp
        0,              //int bulletType
        0,              //float angle (radians)
        2,              //float speed
        1,              //float delay (in ms)
        0,              //int shootAnglesNb
        NULL);          //float* shootAngles
    stats_bullets[0] = tmpEntity;
}

