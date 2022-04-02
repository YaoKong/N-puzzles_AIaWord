#include <generateDatabase.h>
#include <state.h>
#include <direction.h>

void initDatabase(PzlState* state, int size)
{
	if(size == aSize && goal == state->status && tables != NULL) {
		return;
	}


	if(tables != NULL) {
		tables->clear();
		partitions->clear();
	}
	else {
		tables = new std::vector<std::map<uLong, int> >;
	}

	aSize = size;
	goal = state->status;

	partitionDatabase(state, size);

	
	for(tableIndex = 0; tableIndex < partitions->size(); tableIndex++) {
		tables->push_back(std::map<uLong, int>());
		bfs(state);
	}
}

/// <summary>
/// ��Ŀ��״̬��ʼ����
/// </summary>
/// <param name="state"></param>
/// <returns>void</returns>
void bfs(PzlState* state)
{
	Node* currentState = new Node(*state, -1, NULL, 0, 0);


	std::map<uLong, int>* temp = &(*tables)[tableIndex];
	(*temp)[state->status] = 0;

	std::queue<Node*> tempQueue;
	tempQueue.push(currentState);

	while(!tempQueue.empty()) {
		currentState = tempQueue.front();
		tempQueue.pop();

		int numOfChild;
		int dummy[4];
		PzlState* children = nextStates(&currentState->state, &numOfChild, dummy);

		for(int i = 0; i < 4; i++) {
			if (!dummy[i]) continue;
			if(currentState->parent != NULL) {
				if ((i + 2) % 4 == currentState->parent->action) continue;
			}



			Node* tempNode = new Node(children[i], i, currentState, currentState->pathCost, currentState->hValue);

			Node* p = moveNode(tempNode);
			if(p != NULL) {
				tempQueue.push(p);
			}
		}
		delete[] children;
	}
}

/// <summary>
/// ��6Ϊ���飬��16��Ϊ6,6,3
/// </summary>
/// <param name="size">�����ģ</param>
void partitionDatabase(PzlState* state, int size)
{

	emptyIndex = state->blankPos;

	int num = size * size;	//���������
	num = num % 6 ? (num / 6) + 1 : (num / 6);
	int count = 0;
	byte* status = getValues(state->status);


	partitions = new std::vector<std::map<int, bool> >(num);

	std::map<int, bool>* p = &(*partitions)[0];
	num = 0;

	for(int i = 0; i < size * size; i++) {
		if(i != state->blankPos) {
			if(count % 6 == 0) {
				p = &(*partitions)[num];
				for(int j = 0; j < size * size; j++) {
					(*p)[j] = false;
				}
				num++;
			}

			int index = status[i];
			(*p)[index] = true; //����ÿ�����黬�������
			count++;
			
		}
	}
}


//��ǰ�ո���ƫ����offset���ƶ��Ƿ�Ϸ�
//blankPos: ��ǰ�ո����ڵ�λ����ţ�0~15��
int validMove(int blankPos, int offset[], int size) {
	//Fix Me.
	int row = blankPos / size + offset[1];
	int col = (blankPos % size) + offset[0];

	if (row < 0 || row >= size) return 0;
	if (col < 0 || col >= size) return 0;

	return 1;
}

Node* moveNode(Node* currentState)
{
	PzlState state = currentState->state;
	// if(!validMove(state.blankPos, getOffsets(currentState->action), aSize)) return NULL;

	PzlState child;
	nextState(&state, currentState->action, &child);	//�ƶ�state����һ�����
	int hValue = currentState->hValue;





	//��ӵ�ǰ״̬������
	std::map<int, bool>& p = (*partitions)[tableIndex];
	if( p[child.blankPos]) {	//�������������λ��
		p[child.blankPos] = false;
		p[state.blankPos] = true;
		hValue++;
	}

	Node* nState = new Node(child, -1, currentState, currentState->pathCost + 1, hValue);

	std::map<uLong, int>& table = (*tables)[tableIndex];
	if(table.count(child.status) == 0 || (table)[child.status] > nState->hValue) {
		(table)[child.status] = hValue;
	}

	return nState;
}
