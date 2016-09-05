#include "Ball.h"
#include "Game.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char const *argv[]) {
    try {

        Game pong;
        pong.init();
        pong.run();

    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "..." << std::endl;
    }
    return 0;
}
