#ifndef _NODE_H
#define _NODE_H
#include <state.h>
struct node {
	PzlState state;	     //状态
	int	action;			 //所采取的动作
	struct node* parent; //父结点
	int pathCost;        //到达结点的路径长度
	int hValue;			 //当前状态的启发值
};

typedef struct node Node;
#endif