#include <problem.h>

/// <summary>
/// 读入数字推盘的一个局面状态
/// </summary>
/// <param name="n">将牌的个数</param>
/// <returns></returns>
byte* getStatus(int n) {
    byte* bytes = (byte*)malloc(sizeof(byte) * n);
    for (int i = 0; i < n; i++) {
        scanf_s("%hhu", bytes + i);
    }
    return bytes;
}

/// <summary>
/// 求解第n个问题
/// </summary>
/// <param name="n">问题序号</param>
void solvePuzzle(int n)
{

/// 读入一个新的问题 ///
    int size;
    scanf_s("%d", &size);
    byte* init = getStatus(size * size);
    byte* goal = getStatus(size * size);
    newProblem(goal, init, size);
    free(goal); //释放掉goal和init所占用的空间
    free(init);

/// 求解该问题并动画模拟 ///
    char path[100];
    astar(path, manhattan); 
    drawSolution(path);
    //animation(path);
}

int main() {
    setMask(4);     //使用64位二进制表示数字推盘，每4个bit表示一个tile
    int num = 0;    //问题的个数
    scanf_s("%d", &num);
    for (int i = 0; i < num; i++) {
        printf("solution for problme no.%d\n", i+1);
        solvePuzzle(i);
    }
    return 0;
}


