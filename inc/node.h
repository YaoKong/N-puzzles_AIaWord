#ifndef _NODE_H
#define _NODE_H
#include <state.h>
struct node {
	PzlState state;	     //状态
	int	action;			 //所采取的动作
	struct node* parent; //父结点
	int pathCost;        //到达结点的路径长度
	int hValue;			 //当前状态的启发值

	//实现小顶堆
	bool operator>(const struct node& b) const
	{
		return hValue > b.hValue;
	}

	//大顶堆
	bool operator<(const struct node& b) const
	{
		return hValue < b.hValue;
	}
	node(){}
	node(PzlState _state, int _action, struct node* _parent, int _pathCost, int _hValue) {
		state = _state;
		action = _action;
		parent = _parent;
		pathCost = _pathCost;
		hValue = _hValue;
	}
	node(const struct node &obj ){
		state = obj.state;
		action = obj.action;
		parent = obj.parent;
		pathCost = obj.pathCost;
		hValue = obj.hValue;
	};


	// bool operator==(const struct node& b) const
	// {
	// 	return state.status == b.state.status;
	// }


};

typedef struct node Node;
#endif