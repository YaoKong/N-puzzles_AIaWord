#ifndef _PROBLEM_H
#define _PROBLEM_H

#include "state.h"
#include "twobuff.h"
#include <Windows.h>    //Windows操作系统特有的

typedef int(*Heuristic)(const PzlState& state);
extern void newProblem(byte goalstatus[], byte initstatus[], int size);
extern int isGoal(PzlState* state);
extern PzlState* getGoal();
extern PzlState* getInit();
extern int solvable();
extern void animation(char* path);
extern void drawSolution(char* path);
extern void astar(char* path, Heuristic _heuristics);
extern void printProblem();
extern void idaStar(char* path, Heuristic _heuristics);

#endif