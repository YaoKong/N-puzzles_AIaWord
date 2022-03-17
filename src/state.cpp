#include <state.h>
#include <direction.h>
#include <string.h>
//对于同一个问题的所有状态，其阶数和目标状态都是相同的，
static int _size = 0;  //数字推盘的边长 3， 4
static byte* posInGoal = NULL; //4阶：指向16个byte连续数据区（空格0以及1~15在目标状态中的位置）的指针

//设置State模块的全局变量: size (数字推盘的边长)，
//为所有的状态共享
void setStateSize(int size) {
    _size = size;
}

/// <summary>
/// 设置State模块的全局变量：目标状态中各个将牌的位置
/// </summary>
/// <param name="goalstatus"></param>
void setGoal(byte* goalstatus) {
    posInGoal = goalstatus;
    //Fix Me.
}

//获取数字推盘中空格的位置(序号从0开始); static，模块的私有函数
static int getBlankPos(byte status[]) {
    //Fix Me.
    for(int i = 0; i < _size * _size; i++) {
        if (status[i] == 0) return i;
    	
    }
    return -1;
}

//将数字推盘的状态数组转换为状态结构体
void setPzlState(PzlState* state, byte status[]) {
    state->status = getBitRep(status, _size * _size);
    state->blankPos = getBlankPos(status);
}


/// <summary>
/// 将位置index上的将牌滑到空格位置，返回新的64位二进制
/// static，模块私有函数
/// </summary>
/// <param name="status">当前状态</param>
/// <param name="blankPos">当前空格的位置</param>
/// <param name="index">空格移动的目标位置</param>
/// <returns>空格移动以后，新状态的64位二进制表示</returns>
static uLong moveTile(uLong status, int blankPos, int index) {
    //Fix Me.
    status = setValue(status, blankPos, getValue(status, index));
    status = resetZero(status, index);
    return status;
}

//计算两个单元格的曼哈顿距离
//i，j为单元格的序号（例如：0~15）
static int singleManhattan(int i, int j) {
    //Fix Me.
    return 0;
}

/// <summary>
/// 计算状态state与目标状态的曼哈顿距离
/// </summary>
/// <param name="state">当前状态</param>
/// <returns>当前状态state到目标状态的曼哈顿距离</returns>
int manhattan(const PzlState& state) {
    int manhattan = 0;
    //Fix Me.
    return manhattan;
}

/// <summary>
/// 计算状态state与目标状态的汉明距离，也即不在位将牌的个数
/// </summary>
/// <param name="state"></param>
/// <returns>当前状态state到目标状态的汉明距离</returns>
int hamming(const PzlState& state){
    int hamming = 0;
    //Fix Me.
    return hamming;
}

/// <summary>
/// 通过disjoint pattern计算状态state与目标状态的距离
/// </summary>
/// <param name="state"></param>
/// <returns>当前状态state到目标状态的距离</returns>
int disjoint(const PzlState& state){
    int disjoint = 0;
    //Fix Me.
    return disjoint;
}

//当前空格以偏移量offset的移动是否合法
//blankPos: 当前空格所在的位置序号（0~15）
static int validMove(int blankPos, int offset[]) {
    //Fix Me.
    return 0;
}

/// <summary>
/// 当前状态在执行action后的后继状态
/// </summary>
/// <param name="state">当前状态，in</param>
/// <param name="action">所采取的动作 in</param>
/// <param name="child">后继状态 out</param>
void nextState(PzlState* state, int action, PzlState* child) {
    
    //Fix Me. 
    //要求调用moveTile函数
    child->blankPos = state->blankPos +  getOffsets(action)[1] * _size + getOffsets(action)[0]; //后继状态的空格位置
    child->status = moveTile(state->status, state->blankPos, child->blankPos);  //获得后继状态
}

/*
 当前状态state的所有可行的后继状态
   参数
     state：当前状态
     numOfChild: 可行的后继状态的个数
   返回值：所有后继状态的数组
*/
PzlState* nextStates(PzlState* state, int* numOfChild) {
    
    //Fix Me.
    //要求调用nextState函数a
}

/// <summary>
/// 计算结点的奇偶性
/// size为奇数时: 所有将牌之间的逆序对数之和的奇偶性
/// size为偶数时: 所有将牌之间的逆序对数之和再加上空格所在行号的奇偶性
/// </summary>
/// <returns>状态state相对于目标状态的奇偶性</returns>
int getParity(PzlState* state) {
    
    int inversions = 0;

    //Fix Me.

    return inversions;
}

/// <summary>
/// 
/// </summary>
/// <param name="buffer">存放状态的缓冲区</param>
/// <param name="state">要存放的状态</param>
/// <param name="row">该状态的第row行</param>
/// <param name="start">状态的第row行，在缓冲区中的起始位置</param>
///     将 “| 8 | # | 7 |”, 用‘|’包围的数字或空格#, 写入缓冲区
/// <returns>写入缓冲区的字符的个数</returns>
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
/// 将分割线写入缓冲区
/// </summary>
/// <param name="buffer"></param>
/// <returns>写入缓冲区的字符的个数</returns>
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
/// 将当前状态的字符串表示写入buffer. 用'#'代表空格
/// +---+---+---+
/// | 1 | 2 | 3 |
/// +---+---+---+
/// | 4 | 5 | 6 |
/// +---+---+---+
/// | 7 | 8 | # |
/// +---+---+---+
/// </summary>
/// <param name="state">当前状态</param>
/// <param name="buffer">写入目的buffer</param>
/// <param name="buffer_size">buffer的容量</param>
/// <returns>写入state后的buffer</returns>
char* toCharBuffer(PzlState * state, char* buffer, int buffer_size) {
    int k = 0;
    //Fix Me. 要求调用rowToBuffer和lineToBuffer函数

    for(int i = 0; i < _size; i++) {
        k += lineToBuffer(buffer + k);  //写入一行分隔符
        
        k += rowToBuffer(buffer + k, i * _size, state, i);  //写入一行数字

    }
    lineToBuffer(buffer + k);   //末尾补上分隔符
    return buffer;
}

///
///打印行分割线
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
/// 打印状态的字符串表示
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
    //Fix Me. 要求调用drawLine
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