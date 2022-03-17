#include <state.h>
#include <direction.h>
#include <string.h>
//����ͬһ�����������״̬���������Ŀ��״̬������ͬ�ģ�
static int _size = 0;  //�������̵ı߳� 3�� 4
static byte* posInGoal = NULL; //4�ף�ָ��16��byte�������������ո�0�Լ�1~15��Ŀ��״̬�е�λ�ã���ָ��

//����Stateģ���ȫ�ֱ���: size (�������̵ı߳�)��
//Ϊ���е�״̬����
void setStateSize(int size) {
    _size = size;
}

/// <summary>
/// ����Stateģ���ȫ�ֱ�����Ŀ��״̬�и������Ƶ�λ��
/// </summary>
/// <param name="goalstatus"></param>
void setGoal(byte* goalstatus) {
    posInGoal = goalstatus;
    //Fix Me.
}

//��ȡ���������пո��λ��(��Ŵ�0��ʼ); static��ģ���˽�к���
static int getBlankPos(byte status[]) {
    //Fix Me.
    for(int i = 0; i < _size * _size; i++) {
        if (status[i] == 0) return i;
    	
    }
    return -1;
}

//���������̵�״̬����ת��Ϊ״̬�ṹ��
void setPzlState(PzlState* state, byte status[]) {
    state->status = getBitRep(status, _size * _size);
    state->blankPos = getBlankPos(status);
}


/// <summary>
/// ��λ��index�ϵĽ��ƻ����ո�λ�ã������µ�64λ������
/// static��ģ��˽�к���
/// </summary>
/// <param name="status">��ǰ״̬</param>
/// <param name="blankPos">��ǰ�ո��λ��</param>
/// <param name="index">�ո��ƶ���Ŀ��λ��</param>
/// <returns>�ո��ƶ��Ժ���״̬��64λ�����Ʊ�ʾ</returns>
static uLong moveTile(uLong status, int blankPos, int index) {
    //Fix Me.
    status = setValue(status, blankPos, getValue(status, index));
    status = resetZero(status, index);
    return status;
}

//����������Ԫ��������پ���
//i��jΪ��Ԫ�����ţ����磺0~15��
static int singleManhattan(int i, int j) {
    //Fix Me.
    return 0;
}

/// <summary>
/// ����״̬state��Ŀ��״̬�������پ���
/// </summary>
/// <param name="state">��ǰ״̬</param>
/// <returns>��ǰ״̬state��Ŀ��״̬�������پ���</returns>
int manhattan(const PzlState& state) {
    int manhattan = 0;
    //Fix Me.
    return manhattan;
}

/// <summary>
/// ����״̬state��Ŀ��״̬�ĺ������룬Ҳ������λ���Ƶĸ���
/// </summary>
/// <param name="state"></param>
/// <returns>��ǰ״̬state��Ŀ��״̬�ĺ�������</returns>
int hamming(const PzlState& state){
    int hamming = 0;
    //Fix Me.
    return hamming;
}

/// <summary>
/// ͨ��disjoint pattern����״̬state��Ŀ��״̬�ľ���
/// </summary>
/// <param name="state"></param>
/// <returns>��ǰ״̬state��Ŀ��״̬�ľ���</returns>
int disjoint(const PzlState& state){
    int disjoint = 0;
    //Fix Me.
    return disjoint;
}

//��ǰ�ո���ƫ����offset���ƶ��Ƿ�Ϸ�
//blankPos: ��ǰ�ո����ڵ�λ����ţ�0~15��
static int validMove(int blankPos, int offset[]) {
    //Fix Me.
    return 0;
}

/// <summary>
/// ��ǰ״̬��ִ��action��ĺ��״̬
/// </summary>
/// <param name="state">��ǰ״̬��in</param>
/// <param name="action">����ȡ�Ķ��� in</param>
/// <param name="child">���״̬ out</param>
void nextState(PzlState* state, int action, PzlState* child) {
    
    //Fix Me. 
    //Ҫ�����moveTile����
    child->blankPos = state->blankPos +  getOffsets(action)[1] * _size + getOffsets(action)[0]; //���״̬�Ŀո�λ��
    child->status = moveTile(state->status, state->blankPos, child->blankPos);  //��ú��״̬
}

