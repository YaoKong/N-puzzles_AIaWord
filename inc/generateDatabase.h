#ifndef _GENERATE_H
#define _GENERATE_H
#include <node.h>
#include <map>
#include <queue>

// typedef struct Partition {
// 	int index[6];
// 	int length = 0;
// } Partition;

static int aSize = 0;
static uLong goal = 0; //4阶：指向16个byte连续数据区（空格0以及1~15在目标状态中的位置）的指针
static std::vector<std::map<uLong, int> >* tables = NULL;
static std::vector<std::map<int, bool> >* partitions = NULL;
static int emptyIndex,tableIndex;



void initDatabase(PzlState* state, int _size);
void bfs(PzlState* state);
void partitionDatabase(PzlState* state, int size);
Node* moveNode(Node* currentState);
PzlState getDummyState(int* dummy);
int validMove(int blankPos, int offset[], int size);
#endif