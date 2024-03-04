//
// Created by notnuff on 20.01.24.
//

#include "../DisappearingPlatform.h"

DisappearingPlatform::DisappearingPlatform(dVec2D position) {
    ProjectSprites *sprites = ProjectSprites::getInstance();
    sprite = sprites->dissPlatform;
    int iWidth, iHeight;
    FRAMEWORK_API::getSpriteSize(sprite, iWidth, iHeight);
    size = CoordinatesConverter::screenSizeToWorld(iWidth, iHeight);
    pos = position;
}
