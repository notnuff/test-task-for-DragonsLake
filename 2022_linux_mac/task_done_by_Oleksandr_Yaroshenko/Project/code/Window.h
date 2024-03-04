//
// Created by notnuff on 16.01.24.
//

#ifndef GAMEPROJECT_WINDOW_H
#define GAMEPROJECT_WINDOW_H

#include "Framework.h"

class Window : public Framework {
protected:
    int width;
    int height;
    bool fullscreen;
public:

    unsigned int lastTick = 0;

    explicit Window(int width = 800, int height = 600, bool fullscreen = false) :
            width(width), height(height), fullscreen(fullscreen) {

    };

    virtual void setSize(int width, int height, bool fullscreen = false) {
        this->width = width;
        this->height = height;
        this->fullscreen = fullscreen;
    }

    virtual void PreInit(int &gwidth, int &gheight, bool &gfullscreen) {
        gwidth = width;
        gheight = height;
        gfullscreen = fullscreen;
    }

    virtual bool Init() {
        return true;
    }

    virtual void Close() {

    }

    virtual bool Tick() {
//
//        int currTick = FRAMEWORK_API::getTickCount();
//        int dtick = currTick - lastTick;
//
//        player->vy += player->dy * dtick / 600;
//        std::cout << currTick << " " << dtick << " " << lastTick << "\n";
//        std::cout << player->posX << " " << player->posY << "\n";
//        lastTick = currTick;
//        if (player->posY >= height) {
//            player->vy = 0;
//            player->posY = 0;
//        }
//        //drawTestBackground();
//        player->move(0, player->vy);
//        FRAMEWORK_API::drawSprite(player->sprite, player->posX, player->posY);
        return false;
    }

    virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

    }

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

    }

    virtual void onKeyPressed(FRKey k) {
    }

    virtual void onKeyReleased(FRKey k) {
    }

    virtual const char *GetTitle() {
        return "Basic window";
    }
};

#endif //GAMEPROJECT_WINDOW_H
