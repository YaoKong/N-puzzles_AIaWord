#include <problem.h>
#include <direction.h>
#include <map>

#include "aStar.h"
#include "node.h"
static int _size = 0;
static PzlState goal;
static PzlState init;
static int count = 0;	// 已经求解的问题的个数

void printStatus(uLong status) {
	byte* temp = getValues(status);
	for (int i = 0; i < _size * _size; i++) {
		printf("%hhu", temp[i]);
	}

	printf("\n");
}

/*
 开始一个新问题
*/
void newProblem(byte goalstatus[], byte initstatus[], int size) {

	setStateSize(size);   //为所有状态设置全局的规模：size
	setGoal(goalstatus);  //为所有状态设置全局的目标状态

	_size = size;         //设置问题的规模为size
	setPzlState(&goal, goalstatus);	//设置当前问题的目标状态
	setPzlState(&init, initstatus); //设置当前问题的初始状态

	// printStatus(goal.status);

	count++;
}

//状态state是否是目标状态
int isGoal(PzlState* state) {
	return state->status == goal.status;
}


PzlState* getGoal()
{
	return &goal;
}

PzlState* getInit()
{
	return &init;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int solvable()
{
	int flag = 0;
	if(_size % 2) {
		if ((getParity(&init) % 2) == (getParity(&goal))) flag = 1;
	}
	else {
		int rowSpacing = init.blankPos % _size;
		int initParity = getParity(&init) + rowSpacing;
		if ((initParity % 2 )== (getParity(&goal) % 2)) flag = 1;
	}
	return flag;
	return getParity(&init) == (goal.blankPos % 2);
}

/// <summary>
/// 打印当前问题
/// </summary>
void printProblem() {
	drawState(&goal);
	printf("\n");

	drawState(&init);
	printf("\n");

	printf("%d\n", manhattan(init));
}

/// <summary>
/// astar搜索
/// </summary>
/// <param name="path"></param>
void astar(char* path, Heuristic _heuristics) {
	//Fix Me. 用Astar算法求出各个问题的最优解，而不是预先放在以下的数组里:)
	// const char* solutions[7] = {
	// 	"SENWSSENWSWNNEESWWSEE",
	// 	"NWSESWNWSENNESSWNWNEESWWNEESWSE",
	// 	"NNESWWSEENWWNEESWSWNNESSWNNEESS",
	// 	"WWSESENNWSSWNESSENNENWWSSSENNENWWSSWSEENWWSEENWNESES",
	// 	"NENWNEESSSENNNWSWSSENENWWWSSENESWNWNNEESSWWNNESESES",
	// 	"ESSWSENWNWWSSEENNWWSEENESWWNENWWSEENWWSSSENNEENWSWWSEESE",
	// 	"SWWNESWSSENESENNNWWSESSWNWNEENWSSEESWNNESS"
	// };
	// printf("%d\n", _heuristics(init));
	// memcpy(path, solutions[count - 1], strlen(solutions[count - 1]) + 1);


	int pathLen = 0;
	PriorityQueue<Node*, int> frontier;
	std::unordered_map<uLong,int> explore;
	// std::map<Node*, Node> comeFrom;

	Node* node = new Node(init, -1, NULL, 0, 0);
	frontier.put(node, 0);
	explore[node->state.status] = 0 ;
	// comeFrom[node] = *node;




	while(!frontier.empty()) {

		node = frontier.get();

		if (node->state.status == goal.status) {
			break;
		}

		int numOfChild;
		int dummy[4];
		PzlState* children = nextStates(&node->state, &numOfChild, dummy);
		for(int i = 0; i < 4; i++) {
			if(!dummy[i]) continue;
	
			int newCost = node->pathCost + 1;
			uLong childStatus = children[i].status;
			if(explore.end() == explore.find(childStatus) ||
				newCost < explore[childStatus]) {
	
				int hValue = newCost + _heuristics(children[i]);
				Node* child = new Node(children[i], i, node, newCost, hValue);
				frontier.put(child, hValue);
				explore[childStatus] = newCost;
				// comeFrom[child] = *node;
			}
		}
	}

	while (node->parent) {
		char dir;
		switch (node->action) {
			case 0: path[pathLen++] = 'N'; break;
			case 1: path[pathLen++] = 'E'; break;
			case 2: path[pathLen++] = 'S'; break;
			case 3: path[pathLen++] = 'W'; break;
			default: path[pathLen++] = '\0'; break;
		}
		node = node->parent;
	}
	path[pathLen] = '\0';

	for(int i = 0; i < pathLen / 2; i++) {
		char temp = path[i];
		path[i] = path[pathLen - i - 1];
		path[pathLen - i - 1] = temp;
	}

	printf("%s\n", path);


}

static int  maxDeepth, minDistance;
static Node* endNode;
bool dfs(Node* tempNode, Heuristic _heuristics) {
	int distance = _heuristics(tempNode->state);	//估计到目标还要多深

	if (distance == 0) {	//当距离为0时，此时是终点
		endNode = tempNode;
		return true;
	}

	int estimateDistance = distance + tempNode->pathCost;	//根据当前状态，估计到终点时的深度
	if(maxDeepth < estimateDistance && minDistance < estimateDistance) {	//当估计深度大于最大深度，且最小距离也小于估计距离
			minDistance = estimateDistance;	//让最小距离为估计深度
	}


	//若估计深度大于最大深度，则返回假，增大最大深度
	if(estimateDistance > maxDeepth) return false;



	int numOfChild;
	int dummy[4];
	PzlState* children = nextStates(&tempNode->state, &numOfChild, dummy);
	for(int i = 0; i < 4; i++) {
		if(dummy[i] == 0) continue;
		int action = (i + 2) % 4;
		if(action == tempNode->action) continue;


		Node* p = new Node(children[i], i, tempNode, tempNode->pathCost + 1, 0);
		if (dfs(p, _heuristics)) return true;
		delete p;

	}
	return false;
}

void idaStar(char* path, Heuristic _heuristics){
	//Fix Me.

	maxDeepth = _heuristics(init);
	minDistance = maxDeepth;
	Node* tempNode = new Node(init, -1, NULL, 0, maxDeepth);

	while (!dfs(tempNode, _heuristics)) {
		maxDeepth = minDistance > maxDeepth ? minDistance : (maxDeepth + 1);
	}

	int pathLen = 0;
	tempNode = endNode;
	while (tempNode->parent) {
		char dir;
		switch (tempNode->action) {
		case 0: path[pathLen++] = 'N'; break;
		case 1: path[pathLen++] = 'E'; break;
		case 2: path[pathLen++] = 'S'; break;
		case 3: path[pathLen++] = 'W'; break;
		default: path[pathLen++] = '\0'; break;
		}
		tempNode = tempNode->parent;
	}
	path[pathLen] = '\0';


	for (int i = 0; i < pathLen / 2; i++) {
		char temp = path[i];
		path[i] = path[pathLen - i - 1];
		path[pathLen - i - 1] = temp;
	}

	printf("%s\n", path);

}

/// <summary>
/// 可视化解路径，利用双缓冲技术，实现Console字符界面的动画效果
/// </summary>
/// <param name="path">解路径</param>
void animation(char* path){

	initDoubleBuffer();	 //初始化console双缓冲区

//// 初始化一个字符缓冲区 //// 
	int n_col = _size * 4 + 1;
	int n_row = _size * 2 + 1;
	int buffer_size = n_col * n_row;	
	char* buffer = (char*) malloc(sizeof(char) * buffer_size);
////////////////////////////
	
//// 动画显示解路径 ////
	char caption[200];   //标题
	sprintf_s(caption, 200, "solving problem %02d......", count);
	PzlState currState = *getInit();
	toCharBuffer(&currState, buffer, buffer_size);

	while(*path) {
		showBuffer(buffer, n_col, n_row, caption);
		nextState(&currState, toDirection(* path), &currState);
		toCharBuffer(&currState, buffer, buffer_size);
		showBuffer(buffer, n_col, n_row, caption);
		path++;
	}
	toCharBuffer(&currState, buffer, buffer_size);
	showBuffer(buffer, n_col, n_row, caption);
////////////////////////////

	Sleep(2000);
	free(buffer);   //释放掉buffer所占空间
}

//小小地修改了一下这个函数，多加了一个参数
static void drawArrow(int size, char action, PzlState* state){
	//FixMe.
	int d = toDirection(action);
	const char* arrow = toString(d, 0);

	for (int i = 0; i < _size; i++) {
		//画分割线
		for (int j = 0; j < _size; j++) {
			printf("+---");
		}
		printf("+\n");

		//输出对应格子
		for (int j = 0; j < _size; j++) {
			char c = getValue(state->status, i * _size + j) + 48;
			if (c == '0') printf("|%s", arrow);
			else printf("| %c ", c);
			
		}
		printf("|\n");
	}

	//画分割线
	for (int i = 0; i < _size; i++) {
		printf("+---");
	}
	printf("+\n");
}

/// <summary>
/// 显示解路径
/// </summary>
/// <param name="path">解路径</param>
void drawSolution(char* path){
	//Fix Me.
	//要求调用drawState, drawArrow, nextState
	//
	//// 动画显示解路径 ////
	char caption[200];   //标题
	sprintf_s(caption, 200, "solving problem %02d......", count);
	PzlState currState = *getInit();
	PzlState child;

	char* p = path;
	while (*p) {
		drawState(&currState);
		Sleep(500);
		system("cls");
		drawArrow(_size, *p, &currState);
		Sleep(500);
		system("cls");

		nextState(&currState, toDirection(*p), &child);
		currState = child;	//更新当前状态
		p++;
	}

}
