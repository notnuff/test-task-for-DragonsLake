//
// Created by notnuff on 21.01.24.
//

#ifndef GAMEPROJECT_PROPELLER_H
#define GAMEPROJECT_PROPELLER_H


#include "Ability.h"

class Propeller : public Ability {

public:
    explicit Propeller(dVec2D position);

    explicit Propeller();

    void affect(Player *player, std::list<TimerEvent *> &eventsList) override;
};


#endif //GAMEPROJECT_PROPELLER_H
