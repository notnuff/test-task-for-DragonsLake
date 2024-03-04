//
// Created by notnuff on 19.01.24.
//

#ifndef GAMEPROJECT_PROJECTSPRITES_H
#define GAMEPROJECT_PROJECTSPRITES_H

#include "Framework.h"
#include <vector>
#include <string>
#include <iostream>

struct playerSprites {
    Sprite *spriteL;
    Sprite *spriteR;
    Sprite *spriteJumpL;
    Sprite *spriteJumpR;
};

class ProjectSprites {

    ProjectSprites();
    static ProjectSprites* instance;

    void initPlayer();

    void initEnemy();

    void initShot();

    void initPlatform();

    void initBackground();

    void initDissapearPlatform();

    void initShield();

    void initPropeller();

    void initScore();

    void initHeart();

    void initNumbers();

public:

    Sprite *numbers[10];
    Sprite *platform;
    Sprite *enemy;
    Sprite *shot;
    Sprite *background;
    Sprite *shield;
    Sprite *propeller;
    Sprite *score;
    Sprite *dissPlatform;
    Sprite *heart;
    playerSprites player;

    ProjectSprites(ProjectSprites &other) = delete;

    void operator=(const ProjectSprites &) = delete;

    static ProjectSprites* getInstance();

};



#endif //GAMEPROJECT_PROJECTSPRITES_H
