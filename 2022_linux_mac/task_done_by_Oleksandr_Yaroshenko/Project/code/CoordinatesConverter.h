//
// Created by notnuff on 17.01.24.
//

#ifndef GAMEPROJECT_COORDINATESCONVERTER_H
#define GAMEPROJECT_COORDINATESCONVERTER_H

#include "Framework.h"
#include <iostream>
#include <valarray>

struct vec2D {
    int x;
    int y;
};
struct vec4D {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct dVec2D {
    double x;
    double y;

    void normalize() {
        double length = sqrt(x * x + y * y);
        x /= length;
        y /= length;
    }
};

struct dVec4D {
    double x1;
    double y1;
    double x2;
    double y2;
};

struct playerSpritePaths {
    const char *sLeft;
    const char *sRight;
    const char *sJumpL;
    const char *sJumpR;
};

class CoordinatesConverter {
    //static int winWidth;
    //static int winHeight;
public:

    // min x double = -1
    // max x double = 1
    // min y double = -1
    // max y double = 0
    static vec2D worldToScreen(double x, double y) {
        int winWidth;
        int winHeight;
        FRAMEWORK_API::getScreenSize(winWidth, winHeight);
        double dX = (x + 1) * winWidth / 2;
        double dY = winHeight - y * winHeight;

        int sX = (int) dX;
        int sY = (int) dY;


        return vec2D{sX, sY};
    }

    static vec2D worldToScreen(dVec2D vec) {
        return worldToScreen(vec.x, vec.y);
    }

    static vec2D offsetWorldToScreen(dVec2D pos, dVec2D size) {
        dVec2D newPos = {pos.x, pos.y + size.y};
        return worldToScreen(newPos);
    }

    static dVec2D screenToWorld(int x, int y) {
        int winWidth;
        int winHeight;

        FRAMEWORK_API::getScreenSize(winWidth, winHeight);
        //yes, I know about operator overloading, just don`t want to do it in here)

        double preX = (double) x / winWidth;
        double preY = (double) y / winHeight;

        double dX = preX * 2 - 1;
        double dY = 1 - preY;

        return dVec2D{dX, dY};
    }

    static dVec2D screenSizeToWorld(int x, int y) {
        int winWidth;
        int winHeight;

        FRAMEWORK_API::getScreenSize(winWidth, winHeight);
        //yes, I know about operator overloading, just don`t want to do it in here)

        double preX = 2 * (double) x / winWidth;
        double preY = (double) y / winHeight;

        return dVec2D{preX, preY};
    }

    static vec2D offsetWorldToScreen(double x, double y, vec2D offset) {
        vec2D coords = worldToScreen(x, y);
        coords.x -= offset.x;
        coords.y -= offset.y;

        return coords;
    }
};


#endif //GAMEPROJECT_COORDINATESCONVERTER_H