/*
 ��ǰ״̬state�����п��еĺ��״̬
   ����
     state����ǰ״̬
     numOfChild: ���еĺ��״̬�ĸ���
   ����ֵ�����к��״̬������
*/
PzlState* nextStates(PzlState* state, int* numOfChild) {
    
    //Fix Me.
    //Ҫ�����nextState����a
}

/// <summary>
/// ���������ż��
/// sizeΪ����ʱ: ���н���֮����������֮�͵���ż��
/// sizeΪż��ʱ: ���н���֮����������֮���ټ��Ͽո������кŵ���ż��
/// </summary>
/// <returns>״̬state�����Ŀ��״̬����ż��</returns>
int getParity(PzlState* state) {
    
    int inversions = 0;

    //Fix Me.

    return inversions;
}

/// <summary>
/// 
/// </summary>
/// <param name="buffer">���״̬�Ļ�����</param>
/// <param name="state">Ҫ��ŵ�״̬</param>
/// <param name="row">��״̬�ĵ�row��</param>
/// <param name="start">״̬�ĵ�row�У��ڻ������е���ʼλ��</param>
///     �� ��| 8 | # | 7 |��, �á�|����Χ�����ֻ�ո�#, д�뻺����
/// <returns>д�뻺�������ַ��ĸ���</returns>
static int rowToBuffer(char* buffer, int start, PzlState* state, int row) {
    int k = 0;
    //Fix Me.
    for(int i = 0; i < _size; i++) {
        char c = getValue(state->status, start + i) - 48;
        if (c == '0') c = '#';

        *buffer = '|';
        buffer++;
        for(int j = 0; j < 3; j++) {
	        if(j == 1) {
                *buffer = c;
                buffer++;
	        }
            else {
                *buffer = ' ';
                buffer++;
            }
        }
        k += 4;
    }
    *buffer = '|';
    buffer++;
    *buffer = '\n';
    buffer++;
    k += 2;

    return k;
}

/// <summary>
/// ���ָ���д�뻺����
/// </summary>
/// <param name="buffer"></param>
/// <returns>д�뻺�������ַ��ĸ���</returns>
static int lineToBuffer(char* buffer) {
    int k = 0;
    //Fix Me.
    for(int i = 0; i < _size; i++) {
        char* p = buffer;
        *buffer = '+';
        buffer++;

        for(int j = 0; j < 3; j++) {
            *(p + j) = '-';
        }

        buffer += 4;
        k += 4;
    }
    *buffer = '+';
    buffer++;
    *buffer = '\n';

    k+= 2;
    return k;
}

/// <summary>
/// ����ǰ״̬���ַ�����ʾд��buffer. ��'#'����ո�
/// +---+---+---+
/// | 1 | 2 | 3 |
/// +---+---+---+
/// | 4 | 5 | 6 |
/// +---+---+---+
/// | 7 | 8 | # |
/// +---+---+---+
/// </summary>
/// <param name="state">��ǰ״̬</param>
/// <param name="buffer">д��Ŀ��buffer</param>
/// <param name="buffer_size">buffer������</param>
/// <returns>д��state���buffer</returns>
char* toCharBuffer(PzlState * state, char* buffer, int buffer_size) {
    int k = 0;
    //Fix Me. Ҫ�����rowToBuffer��lineToBuffer����

    for(int i = 0; i < _size; i++) {
        k += lineToBuffer(buffer + k);  //д��һ�зָ���
        
        k += rowToBuffer(buffer + k, i * _size, state, i);  //д��һ������

    }
    lineToBuffer(buffer + k);   //ĩβ���Ϸָ���
    return buffer;
}

///
///��ӡ�зָ���
/// +---+---+---+
///
static void drawLine() {
    //Fix Me.
    for(int i = 0; i < _size; i++) {
        printf("+---");
    }
    printf("+\n");
}

/// <summary>
/// ��ӡ״̬���ַ�����ʾ
/// +---+---+---+
/// | 1 | 2 | 3 |
/// +---+---+---+
/// | 4 | 5 | 6 |
/// +---+---+---+
/// | 7 | 8 | # |
/// +---+---+---+
/// </summary>
/// <param name="state"></param>
void drawState(PzlState* state) {
    //Fix Me. Ҫ�����drawLine
    for(int i = 0; i < _size; i++) {
        drawLine();
	    for(int j = 0; j < _size; j++) {
            char c = getValue(state->status, i * _size + j) - 48;
            if (c == '0') c = '#';

            printf("| %c ", c);
	    }
        printf("|\n");
    }
    drawLine();
}