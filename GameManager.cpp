
#include "GameManager.h"
#include "iostream"
#include "string"

GameManager::GameManager(int width, int height) : _tool(0), _nextTool(0) {
    std::clog << "[+]Constructing GameManager..." << std::endl;
    _netHeight = height;
    _netWidth = width;
    _bigNet = nullptr;
    _bigNetAux = nullptr;
    _state = GAME_STATE::STOP;
    _iLocX = -1;
    _iLocY = -1;

    std::clog << "[|]Allocate memory for _bigNet." << std::endl;
    _bigNet = new int[_netHeight * _netWidth];
    std::clog << "[|]Allocate memory for _bigNetAux." << std::endl;
    _bigNetAux = new int[_netHeight * _netWidth];
    std::clog << "[|]Init _bigNet." << std::endl;
    for (int x = 0; x < _netHeight; x++) {
        for (int y = 0; y < _netWidth; y++) {
            _bigNet[x * _netWidth + y] = 0;
        }
    }
//    srand((unsigned int)time(0));
    std::clog << "[-]Finish" << std::endl;
}

GameManager::~GameManager() {
    std::clog << "[+]Destructing GameManager..." << std::endl;
    std::clog << "[|]Delete _bigNet." << std::endl;
    delete[] _bigNet;
    std::clog << "[|]Delete _bigNetAux." << std::endl;
    delete[] _bigNetAux;
    std::clog << "[-]Finish." << std::endl;
}

GAME_STATE GameManager::getState() {
    return _state;
}

void GameManager::start() {
    std::clog << "[*]Start..." << std::endl;
    std::clog << "[#]Clear _bigNet." << std::endl;
    for (int x = 0; x < _netHeight; ++x) {
        for (int y = 0; y < _netWidth; ++y) {
            _bigNet[x * _netWidth + y] = 0;
        }
    } // end clear _bigNet for
    _state = GAME_STATE::RUN;
    std::clog << "[#]Init _tool, _nextTool." << std::endl;
    _tool = Tool(0);
    _nextTool = Tool(0);
    std::clog << "[#]Call nextTool twice." << std::endl;
    nextTool();
    nextTool();
    std::clog << "[*]Start End." << std::endl;
}

void GameManager::run() {
    while (_state == GAME_STATE::RUN) {
        std::cout<<"=============="<<std::endl;
        moveDown();
        render();
        log();
        // haltOrContinue();
    }
}

void GameManager::haltOrContinue() {
    if (_state == GAME_STATE::HALT) {
        _state = GAME_STATE::RUN;
        return;
    }
    if (_state == GAME_STATE::RUN) {
        _state = GAME_STATE::HALT;
        return;
    }
}

void GameManager::addToolToAux(int *net, int iOffestX, int iOffestY, const Tool &_t) {
    std::clog << "[*]Adding Tool to _bigNetAux." << std::endl;
//    for (int x = 0; x < 4; ++x) {
//        for (int y = 0; y < 4; ++y) {
//            if ((x + iOffestX) >= _netWidth || (y + iOffestY) > _netHeight) {
//                std::clog << "[!]Out of net, ignore." << std::endl;
//                continue;
//            }
//            net[(y + iOffestY) * _netWidth + x + iOffestX] = _t.elemAt(x, y);
//        }
//    }
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if ((x + iOffestX) >= _netWidth || (y + iOffestY) > _netHeight) {
                std::clog << "[!]Out of net, ignore." << std::endl;
                continue;
            }
            net[(y + iOffestY) * _netWidth + x + iOffestX] = _t.elemAt(x, y);
        }
    }
    std::clog << "[*]Add Finish." << std::endl;
}

void GameManager::nextTool() {
    std::clog << "[+]Create next tool." << std::endl;
    _tool = _nextTool;
    _nextTool = Tool(rand() % 7 + 1);
    _iLocY = 0;
    _iLocX = ((_netWidth - 4) / 2);
    std::clog << "[|]Set location to " << _iLocX << ", " << _iLocY << "." << std::endl;
    std::clog << "[-]Finish create next tool." << std::endl;
}

bool GameManager::isDead() {
    std::clog << "[*]Judging whether is dead..." << std::endl;
    int ctr = countNoneZero(_bigNet, _netHeight, _netWidth);
    std::clog << "[*]Copy _bigNet to _bigNetAux by memcpy." << std::endl;
    memcpy(_bigNetAux, _bigNet, _netHeight * _netWidth * sizeof(int));
    addToolToAux(_bigNetAux, _iLocX, _iLocY, _tool);
    if (ctr + 4 > countNoneZero(_bigNetAux, _netHeight, _netWidth)) {
        std::clog << "[*]Is dead." << std::endl;
        return true;
    }
    std::clog << "[*]Not dead." << std::endl;
    return false;
}

