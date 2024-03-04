//
// Created by notnuff on 20.01.24.
//

#ifndef GAMEPROJECT_BACKGROUND_H
#define GAMEPROJECT_BACKGROUND_H


#include "StaticEntity.h"

class Background : public StaticEntity {
    Sprite *sprite;

public:
    double backgroundSpeed = 0.3;

    explicit Background(dVec2D position);

    explicit Background();

    void draw(vec2D coords) override;

    EntType getType() override;
};


#endif //GAMEPROJECT_BACKGROUND_H
