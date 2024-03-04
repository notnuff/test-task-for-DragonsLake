//
// Created by notnuff on 16.01.24.
//

#include "../GameEngine.h"


void GameEngine::printNumber(int number, dVec2D pos) {

    vec2D sPos = CoordinatesConverter::worldToScreen(pos);

    std::vector<int> disintegrated;
    while (number > 0){
        int t = number % 10;
        disintegrated.push_back(t);
        number /= 10;
    }
    for (int i = disintegrated.size() - 1; i >= 0; i--){
        FRAMEWORK_API::drawSprite(numbers[disintegrated[i]], sPos.x, sPos.y);
        int iW, iH;
        FRAMEWORK_API::getSpriteSize(numbers[disintegrated[i]], iW, iH);
        sPos.x += iW + 5;
    }
}
void GameEngine::printScore(dVec2D pos) {
    vec2D sPos = CoordinatesConverter::worldToScreen(pos);
    int iW, iH;
    FRAMEWORK_API::getSpriteSize(scoreSprite, iW, iH);
    FRAMEWORK_API::drawSprite(scoreSprite, sPos.x, sPos.y);
    dVec2D scoreSize = CoordinatesConverter::screenSizeToWorld(iW, iH);
    printNumber(score * screenSize.y, {pos.x + scoreSize.x + 0.1, pos.y});
    printNumber(platformsPassed, {pos.x + scoreSize.x + 1, pos.y});
}
bool GameEngine::updateScore() {
    double posY = player->getPosition().y;
    if (posY >= score) {
        score = posY;
        return true;
    }
    return false;
}

GameEngine::GameEngine(int width, int height, bool fullscreen) : Window(width, height, fullscreen) {
    srand((unsigned) time(NULL));
    screenSize = {width, height};
}

void GameEngine::generatePlatforms(uint number, dVec4D range, bool enemies) {
    for (int i = 0; i < number; i++) {
        dVec2D randCoords = {fRand(range.x1, range.x2),
                             fRand(range.y1, range.y2)};
        Platform *plat;
        if (fRand(0, 1) <= 0.1) {
            plat = new DisappearingPlatform(randCoords);
            auto *event = new TimerEvent{3000, [=]() {
                bool found = (std::find(entities.begin(), entities.end(), plat) != entities.end());
                if (found) {
                    entities.remove(plat);
                    delete plat;
                    if (plat == minPlatform) {
                        minPlatform = findMinPlatform();
                    }
                }
            }
            };
            events.push_front(event);
        } else {
            plat = new Platform(randCoords);
        }

        if (enemies && fRand(0, 1) <= enemiesSpawnRate) {
            randCoords.y += plat->getSize().y;
            auto *enemy = new Enemy(randCoords);
            entities.push_front(enemy);
        }
        entities.push_front(plat);
    }
}

bool GameEngine::Init() {
    projectSprites = ProjectSprites::getInstance();
    numbers = projectSprites->numbers;
    scoreSprite = projectSprites->score;
    heart = projectSprites->heart;

    background = new Background;
    lastTick = FRAMEWORK_API::getTickCount();
    player = new Player;
    player->setAccel({0, gravityAccel});
    player->setVelocity(playerSpeedCoeff / ((double) screenSize.x / screenSize.y / (800.0 / 600)));
    minPlatform = new Platform;
    player->jump(5);
    entities.push_front(minPlatform);
    generatePlatforms(10, {-1, 0.2,
                           1 - minPlatform->getSize().x, 1 + guaranteedPlatformRange}, false);
    return true;
}

vec2D GameEngine::getScreenCoords(Entity *entity) {
    dVec2D pos = entity->getPosition();
    pos.y -= screenPos;
    dVec2D size = entity->getSize();
    vec2D coords = CoordinatesConverter::offsetWorldToScreen(pos, size);
    return coords;
}

void GameEngine::drawAll() {
    vec2D coords = getScreenCoords(player);
    player->draw(coords);
    for (auto entity: entities) {
        coords = getScreenCoords(entity);
        entity->draw(coords);
    }
}

