#include <problem.h>

/// <summary>
/// �����������̵�һ������״̬
/// </summary>
/// <param name="n">���Ƶĸ���</param>
/// <returns></returns>
byte* getStatus(int n) {
    byte* bytes = (byte*)malloc(sizeof(byte) * n);
    for (int i = 0; i < n; i++) {
        scanf_s("%hhu", bytes + i);
    }
    return bytes;
}

/// <summary>
/// ����n������
/// </summary>
/// <param name="n">�������</param>
void solvePuzzle(int n)
{

/// ����һ���µ����� ///
    int size;
    scanf_s("%d", &size);
    byte* init = getStatus(size * size);
    byte* goal = getStatus(size * size);
    newProblem(goal, init, size);
    free(goal); //�ͷŵ�goal��init��ռ�õĿռ�
    free(init);

/// �������Ⲣ����ģ�� ///
    char path[100];
    astar(path, manhattan); 
    drawSolution(path);
    //animation(path);
}

int main() {
    setMask(4);     //ʹ��64λ�����Ʊ�ʾ�������̣�ÿ4��bit��ʾһ��tile
    int num = 0;    //����ĸ���
    scanf_s("%d", &num);
    for (int i = 0; i < num; i++) {
        printf("solution for problme no.%d\n", i+1);
        solvePuzzle(i);
    }
    return 0;
}


