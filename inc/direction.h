#ifndef _DIRECTION_H
#define _DIRECTION_H
//根据代表方向的字符，获取对应的枚举值
extern int toDirection(char d);
//当前方向，顺时针或逆时针转90度
extern int turn(int d, int clockwise);
//获取沿当前方向前进一步时，行列的偏移量
extern int* getOffsets(int d);
//返回方向d的字符串表示，上、下的顺时针和逆时针表示有所不同
extern const char* toString(int d, int clockwise);
#endif