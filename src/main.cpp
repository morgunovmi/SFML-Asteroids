#include "Game.hpp"

int main() {
    float windowWidth = 1280;
    float windowHeight = 720;

    ast::Game game{ windowWidth, windowHeight };
    game.play();

    return 0;
}
