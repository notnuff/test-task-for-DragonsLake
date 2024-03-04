//
// Created by notnuff on 21.01.24.
//

#ifndef GAMEPROJECT_ABILITY_H
#define GAMEPROJECT_ABILITY_H


#include <list>
#include "StaticEntity.h"
#include "Player.h"
#include "TimerEvent.h"

class Ability : public StaticEntity {

protected:
    Sprite *sprite;
public:
    explicit Ability(dVec2D position);

    explicit Ability();

    void draw(vec2D coords) override;

    EntType getType() override;

    virtual void affect(Player *player, std::list<TimerEvent *> &events) = 0;
};


#endif //GAMEPROJECT_ABILITY_H
