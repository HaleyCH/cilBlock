#include <iostream>
#include "GameManager.h"

int main() {
    FILE *log;
    freopen_s(&log,"runtime.log","w",stderr);
    GameManager GM(9,20);
    GM.start();
    std::cout<<(GM.getState()==GAME_STATE::STOP?0:1)<< std::endl;
    GM.run();
    GM.log();
    fclose(stderr);
}
