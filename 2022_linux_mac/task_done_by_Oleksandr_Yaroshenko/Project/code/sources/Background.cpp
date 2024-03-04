//
// Created by notnuff on 20.01.24.
//

#include "../Background.h"
#include "../ProjectSprites.h"

Background::Background(dVec2D position) {

    ProjectSprites *sprites = ProjectSprites::getInstance();
    sprite = sprites->background;

    int sW, sH, bW, bH;
    FRAMEWORK_API::getSpriteSize(sprite, bW, bH);
    FRAMEWORK_API::getScreenSize(sW, sH);
    double backCoeff = (double) sW / bW;
    bH = bH * backCoeff;
    bW = sW;
    FRAMEWORK_API::setSpriteSize(sprite, bW, bH);

    size = CoordinatesConverter::screenSizeToWorld(sW, bH);
    pos = position;
}

Background::Background() : Background({-1, 0}) {

}

void Background::draw(vec2D coords) {
    FRAMEWORK_API::drawSprite(sprite, coords.x, coords.y);
}

EntType Background::getType() {
    return EntType::BACKGROUND;
}
