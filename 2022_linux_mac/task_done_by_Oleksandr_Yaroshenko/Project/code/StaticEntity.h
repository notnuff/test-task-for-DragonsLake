//
// Created by notnuff on 19.01.24.
//

#ifndef GAMEPROJECT_STATICENTITY_H
#define GAMEPROJECT_STATICENTITY_H


#include "Entity.h"

class StaticEntity : public Entity {

protected:
    dVec2D pos;
    dVec2D size;
public:

    ~StaticEntity() override = default;

    dVec2D getPosition() override {
        return pos;
    }

    dVec2D getSize() override {
        return size;
    }

    void setPosition(dVec2D position) override {
        pos = position;
    };

    virtual bool intersects(dVec4D vec) override {
        dVec4D thisRect = {pos.x, pos.y,
                           pos.x + size.x, pos.y + size.y};
        if (!(thisRect.x1 <= vec.x1 && thisRect.x2 >= vec.x1 ||
              thisRect.x1 <= vec.x2 && thisRect.x2 >= vec.x2))
            return false;
        if (!(thisRect.y1 <= vec.y1 && thisRect.y2 >= vec.y1 ||
              thisRect.y1 <= vec.y2 && thisRect.y2 >= vec.y2))
            return false;
        return true;
    };

    virtual bool intersects(Entity *entity) override {
        dVec4D entVec = {entity->getPosition().x, entity->getPosition().y,
                         entity->getPosition().x + entity->getSize().x,
                         entity->getPosition().y + entity->getSize().y
        };
        return intersects(entVec);
    }

    void changePosition(dVec2D deltaPos) override {
        pos.x += deltaPos.x;
        pos.y += deltaPos.y;
    };
};


#endif //GAMEPROJECT_STATICENTITY_H
