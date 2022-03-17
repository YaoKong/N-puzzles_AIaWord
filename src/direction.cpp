#include <direction.h>
#define MAX_DIR 4

//���������ϣ��� ��4�������(��ƫ��������ƫ����)
static int offsets[MAX_DIR][2] = {
    { 0, -1 }, { 1, 0 }, {  0, 1 }, { -1,  0 }
};

static const char* arrows[2][MAX_DIR] = {
    {"�� ", "-->", " ��", "<--"},
    {" ��", "-->", "�� ", "<--"}
};


//���ݴ�������ַ�����ȡ��Ӧ��ö��ֵ
int toDirection(char d) {
    if (d == 'N') return 0;
    if (d == 'E') return 1;
    if (d == 'S') return 2;
    if (d == 'W') return 3;
    return -1;
}

int turn(int d, int clockwise){
    if (!clockwise)
        return (d + MAX_DIR - 1) % MAX_DIR;
    else
        return (d + 1) % MAX_DIR;
}

int* getOffsets(int d){
    return offsets[d];
}

const char* toString(int d, int clockwise){
    return arrows[clockwise][d];
}