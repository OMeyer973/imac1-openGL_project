#include "statistics.h"

void initPlayer() {
    //initialize the player at the begining of a level
    Point2D origin = pointXY(2,level_h/2);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-1,-1,1,1);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.7,-0.6,0.7,0.6);
    float tmpShootAngles[1] = {0};
    Entity tmpEntity  = *instantiateEntity (
        origin,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        4,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEPLAYER,     //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle
        1.1,            //float speed
        0.5,            //float delay
        1,              //int shootAnglesNb
        tmpShootAngles);//float* shootAngles
    player = tmpEntity;
}

void initMobsStats() {
    //initialize the mob statistics array
    Point2D origin = pointXY(0,0);
    BoundingBox tmpSpriteBox = boundingBoxSWNE(-0.5,-0.5,0.5,0.5);
    BoundingBox tmpHitBox = boundingBoxSWNE(-0.4,-0.4,0.4,0.4);
    //MOB 0
    float tmpShootAngles0[2] = {0,0.8};
    Entity tmpEntity  = *instantiateEntity (
        origin,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        0,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEMOB,        //int type
        0,              //int subType
        30,             //int hp
        0,              //int bulletType
        0,              //float angle
        1.1,            //float speed
        0.5,            //float delay
        2,              //int shootAnglesNb
        tmpShootAngles0);//float* shootAngles
    stats_mobs[0] = tmpEntity;

    //MOB 1
    float tmpShootAngles1[3] = {0,0.5,-0.5};
    tmpEntity  = *instantiateEntity (
        origin,         //Point2D anchor
        tmpSpriteBox,   //BoundingBox spriteBox
        1,              //int textureID 
        tmpHitBox,      //BoundingBox hitBox        
        TYPEMOB,        //int type
        1,              //int subType
        50,             //int hp
        1,              //int bulletType
        0,              //float angle
        0.4,            //float speed
        0.5,            //float delay
        3,              //int shootAnglesNb
        tmpShootAngles1);//float* shootAngles
    stats_mobs[1] = tmpEntity;
}


void initBonusesStats();
void initBulletsStats();
