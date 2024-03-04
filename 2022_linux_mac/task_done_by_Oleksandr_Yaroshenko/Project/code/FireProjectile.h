//
// Created by notnuff on 19.01.24.
//

#ifndef GAMEPROJECT_FIREPROJECTILE_H
#define GAMEPROJECT_FIREPROJECTILE_H


#include "Entity.h"
#include "ProjectSprites.h"
#include "MovingEntity.h"

class FireProjectile : public MovingEntity {
    double speed = 5;
    Sprite *sprite;
public:
    FireProjectile(dVec2D pCoords, dVec2D mouseCoords);

    void draw(vec2D coords) override;

    EntType getType() override;

};


#endif //GAMEPROJECT_FIREPROJECTILE_H
