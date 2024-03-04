//
// Created by notnuff on 16.01.24.
//

#ifndef GAMEPROJECT_GAMEENGINE_H
#define GAMEPROJECT_GAMEENGINE_H

#include "Window.h"
#include "Player.h"
#include "Entity.h"
#include "GameEngine.h"
#include "CoordinatesConverter.h"
#include "Platform.h"
#include "Enemy.h"
#include "ProjectSprites.h"
#include "Background.h"
#include "DisappearingPlatform.h"
#include "TimerEvent.h"
#include "Ability.h"
#include "Propeller.h"
#include "Shield.h"
#include <vector>
#include <list>
#include <functional>


class GameEngine : public Window {
private:
    Player *player;
    Platform *minPlatform;
    Platform *prevPlatform;
    ProjectSprites *projectSprites;
    Background *background;

    Sprite **numbers;
    Sprite *scoreSprite;
    Sprite *heart;

    std::list<Entity *> entities;
    std::list<TimerEvent *> events;
    vec2D screenSize;
    uint platformsPassed = 0;
    double playerSpeedCoeff = 2.5;
    dVec4D playerMove{0, 0, 0, 0};
    double screenPos = 0; //position of bottom of screen in the global world
    double prevPlatUpdatePos = 0;
    double moveSpeedCoefficient = 1;
    double accelerationCoefficient = 0.0004;
    double gravityAccel = -10;
    dVec2D mousePos{0.5, 0.5};
    unsigned int lastTick = 0;
    double platformsUpdateAfter = 0.1;
    double enemiesSpawnRate = 0.1;
    double guaranteedPlatformRange = 0.3;
    double cameraUpdateAfter = 0.6;
    double score;
public:
    bool updateScore();

    explicit GameEngine(int width = 800, int height = 600, bool fullscreen = false);

    void printNumber(int number, dVec2D pos);
    void printScore(dVec2D pos);
    void printHealth(int number, dVec2D pos);

    double fRand(double fMin, double fMax) {
        double f = (double) rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    };

    void generatePlatforms(uint number, dVec4D range, bool enemies = true);

    bool Init() override;

    vec2D getScreenCoords(Entity *entity);

    void drawAll();

    void writePlayerMoves();

    void calcNewPosition(MovingEntity *entity, double deltaTime);

    void calcNewVelocities(MovingEntity *entity, double deltaTime);

    void updateCamera();

    void updatePlatforms();

    void Close() override {

    }

    void updateBackground();

    bool Tick() override;

    void onMouseMove(int x, int y, int xrelative, int yrelative) override;

    void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

    void onKeyPressed(FRKey k) override;

    void onKeyReleased(FRKey k) override;

    bool playerFallen();

    Platform *findMinPlatform();

    bool playerStands(Entity *entity);

    const char *GetTitle() override;

    void gameOver();
};


#endif //GAMEPROJECT_GAMEENGINE_H
