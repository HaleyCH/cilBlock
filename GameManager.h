//
// Created by 16173 on 2022/3/23.
//

#ifndef CILBLOCK_GAMEMANAGER_H
#define CILBLOCK_GAMEMANAGER_H


#pragma once
#include"Tool.h"
#include "Debug.h"
enum class GAME_STATE {
    HALT=0,
    RUN,
    STOP
};



/*
The standard of my message in std::clog:
	[#] common info
	[*] common message
	[+] begin of a serie of message and info that occured in a stream of operates.
	[|] all those messages.
	[-] end of these operates and the messages.
	[!] critial message
*/

class GameManager {
    friend class CMFCLearning01Dlg;
public:
    static const int TIME_STEP = 500;
    static const int WIDTH = 9;
    static const int HEIGHT = 20;
    GameManager(int width, int height);
    ~GameManager();
    GAME_STATE getState();
    void start();
    void run();
    void haltOrContinue();
    void render();
    void log();
    void log(DEBUG_LEVEL level);
private:
    GAME_STATE _state;
    int *_bigNet;
    int *_bigNetAux;
    int _netWidth, _netHeight;
    Tool _tool;
    Tool _nextTool;
    int _iLocX, _iLocY;

    void addToolToAux(int *net, int iOffestX, int iOffestY, const Tool &_t);
    void nextTool();
    bool isDead();
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
    bool canRotate();
    void moveDown();
    void moveLeft();
    void moveRight();
    void rotate();
    int countNoneZero(int *mat, int height, int width);
    bool canElimateLine(int idx);
    bool removeLine(int idx);
    void removeLines();
};




#endif //CILBLOCK_GAMEMANAGER_H
