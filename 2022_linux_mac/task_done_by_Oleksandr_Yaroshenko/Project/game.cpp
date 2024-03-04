#include "Framework.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include "./code/GameEngine.h"

int main(int argc, char *argv[]) {

    //todo normal separate parser
    std::string sizeKey = "--window";
    std::string fullscreenKey = "--fullscreen";
    std::map<std::string, int> mapping;
    enum keys {
        WINSIZE = 1, FULLSCREEN = 2, EMPTY = 3
    };
    mapping["--window"] = WINSIZE;
    mapping["--fullscreen"] = FULLSCREEN;
    mapping[""] = EMPTY;
    int width = 800;
    int height = 600;
    bool fullscreen = false;

    for (int i = 0; i < argc; i++) {
        std::string currKey = argv[i];
        switch (mapping[currKey]) {
            case WINSIZE:
                width = std::stoi(argv[++i]);
                height = std::stoi(argv[++i]);
                break;
            case FULLSCREEN:
                fullscreen = true;
                break;
            case EMPTY:
                break;
            default:
                break;
                //std::cout << "unknown option";
        }
    }

    auto *thisWin = new GameEngine();
    thisWin->setSize(width, height, fullscreen);
    //std::copy(argv, argv + argc, std::ostream_iterator<char *>(std::cout, "\n"));

    return run(thisWin);
}
