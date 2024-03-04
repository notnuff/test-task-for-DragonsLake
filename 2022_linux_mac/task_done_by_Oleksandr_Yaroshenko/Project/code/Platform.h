//
// Created by notnuff on 17.01.24.
//

#ifndef GAMEPROJECT_PLATFORM_H
#define GAMEPROJECT_PLATFORM_H


#include "Entity.h"
#include "Framework.h"
#include "CoordinatesConverter.h"
#include "ProjectSprites.h"
#include "StaticEntity.h"

class Platform : public StaticEntity {
protected:
    Sprite *sprite;
public:
    explicit Platform(dVec2D position);

    explicit Platform();

    void draw(vec2D coords) override;

    EntType getType() override;
};


#endif //GAMEPROJECT_PLATFORM_H
