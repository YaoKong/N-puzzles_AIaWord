#ifndef _DIRECTION_H
#define _DIRECTION_H
//���ݴ�������ַ�����ȡ��Ӧ��ö��ֵ
extern int toDirection(char d);
//��ǰ����˳ʱ�����ʱ��ת90��
extern int turn(int d, int clockwise);
//��ȡ�ص�ǰ����ǰ��һ��ʱ�����е�ƫ����
extern int* getOffsets(int d);
//���ط���d���ַ�����ʾ���ϡ��µ�˳ʱ�����ʱ���ʾ������ͬ
extern const char* toString(int d, int clockwise);
#endif