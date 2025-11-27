#include "GLOBALS/global.hpp"

int main(int argc, char *argv[]) {
    Global::init(1000, 1000);
    Global::runLoop();
    return 0;
}