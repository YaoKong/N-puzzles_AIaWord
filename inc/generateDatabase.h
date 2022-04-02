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
static uLong goal = 0; //4�ף�ָ��16��byte�������������ո�0�Լ�1~15��Ŀ��״̬�е�λ�ã���ָ��
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