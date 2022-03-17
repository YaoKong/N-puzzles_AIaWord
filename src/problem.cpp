#include <problem.h>
#include <direction.h>
static int _size = 0;
static PzlState goal;
static PzlState init;
static int count = 0;	// �Ѿ���������ĸ���

/*
 ��ʼһ��������
*/
void newProblem(byte goalstatus[], byte initstatus[], int size) {

	setStateSize(size);   //Ϊ����״̬����ȫ�ֵĹ�ģ��size
	setGoal(goalstatus);  //Ϊ����״̬����ȫ�ֵ�Ŀ��״̬

	_size = size;         //��������Ĺ�ģΪsize
	setPzlState(&goal, goalstatus);	//���õ�ǰ�����Ŀ��״̬
	setPzlState(&init, initstatus); //���õ�ǰ����ĳ�ʼ״̬	
	count++;
}

//״̬state�Ƿ���Ŀ��״̬
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
/// ��ӡ��ǰ����
/// </summary>
void printProblem() {
	drawState(&goal);
	printf("\n");

	drawState(&init);
	printf("\n");

	printf("%d\n", manhattan(init));
}

/// <summary>
/// astar����
/// </summary>
/// <param name="path"></param>
void astar(char* path, Heuristic _heuristics) {
	//Fix Me. ��Astar�㷨���������������Ž⣬������Ԥ�ȷ������µ�������:)
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
/// ���ӻ���·��������˫���弼����ʵ��Console�ַ�����Ķ���Ч��
/// </summary>
/// <param name="path">��·��</param>
void animation(char* path){

	initDoubleBuffer();	 //��ʼ��console˫������

//// ��ʼ��һ���ַ������� //// 
	int n_col = _size * 4 + 1;
	int n_row = _size * 2 + 1;
	int buffer_size = n_col * n_row;	
	char* buffer = (char*) malloc(sizeof(char) * buffer_size);
////////////////////////////
	
//// ������ʾ��·�� ////
	char caption[200];   //����
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
	free(buffer);   //�ͷŵ�buffer��ռ�ռ�
}

//СС���޸���һ����������������һ������
static void drawArrow(int size, char action, PzlState* state){
	//FixMe.
	char arrows[] = { '��', '-->','��', '<--' };
	char arrow = arrows[toDirection(action)];
	for (int i = 0; i < _size; i++) {
		//���ָ���
		for (int i = 0; i < _size; i++) {
			printf("+---");
		}
		printf("+\n");

		//�����Ӧ����
		for (int j = 0; j < _size; j++) {
			char c = getValue(state->status, i * _size + j) - 48;
			if (c == '0') c = arrow;

			printf("| %c ", c);
		}
		printf("|\n");
	}

	//���ָ���
	for (int i = 0; i < _size; i++) {
		printf("+---");
	}
	printf("+\n");
}

/// <summary>
/// ��ʾ��·��
/// </summary>
/// <param name="path">��·��</param>
void drawSolution(char* path){
	//Fix Me.
	//Ҫ�����drawState, drawArrow, nextState
	//
	//// ������ʾ��·�� ////
	char caption[200];   //����
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

		currState = child;	//���µ�ǰ״̬
		p++;
	}

}
