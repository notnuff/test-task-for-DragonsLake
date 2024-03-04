//
// Created by notnuff on 21.01.24.
//

#include "../Ability.h"
#include "../ProjectSprites.h"

void Ability::draw(vec2D coords) {
    FRAMEWORK_API::drawSprite(sprite, coords.x, coords.y);
}


Ability::Ability(dVec2D position) {
}

Ability::Ability() : Ability({0, 0.1}) {
}

EntType Ability::getType() {
    return EntType::ABILITY;
}