bool GameEngine::Tick() {
    unsigned int currTick = FRAMEWORK_API::getTickCount();
    unsigned int dTick = currTick - lastTick;
    lastTick = currTick;
    double pseudoTick = moveSpeedCoefficient * dTick;



    for (auto it = events.begin(); it != events.end(); it++) {
        TimerEvent *event = *it;
        event->ttl -= (int) dTick;
        if (event->ttl <= 0) {
            event->callback();
            it = events.erase(it);
            it--;
        }
    }

    if (platformsPassed % 10 == 0 && platformsPassed != 0) {

        std::cout << platformsPassed << "\n";
        dVec4D genRange{-1, screenPos + 1,
                        1 - minPlatform->getSize().x, screenPos + 1 + guaranteedPlatformRange};
        dVec2D randCoords = {fRand(genRange.x1, genRange.x2),
                             fRand(genRange.y1, genRange.y2)};
        Platform *plat = new Platform(randCoords);
        randCoords.y += plat->getSize().y;
        Ability *ab;
        if (fRand(0, 1) < 0.5) ab = new Propeller(randCoords);
        else ab = new Shield(randCoords);
        entities.push_front(plat);
        entities.push_front(ab);
        platformsPassed++;
    }

    updateCamera();
    updateBackground();
    updatePlatforms();

    if (playerFallen()) {
        player->getDamage(1);
        if (player->getHealth() <= 0) {
            player->setAccel({0, 0});
            gameOver();
        } else {
            player->setPosition(minPlatform->getPosition());
            player->changePosition({0, minPlatform->getSize().y});
        }
    }

    for (auto it = entities.begin(); it != entities.end(); it++) {
        Entity *entity = *it;

        if (entity->getPosition().y < screenPos - platformsUpdateAfter) {
            it = entities.erase(it);
            delete entity;
            if (entity == minPlatform) {
                minPlatform = findMinPlatform();
            }
            continue;
        }

        switch (entity->getType()) {
            case EntType::PLAYER:
                break;
            case EntType::ENEMY:
                if (playerStands(entity)) {
                    player->jump(7);
                    it = entities.erase(it);
                    it--;
                    delete entity;
                    break;
                }
                if (entity->intersects(player)) {
                    if (player->isInvincible()) break;
                    player->getDamage(1);
                    player->setPosition(minPlatform->getPosition());
                    player->changePosition({0, minPlatform->getSize().y});
                    break;
                }
                break;
            case EntType::PLATFORM:
                if (playerStands(entity)) {
                    player->jump();
                    if (prevPlatform != entity) {
                        platformsPassed++;
                        prevPlatform = dynamic_cast<Platform *>(entity);
                    }
                }
                break;
            case EntType::SHOT:
                calcNewPosition(dynamic_cast<MovingEntity *>(entity), pseudoTick);
                for (auto ent: entities) {
                    if (ent->getType() != EntType::ENEMY) continue;
                    if (ent->intersects(entity)) {
                        it = entities.erase(it);
                        it--;
                        delete entity;
                        entities.remove(ent);
                        delete ent;
                        break;
                    }
                }
                break;
            case EntType::ABILITY:
                if (entity->intersects(player)) {
                    Ability *ab = dynamic_cast<Ability *>(entity);
                    ab->affect(player, events);
                    it = entities.erase(it);
                    it--;
                    delete entity;
                }
                break;
        }
    }

    calcNewVelocities(player, pseudoTick);
    calcNewPosition(player, pseudoTick);

    updateScore();
    printScore({-1, 1});
    printHealth(player->getHealth(), {1, 1});
    writePlayerMoves();

    drawAll();
    return false;
}

void GameEngine::onMouseMove(int x, int y, int xrelative, int yrelative) {
    mousePos = CoordinatesConverter::screenToWorld(x, y);
}

void GameEngine::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    if (isReleased) return;

    FireProjectile *newShot = player->newShot({mousePos.x, mousePos.y + screenPos});
    auto *event = new TimerEvent{3000, [=]() {
        bool found = (std::find(entities.begin(), entities.end(), newShot) != entities.end());
        if (found) {
            entities.remove(newShot);
            delete newShot;
        }
    }
    };
    entities.push_front(newShot);
    events.push_front(event);
}

void GameEngine::onKeyPressed(FRKey k) {
    switch (k) {
        case FRKey::LEFT:
            player->move(P_MOVE::LEFT);
            break;
        case FRKey::RIGHT:
            player->move(P_MOVE::RIGHT);
            break;
        default:
            break;
    }
}

