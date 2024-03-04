cmake_minimum_required(VERSION 3.6)
project(GameProject VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES game.cpp
        code/sources/ProjectSprites.cpp
        code/ProjectSprites.h
        code/sources/Window.cpp
        code/Window.h
        code/sources/GameEngine.cpp
        code/GameEngine.h
        code/sources/GameEngine.cpp
        code/GameEngine.h
        code/sources/Entity.cpp
        code/Entity.h
        code/sources/Player.cpp
        code/Player.h
        code/sources/CoordinatesConverter.cpp
        code/CoordinatesConverter.h
        code/sources/Platform.cpp
        code/Platform.h
        code/sources/Enemy.cpp
        code/Enemy.h
        code/sources/FireProjectile.cpp
        code/FireProjectile.h
        code/ProjectSprites.h
        code/sources/StaticEntity.cpp
        code/StaticEntity.h
        code/sources/MovingEntity.cpp
        code/MovingEntity.h
        code/sources/Background.cpp
        code/Background.h
        code/sources/DisappearingPlatform.cpp
        code/DisappearingPlatform.h
        code/sources/Ability.cpp
        code/Ability.h
        code/sources/Propeller.cpp
        code/Propeller.h
        code/sources/Shield.cpp
        code/Shield.h
        code/TimerEvent.h)

add_subdirectory(Framework)

add_executable(GameProject ${SOURCES} Framework/inc/Framework.h)


target_link_libraries(GameProject Framework)


target_include_directories(GameProject PUBLIC
        "Framework/inc"
        "Framework/cmake-build-debug"
)

