//
// Created by notnuff on 21.01.24.
//

#include "../Propeller.h"


Propeller::Propeller(dVec2D position) {
    ProjectSprites *sprites = ProjectSprites::getInstance();
    sprite = sprites->propeller;
    int iWidth, iHeight;
    FRAMEWORK_API::getSpriteSize(sprite, iWidth, iHeight);
    size = CoordinatesConverter::screenSizeToWorld(iWidth, iHeight);
    pos = position;
}

Propeller::Propeller() : Propeller({0, 0.1}) {
}


void Propeller::affect(Player *player, std::list<TimerEvent *> &eventsList) {
    dVec2D prevAcc = player->getAccel();
    player->setInvincible();
    player->setAccel({0, 0});
    TimerEvent *event = new TimerEvent{3000, [=]() {
        player->setAccel(prevAcc);
        player->setInvincible(false);
    }};
    eventsList.push_front(event);
}
