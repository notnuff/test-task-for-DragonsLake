//
// Created by notnuff on 21.01.24.
//

#ifndef GAMEPROJECT_TIMEREVENT_H
#define GAMEPROJECT_TIMEREVENT_H

#include <functional>

struct TimerEvent {
    int ttl;
    std::function<void()> callback;
};

#endif //GAMEPROJECT_TIMEREVENT_H
