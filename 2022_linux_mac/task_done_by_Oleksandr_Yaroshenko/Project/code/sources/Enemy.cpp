//
// Created by notnuff on 19.01.24.
//

#include "../Enemy.h"

Enemy::Enemy(dVec2D platformCoords) {

    ProjectSprites *sprites = ProjectSprites::getInstance();
    sprite = sprites->enemy;

    int iWidth, iHeight;
    FRAMEWORK_API::getSpriteSize(sprite, iWidth, iHeight);

    size = CoordinatesConverter::screenSizeToWorld(iWidth, iHeight);

    pos = platformCoords;
}

void Enemy::draw(vec2D coords) {
    FRAMEWORK_API::drawSprite(sprite, coords.x, coords.y);
}

EntType Enemy::getType() {
    return EntType::ENEMY;
}

