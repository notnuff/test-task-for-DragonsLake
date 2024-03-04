//
// Created by notnuff on 19.01.24.
//

#include "../ProjectSprites.h"


ProjectSprites *ProjectSprites::instance = nullptr;

ProjectSprites::ProjectSprites() {
    initPlayer();

    initEnemy();

    initShot();

    initPlatform();

    initBackground();

    initDissapearPlatform();

    initShield();

    initPropeller();

    initScore();

    initNumbers();

    initHeart();
}

void ProjectSprites::initShot() {
    shot = FRAMEWORK_API::createSprite("../data/bullet.png");
    int shotHeight, shotWidth;
    FRAMEWORK_API::getSpriteSize(shot, shotWidth, shotHeight);
    FRAMEWORK_API::setSpriteSize(shot, shotWidth / 2, shotHeight / 2);
}



void ProjectSprites::initBackground() {
    background = FRAMEWORK_API::createSprite("../data/bck@2x.png");
}

void ProjectSprites::initDissapearPlatform() {
    dissPlatform = FRAMEWORK_API::createSprite("../data/dissappear-platform.png");
    int shotHeight, shotWidth;
    FRAMEWORK_API::getSpriteSize(dissPlatform, shotWidth, shotHeight);
    FRAMEWORK_API::setSpriteSize(dissPlatform, shotWidth / 2, shotHeight / 2);
}

void ProjectSprites::initShield() {
    shield = FRAMEWORK_API::createSprite("../data/my-shield.png");
    int shotHeight, shotWidth;
    FRAMEWORK_API::getSpriteSize(shield, shotWidth, shotHeight);
    FRAMEWORK_API::setSpriteSize(shield, shotWidth / 2, shotHeight / 2);
}

void ProjectSprites::initPropeller() {
    propeller = FRAMEWORK_API::createSprite("../data/my-propeller.png");
    int shotHeight, shotWidth;
    FRAMEWORK_API::getSpriteSize(propeller, shotWidth, shotHeight);
    FRAMEWORK_API::setSpriteSize(propeller, shotWidth / 2, shotHeight / 2);
}

void ProjectSprites::initScore() {
    score = FRAMEWORK_API::createSprite("../data/score.png");
}

void ProjectSprites::initNumbers() {
    const char* paths[10] = {
            "../data/0.png",
            "../data/1.png",
            "../data/2.png",
            "../data/3.png",
            "../data/4.png",
            "../data/5.png",
            "../data/6.png",
            "../data/7.png",
            "../data/8.png",
            "../data/9.png"
    };

    for (int i = 0; i < 10; ++i) {
        numbers[i] = FRAMEWORK_API::createSprite(paths[i]);
    }

    for (auto num : numbers) {
        int iW, iH;
        FRAMEWORK_API::getSpriteSize(num, iW, iH);
        FRAMEWORK_API::setSpriteSize(num, iW / 2, iH / 2);
    }
}

void ProjectSprites::initPlayer() {
    player = {
            FRAMEWORK_API::createSprite("../data/blue-lik-left.png"),
            FRAMEWORK_API::createSprite("../data/blue-lik-right.png"),
            FRAMEWORK_API::createSprite("../data/blue-lik-left-odskok.png"),
            FRAMEWORK_API::createSprite("../data/blue-lik-right-odskok.png")
    };
}

void ProjectSprites::initEnemy() {
    enemy = FRAMEWORK_API::createSprite("../data/enemy.png");
    int enemHeight, enemWidth;
    FRAMEWORK_API::getSpriteSize(enemy, enemWidth, enemHeight);
    FRAMEWORK_API::setSpriteSize(enemy, enemWidth / 3, enemHeight / 3);
}

void ProjectSprites::initPlatform() {
    platform = FRAMEWORK_API::createSprite("../data/platform-custom.png");
}

ProjectSprites *ProjectSprites::getInstance() {
    if(instance==nullptr){
        instance = new ProjectSprites();
    }
    return instance;
}

void ProjectSprites::initHeart() {
    heart = FRAMEWORK_API::createSprite("../data/heart.png");
    int Height, Width;
    FRAMEWORK_API::getSpriteSize(heart, Width, Height);
    FRAMEWORK_API::setSpriteSize(heart, Width / 8, Height / 8);
}



