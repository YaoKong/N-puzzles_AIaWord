#ifndef _NODE_H
#define _NODE_H
#include <state.h>
struct node {
	PzlState state;	     //״̬
	int	action;			 //����ȡ�Ķ���
	struct node* parent; //�����
	int pathCost;        //�������·������
	int hValue;			 //��ǰ״̬������ֵ
};

typedef struct node Node;
#endif