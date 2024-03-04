//
// Created by notnuff on 19.01.24.
//

#ifndef GAMEPROJECT_ENEMY_H
#define GAMEPROJECT_ENEMY_H


#include "ProjectSprites.h"
#include "MovingEntity.h"

class Enemy : public MovingEntity {
    Sprite *sprite;
public:
    explicit Enemy(dVec2D platformCoords);

    void draw(vec2D coords) override;

    EntType getType() override;

};


#endif //GAMEPROJECT_ENEMY_H
