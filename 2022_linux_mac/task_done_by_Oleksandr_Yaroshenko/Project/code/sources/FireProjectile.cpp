//
// Created by notnuff on 19.01.24.
//

#include "../FireProjectile.h"

FireProjectile::FireProjectile(dVec2D pCoords, dVec2D mouseCoords) {
    vel = {mouseCoords.x - pCoords.x, mouseCoords.y - pCoords.y};
    ProjectSprites *sprites = ProjectSprites::getInstance();
    sprite = sprites->shot;

    int iWidth, iHeight;
    FRAMEWORK_API::getSpriteSize(sprite, iWidth, iHeight);

    size = CoordinatesConverter::screenSizeToWorld(iWidth, iHeight);

    vel.normalize();
    vel = {vel.x * speed, vel.y * speed};

    pos = pCoords;
}

void FireProjectile::draw(vec2D coords) {
    FRAMEWORK_API::drawSprite(sprite, coords.x, coords.y);
}


EntType FireProjectile::getType() {
    return EntType::SHOT;
}
