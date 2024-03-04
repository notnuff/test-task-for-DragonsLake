//
// Created by notnuff on 21.01.24.
//

#include "../Shield.h"

Shield::Shield(dVec2D position) {
    ProjectSprites *sprites = ProjectSprites::getInstance();
    sprite = sprites->shield;
    int iWidth, iHeight;
    FRAMEWORK_API::getSpriteSize(sprite, iWidth, iHeight);
    size = CoordinatesConverter::screenSizeToWorld(iWidth, iHeight);
    pos = position;
}

Shield::Shield() : Shield({0, 0.1}) {
}

void Shield::affect(Player *player, std::list<TimerEvent *> &eventsList) {
    player->setInvincible();
    TimerEvent *event = new TimerEvent{20000, [=]() {
        player->setInvincible(false);
    }};
    eventsList.push_front(event);
}