void GameEngine::onKeyReleased(FRKey k) {
    switch (k) {
        case FRKey::LEFT:
            player->move(P_MOVE::STOP_LEFT);
            break;
        case FRKey::RIGHT:
            player->move(P_MOVE::STOP_RIGHT);
            break;
        default:
            break;
    }
}

const char *GameEngine::GetTitle() {
    return "Doodle jump";
}

void GameEngine::calcNewVelocities(MovingEntity *entity, double deltaTime) {
    dVec2D accel = entity->getAccel();
    double dTimeSeconds = deltaTime / 1000.0;
    dVec2D deltaVel = {accel.x * dTimeSeconds, accel.y * dTimeSeconds};
    entity->changeVelocities(deltaVel);
}

void GameEngine::calcNewPosition(MovingEntity *entity, double deltaTime) {
    dVec2D pos = entity->getPosition();
    dVec2D vel = entity->getVelocities();

    pos.x += vel.x * deltaTime * accelerationCoefficient;
    pos.y += vel.y * deltaTime * accelerationCoefficient;

    if (pos.x < -1.0000) {
        pos.x = 1;
    }
    if (pos.x > 1.0000) {
        pos.x = -1;
    }

    entity->setPosition(pos);
}

void GameEngine::writePlayerMoves() {
    playerMove.x1 = playerMove.x2 - player->getSize().x;
    playerMove.y1 = playerMove.y2;
    dVec2D pos = player->getPosition();
    playerMove.x2 = pos.x + player->getSize().x;
    playerMove.y2 = pos.y;
}

void GameEngine::updateCamera() {
    double posY = player->getPosition().y;
    if (posY > cameraUpdateAfter + screenPos) {
        screenPos += posY - (cameraUpdateAfter + screenPos);
    }
    if (posY < screenPos + 0.05) {
        screenPos -= screenPos - posY + 0.05;
    }
}

void GameEngine::updatePlatforms() {
    if (screenPos - prevPlatUpdatePos >= platformsUpdateAfter) {
        dVec4D genRange{-1, screenPos + 1,
                        1 - minPlatform->getSize().x, screenPos + 1 + guaranteedPlatformRange};
        generatePlatforms(1, genRange);
        prevPlatUpdatePos = screenPos;
    }
}

bool GameEngine::playerFallen() {
    if (player->getPosition().y < minPlatform->getPosition().y - 1) {
        return true;
    }
    return false;
}

Platform *GameEngine::findMinPlatform() {
    Entity *min = nullptr;
    for (auto entity: entities) {
        if (entity->getType() != EntType::PLATFORM) continue;
        if (!min) {
            min = entity;
            continue;
        }
        if (entity->getPosition().y < min->getPosition().y)
            min = entity;
    }
    return dynamic_cast<Platform *>(min);
}

bool GameEngine::playerStands(Entity *entity) {
    if (entity->intersects(playerMove)
        && player->getVelocities().y <= 0) {
        return true;
    }
    return false;
}

void GameEngine::updateBackground() {
    dVec2D pos = background->getPosition();
    dVec2D size = background->getSize();

    if (screenPos * background->backgroundSpeed - pos.y >= size.y) {
        background->setPosition({-1, pos.y + size.y});
    }

    pos.y -= (screenPos) * background->backgroundSpeed;
    vec2D coords = CoordinatesConverter::offsetWorldToScreen(pos, size);
    background->draw(coords);
    coords = CoordinatesConverter::offsetWorldToScreen({pos.x, pos.y + size.y}, size);
    background->draw(coords);
}

void GameEngine::gameOver() {

    for (auto entity: entities) {
        delete entity;
    }
    delete background;
    delete player;

    entities.clear();
    for (auto event: events) {
        delete event;
    }
    events.clear();
    screenPos = 0;
    prevPlatUpdatePos = 0;
    Init();
}

void GameEngine::printHealth(int number, dVec2D pos) {

    vec2D sPos = CoordinatesConverter::worldToScreen(pos);
    int iW, iH;
    FRAMEWORK_API::getSpriteSize(heart, iW, iH);
    for(int i = number; i >= 0; i--){
        FRAMEWORK_API::drawSprite(heart, sPos.x, sPos.y);
        sPos.x -= iW + 5;
    }
}