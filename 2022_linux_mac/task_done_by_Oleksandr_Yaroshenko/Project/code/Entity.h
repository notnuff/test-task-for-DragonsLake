//
// Created by notnuff on 17.01.24.
//

#ifndef GAMEPROJECT_ENTITY_H
#define GAMEPROJECT_ENTITY_H

//todo musthave vec4Df dimentions for every sprite
//todo general renderer that converts world -> screen coordinates - done.

#include "CoordinatesConverter.h"

enum class EntType {
    PLAYER, ENEMY, PLATFORM, SHOT, ABILITY, BACKGROUND
};

class Entity {
public:

    virtual ~Entity() = default;

    virtual dVec2D getPosition() = 0;

    virtual void setPosition(dVec2D pos) = 0;

    virtual void changePosition(dVec2D deltaPos) = 0;

    virtual dVec2D getSize() = 0;

    virtual bool intersects(dVec4D vec) = 0;

    virtual bool intersects(Entity *entity) = 0;

    virtual void draw(vec2D coords) = 0;

    virtual EntType getType() = 0;
};

#endif //GAMEPROJECT_ENTITY_H