bool GameManager::canMoveLeft() {
    std::clog << "[*]Judging whether Tool can move Left..." << std::endl;
    int ctr = countNoneZero(_bigNet, _netHeight, _netWidth);
    std::clog << "[*]Copy _bigNet to _bigNetAux by memcpy." << std::endl;
    memcpy(_bigNetAux, _bigNet, _netHeight * _netWidth * sizeof(int));
    addToolToAux(_bigNetAux, _iLocX - 1, _iLocY, _tool);
    if (ctr + 4 > countNoneZero(_bigNetAux, _netHeight, _netWidth)) {
        std::clog << "[*]Can Not move Left." << std::endl;
        return false;
    }
    std::clog << "[*]Can move Left." << std::endl;
    return true;
}

bool GameManager::canMoveRight() {
    std::clog << "[*]Judging whether Tool can move Right..." << std::endl;
    int ctr = countNoneZero(_bigNet, _netHeight, _netWidth);
    std::clog << "[*]Copy _bigNet to _bigNetAux by memcpy." << std::endl;
    memcpy(_bigNetAux, _bigNet, _netHeight * _netWidth * sizeof(int));
    addToolToAux(_bigNetAux, _iLocX + 1, _iLocY, _tool);
    if (ctr + 4 > countNoneZero(_bigNetAux, _netHeight, _netWidth)) {
        std::clog << "[*]Can Not move Right." << std::endl;
        return false;
    }
    std::clog << "[*]Can move Right." << std::endl;
    return true;
}

bool GameManager::canMoveDown() {
    std::clog << "[*]Judging whether Tool can move Down..." << std::endl;
    int ctr = countNoneZero(_bigNet, _netHeight, _netWidth);
    std::clog << "[*]Copy _bigNet to _bigNetAux by memcpy." << std::endl;
    memcpy(_bigNetAux, _bigNet, _netHeight * _netWidth * sizeof(int));
    addToolToAux(_bigNetAux, _iLocX, _iLocY + 1, _tool);
    if (ctr + 4 != countNoneZero(_bigNetAux, _netHeight, _netWidth)) {
        std::clog << "[*]Can Not move Down." << std::endl;
        return false;
    }
    std::clog << "[*]Can move Down." << std::endl;
    return true;
}

bool GameManager::canRotate() {
    std::clog << "[*]Judging whether Tool can rotate..." << std::endl;
    int ctr;
    ctr = countNoneZero(_bigNet, _netHeight, _netWidth);
    auto rotatedT = _tool.roll();
    std::clog << "[*]Copy _bigNet to _bigNetAux by memcpy." << std::endl;
    memcpy(_bigNetAux, _bigNet, _netHeight * _netWidth * sizeof(int));
    addToolToAux(_bigNetAux, _iLocX, _iLocY, rotatedT);
    if (countNoneZero(_bigNetAux, _netHeight, _netWidth) - 4 == ctr) {
        std::clog << "[*]Can rotate." << std::endl;
        return true;
    }
    std::clog << "[*]Can Not rotate." << std::endl;
    return false;
}

void GameManager::moveDown() {
    std::clog << "[*]Move Down." << std::endl;
    if (!canMoveDown()) {
        std::clog << "[!]Cannot move Down." << std::endl;
        //        std::clog << "[*]Adding tool to _bigNet..." << std::endl;
        //        addToolToAux(_bigNet, _netWidth, _netHeight, _tool);
        //        std::clog << "[*]Add Finish." << std::endl;
        //        if (!isDead()) {
        //            std::clog << "[!]Copying Tool to _bigNet..." << std::endl;
        //            for (int i=0;i<4;i++){
        //                for (int j=0;j<4;j++){
        //                    _bigNet[(j+_iLocY)*_netWidth+(i+_iLocX)] = _tool.elemAt(i,j);
        //                }
        //            }
        //            std::clog << "[!]Copy Finish." << std::endl;
        //            std::clog << "[*]Call nextTool." << std::endl;
        //            nextTool();
        //            return;
        //        }
        //        std::clog << "[!]Game over." << std::endl;
        //        _state = GAME_STATE::STOP;
        //        return;
        //    }
        std::clog << "[!]Copying Tool to _bigNet..." << std::endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                _bigNet[(j + _iLocY) * _netWidth + (i + _iLocX)] = _tool.elemAt(i, j);
            }
        }
        std::clog << "[*]Copy Finish." << std::endl;
        std::clog << "[*]Call nextTool." << std::endl;
        nextTool();
        if (isDead()) {
            _state = GAME_STATE::STOP;
        }
        return;
    }
    _iLocY += 1;
    std::clog << "[*]Move Finish." << std::endl;
}

