//
// Created by notnuff on 17.01.24.
//

#ifndef GAMEPROJECT_PLAYER_H
#define GAMEPROJECT_PLAYER_H


#include <map>
#include "Entity.h"
#include "Framework.h"
#include "CoordinatesConverter.h"
#include "iostream"
#include "FireProjectile.h"
#include "ProjectSprites.h"
#include "MovingEntity.h"


enum class P_MOVE {
    LEFT, RIGHT, STOP_LEFT, STOP_RIGHT
};

class Player : public MovingEntity {
private:
    //through deep researches I understood that it`s really better to keep
    //position and size in separate vectors

    playerSprites sprites;
    double standardVX = 2;
    double standardAccX = 2;
    Sprite *currSprite;
    int health = 5;
    bool invincible = false;
public:
    explicit Player();

    void setInvincible(bool invincible = true);

    bool isInvincible();

    FireProjectile *newShot(dVec2D mousePos);

    void draw(vec2D coords) override;

    void move(P_MOVE direction);

    void jump(double jumpVelocity = 5);

    void getDamage(int damage);

    int getHealth();

    dVec4D getThisVec();

    EntType getType() override;

    void setVelocity(double vel);
};


#endif //GAMEPROJECT_PLAYER_H
