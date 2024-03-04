//
// Created by notnuff on 17.01.24.
//

#include "../Platform.h"

void Platform::draw(vec2D coords) {
    FRAMEWORK_API::drawSprite(sprite, coords.x, coords.y);
}


Platform::Platform(dVec2D position) {
    ProjectSprites *sprites = ProjectSprites::getInstance();
    sprite = sprites->platform;
    int iWidth, iHeight;
    FRAMEWORK_API::getSpriteSize(sprite, iWidth, iHeight);
    size = CoordinatesConverter::screenSizeToWorld(iWidth, iHeight);
    pos = position;
}

Platform::Platform() : Platform({0, 0.1}) {
}

EntType Platform::getType() {
    return EntType::PLATFORM;
}
