#ifndef _STATE_H
#define _STATE_H
#include "uLong.h"
#include "cell.h"
#include <stdio.h>
#include <stdlib.h>

struct PuzzleState {
    uLong status;       // 当前格局，64位无符号长整数
    int blankPos;       // 空格所在的位置
    int manhattan;      // 当前状态与目标状态的曼哈顿距离
};
typedef struct PuzzleState PzlState; 

extern void setStateSize(int size);
extern void setPzlState(PzlState* state, byte status[]);
extern PzlState* nextStates(PzlState* state, int* numOfChild);
extern void drawState(PzlState* state);
extern char* toCharBuffer(PzlState* state, char* buffer, int buffer_size);
extern void nextState(PzlState* state, int action, PzlState* child);
extern void setGoal(byte* goalstatus);
extern int manhattan(const PzlState& state);
extern int hamming(const PzlState& state);
extern int disjoint(const PzlState& state);
extern int getParity(PzlState* state);
#endif