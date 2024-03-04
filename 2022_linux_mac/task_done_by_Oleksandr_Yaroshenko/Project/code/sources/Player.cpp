//
// Created by notnuff on 17.01.24.
//

#include "../Player.h"

void Player::jump(double jumpVelocity) {
    vel.y = jumpVelocity;
}

void Player::move(P_MOVE direction) {
    switch (direction) {
        case P_MOVE::LEFT:
            currSprite = sprites.spriteL;
            vel.x -= standardVX;
            accel.x -= standardAccX;
            break;
        case P_MOVE::RIGHT:
            currSprite = sprites.spriteR;
            vel.x += standardVX;
            accel.x += standardAccX;
            break;
        case P_MOVE::STOP_LEFT:
            vel.x = 0;
            accel.x = 0;
            break;
        case P_MOVE::STOP_RIGHT:
            vel.x = 0;
            accel.x = 0;
            break;
        default:
            break;
    }
}

void Player::draw(vec2D coords) {
    FRAMEWORK_API::drawSprite(currSprite, coords.x, coords.y);

    //todo draw mirrored doodle
//        if (posX - size.x/2 <= -1 || posX + size.x/2 >= 1) {
//            coords = prepareCoords(-(2 - posX), posY);
//            FRAMEWORK_API::drawSprite(currSprite, coords.x, coords.y);
//        }
}

FireProjectile *Player::newShot(dVec2D mousePos) {
    dVec2D center = pos;
    center.x += size.x / 2;
    center.y += size.y / 2;

    return new FireProjectile(center, mousePos);
}

Player::Player() {
    ProjectSprites *pSprites = ProjectSprites::getInstance();
    sprites = pSprites->player;
    currSprite = sprites.spriteL;

    int iWidth, iHeight;
    FRAMEWORK_API::getSpriteSize(currSprite, iWidth, iHeight);
    size = CoordinatesConverter::screenSizeToWorld(iWidth, iHeight);

    dVec2D startPos{0, 0.1};
    pos = {startPos.x - size.x / 2, startPos.y};
}

void Player::getDamage(int damage) {
    health -= damage;
}

int Player::getHealth() {
    return health;
}

dVec4D Player::getThisVec() {
    dVec4D playerRect = {pos.x, pos.y,
                         pos.x + size.x, pos.y + size.y};
    return playerRect;
}

EntType Player::getType() {
    return EntType::PLAYER;
}

void Player::setVelocity(double vel) {
    standardVX = vel;
}

void Player::setInvincible(bool check) {
    invincible = check;
}

bool Player::isInvincible() {
    return invincible;
}
