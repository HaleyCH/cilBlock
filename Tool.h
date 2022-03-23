//
// Created by 16173 on 2022/3/23.
//

#ifndef CILBLOCK_TOOL_H
#define CILBLOCK_TOOL_H


#pragma once
class Tool {
protected:
    int _data[4][4] = { 0 };
    int _type=1;
private:
    void make1();
    void make2();
    void make3();
    void make4();
    void make5();
    void make6();
    void make7();
public:
    Tool(int type);
    const int getType() const;
    const int& elemAt(int x, int y) const;
    Tool roll();
};



#endif //CILBLOCK_TOOL_H
