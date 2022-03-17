#include <problem.h>
#include <direction.h>
static int _size = 0;
static PzlState goal;
static PzlState init;
static int count = 0;	// 已经求解的问题的个数

/*
 开始一个新问题
*/
void newProblem(byte goalstatus[], byte initstatus[], int size) {

	setStateSize(size);   //为所有状态设置全局的规模：size
	setGoal(goalstatus);  //为所有状态设置全局的目标状态

	_size = size;         //设置问题的规模为size
	setPzlState(&goal, goalstatus);	//设置当前问题的目标状态
	setPzlState(&init, initstatus); //设置当前问题的初始状态	
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
	const char* solutions[7] = {
		"SENWSSENWSWNNEESWWSEE",
		"NWSESWNWSENNESSWNWNEESWWNEESWSE",
		"NNESWWSEENWWNEESWSWNNESSWNNEESS",
		"WWSESENNWSSWNESSENNENWWSSSENNENWWSSWSEENWWSEENWNESES",
		"NENWNEESSSENNNWSWSSENENWWWSSENESWNWNNEESSWWNNESESES",
		"ESSWSENWNWWSSEENNWWSEENESWWNENWWSEENWWSSSENNEENWSWWSEESE",
		"SWWNESWSSENESENNNWWSESSWNWNEENWSSEESWNNESS"
	};
	printf("%d\n", _heuristics(init));
	memcpy(path, solutions[count - 1], strlen(solutions[count - 1]) + 1);
}

void idaStar(char* path, Heuristic _heuristics){
	//Fix Me.
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
	char arrows[] = { '↑', '-->','↓', '<--' };
	char arrow = arrows[toDirection(action)];
	for (int i = 0; i < _size; i++) {
		//画分割线
		for (int i = 0; i < _size; i++) {
			printf("+---");
		}
		printf("+\n");

		//输出对应格子
		for (int j = 0; j < _size; j++) {
			char c = getValue(state->status, i * _size + j) - 48;
			if (c == '0') c = arrow;

			printf("| %c ", c);
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

		drawArrow(_size, *p, &currState);
		Sleep(500);


		nextState(&currState, toDirection(*p), &child);
		drawState(&child);
		Sleep(500);

		currState = child;	//更新当前状态
		p++;
	}

}
