//
// Created by notnuff on 21.01.24.
//

#ifndef GAMEPROJECT_SHIELD_H
#define GAMEPROJECT_SHIELD_H


#include "Ability.h"

class Shield : public Ability {
public:
    explicit Shield(dVec2D position);

    explicit Shield();

    void affect(Player *player, std::list<TimerEvent *> &eventsList) override;
};


#endif //GAMEPROJECT_SHIELD_H