void GameManager::moveLeft() {
    std::clog << "[*]Move Left." << std::endl;
    if (!canMoveLeft()) {
        std::clog << "[!]Cannot move Left." << std::endl;
        return;
    }
    _iLocX -= 1;
    std::clog << "[*]Move Finish." << std::endl;
}

void GameManager::moveRight() {
    std::clog << "[*]Move Right." << std::endl;
    if (!canMoveRight()) {
        std::clog << "[!]Cannot move Right." << std::endl;
        return;
    }
    _iLocX += 1;
    std::clog << "[*]Move Finish." << std::endl;
}

void GameManager::rotate() {
    std::clog << "[*]Rotate." << std::endl;
    if (!canRotate()) {
        return;
    }
    _tool = _tool.roll();
    std::clog << "[*]Rotate Finish." << std::endl;
}

int GameManager::countNoneZero(int *mat, int height, int width) {
    int ctr = 0;
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            if (mat[width * x + y] != 0) {
                ++ctr;
            }
        }
    }
    std::clog << "[#]None zero: " << ctr << std::endl;
    return ctr;
}

bool GameManager::canElimateLine(int idx) {
    std::clog << "[*]Judging whether Line " << idx << " can elimate..." << std::endl;
    for (int i = 0; i < _netWidth; ++i) {
        if (_bigNet[idx * _netWidth + i] == 0) {
            std::clog << "[*]Cannot elimate Line " << idx << "." << std::endl;
            return false;
        }
    }

    std::clog << "[*]Can elimate Line " << idx << "." << std::endl;
    return true;
}

bool GameManager::removeLine(int idx) {
    std::clog << "[*]Try to remove Line " << idx << "..." << std::endl;
    if (!canElimateLine(idx)) {
        std::clog << "[*]Not remove." << std::endl;
        return false;
    }
    std::clog << "[*]Removing Line " << idx << "..." << std::endl;
    for (int i = idx; i > 0; ++i) {
        for (int j = 0; j < _netWidth; ++j) {
            _bigNet[(i) * _netWidth + j] = _bigNet[(i - 1) * _netWidth + j];
        }
    }
    for (int j = 0; j < _netWidth; ++j) {
        _bigNet[j] = 0;
    }
    std::clog << "[*]Remove Line " << idx << " Finish." << std::endl;
    return true;
}

void GameManager::removeLines() {
    std::clog << "[+]Removing Lines..." << std::endl;
    for (int i = _netHeight - 1; i >= 0; --i) {
        while (removeLine(i)) {
            continue;
        }
    }
    std::clog << "[-]Finish Remove lines." << std::endl;
}

void GameManager::render() {
    system("cls");
    std::clog << "[*]Rendering _bigNet..." << std::endl;
    std::clog << "[*]Copy _bigNet to _bigNetAux by memcpy." << std::endl;
    memcpy(_bigNetAux, _bigNet, _netHeight * _netWidth * sizeof(int));
    addToolToAux(_bigNetAux, _iLocX, _iLocY, _nextTool);
    for (int y = 0; y < _netHeight; ++y) {
        for (int x = 0; x < _netWidth; ++x) {
            std::cout << _bigNetAux[y * _netWidth + x];
        }
        std::cout << std::endl;
    }
    std::clog << "[*]Render Finish." << std::endl;
}

void GameManager::log() {
    std::clog << "[@]GENERAL_LOG[@]" << std::endl;
    std::clog << "_iLocX: " << _iLocX << " _iLocY: " << _iLocY << std::endl;
    std::clog << "Tool type: " << _tool.getType() << std::endl;
    std::clog << "[@]GENERAL_LOG_END[@]" << std::endl;
}

void GameManager::log(DEBUG_LEVEL level) {
    std::clog << "[@]GENERAL_LOG[@]" << std::endl;
    std::clog << "_iLocX: " << _iLocX << " _iLocY: " << _iLocY << std::endl;
    std::clog << "Tool type: " << _tool.getType() << std::endl;
    if (level >= DEBUG_LEVEL::DEBUG) {
        std::clog << "_bigNet" << std::endl;
        for (int y = 0; y < _netHeight; ++y) {
            for (int x = 0; x < _netWidth; ++x) {
                std::clog << _bigNet[y * _netWidth + x];
            }
            std::clog << std::endl;
        }
        std::clog << "_bigNetAux" << std::endl;
        for (int y = 0; y < _netHeight; ++y) {
            for (int x = 0; x < _netWidth; ++x) {
                std::clog << _bigNetAux[y * _netWidth + x];
            }
            std::clog << std::endl;
        }
    }

    std::clog << "[@]GENERAL_LOG_END[@]" << std::endl;
}
