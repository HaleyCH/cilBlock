#include "Tool.h"

void Tool::make1() {
    /*
	type 1:
	0 1 0 0    0 0 0 0
	0 1 0 0    0 0 0 0
	0 1 0 0    1 1 1 1
	0 1 0 0	   0 0 0 0
	*/
    _data[1][0] = 1;
    _data[1][1] = 1;
    _data[1][2] = 1;
    _data[1][3] = 1;
}

void Tool::make2() {
    /*
	type 2:
	0 0 0 0
	0 1 1 0
	0 1 1 0
	0 0 0 0
	*/
    _data[1][1] = 2;
    _data[1][2] = 2;
    _data[2][1] = 2;
    _data[2][2] = 2;
}

void Tool::make3() {
    /*
	type 3:
	0 0 0 0    0 0 0 0    0 0 1 0    0 0 0 0
	0 1 1 0    1 1 1 0    0 0 1 0    0 1 0 0
	0 1 0 0    0 0 1 0    0 1 1 0    0 1 1 1
	0 1 0 0    0 0 0 0    0 0 0 0    0 0 0 0
	*/
    _data[1][1] = 3;
    _data[2][1] = 3;
    _data[1][2] = 3;
    _data[3][2] = 3;
}


void Tool::make4() {
    /*
	type 4:
	0 0 0 0    0 0 0 0    0 1 0 0    0 0 0 0
	0 1 1 0    0 0 1 0    0 1 0 0    0 1 1 1
	0 0 1 0    1 1 1 0    0 1 1 0    0 1 0 0
	0 0 1 0    0 0 0 0    0 0 0 0    0 0 0 0
	*/
    _data[1][1] = 4;
    _data[2][1] = 4;
    _data[2][2] = 4;
    _data[2][3] = 4;
}

void Tool::make5() {
    /*
	type 5:
	0 0 0 0    0 1 0 0    0 0 0 0    0 0 0 0
	0 1 1 0    0 1 1 0    0 0 1 1    0 1 0 0
	1 1 0 0    0 0 1 0    0 1 1 0    0 1 1 0
	0 0 0 0    0 0 0 0    0 0 0 0    0 0 1 0
	*/
    _data[1][1] = 5;
    _data[2][1] = 5;
    _data[0][2] = 5;
    _data[1][2] = 5;
}

void Tool::make6() {
    /*
	type 6:
	0 0 0 0    0 0 1 0    0 0 0 0    0 0 0 0
	1 1 0 0    0 1 1 0    0 1 1 0    0 0 1 0
	0 1 1 0    0 1 0 0    0 0 1 1    0 1 1 0
	0 0 0 0    0 0 0 0    0 0 0 0    0 1 0 0
	*/
    _data[0][1] = 6;
    _data[1][1] = 6;
    _data[2][1] = 6;
    _data[2][2] = 6;
}

void Tool::make7() {
    /*
	type 7:
	0 0 0 0    0 0 0 0    0 0 0 0    0 0 1 0
	0 0 1 0    0 1 0 0    1 1 1 0    0 1 1 0
	0 1 1 1    0 1 1 0    0 1 0 0    0 0 1 0
	0 0 0 0    0 1 0 0    0 0 0 0    0 0 0 0
	*/
    _data[2][1] = 7;
    _data[1][2] = 7;
    _data[2][2] = 7;
    _data[3][2] = 7;
}

Tool::Tool(int type) : _type(type){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            _data[i][j] = 0;
        }
    }
    if (_type == 1) {
        make1();
    }
    if (_type == 2) {
        make2();
    }
    if (_type == 3) {
        make3();
    }
    if (_type == 4) {
        make4();
    }
    if (_type == 5) {
        make5();
    }
    if (_type == 6) {
        make6();
    }
    if (_type == 7) {
        make7();
    }
}

const int Tool::getType() const {
    return _type;
}

const int& Tool::elemAt(int x, int y) const {
    return _data[x][y];
}

Tool Tool::roll() {
    Tool rotatedT(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotatedT._data[i][j] = _data[3 - j][i];
        }
    }
    return rotatedT;
}


