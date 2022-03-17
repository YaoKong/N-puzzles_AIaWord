#include <Windows.h>

static HANDLE consoleBuffers[2]; //����������

/// <summary>
/// ������n*m���ַ���buffer����n��m�е���ʽ�������Console������
/// </summary>
/// <param name="buffer">�ַ�������</param>
/// <param name="n">����</param>
/// <param name="m">����</param>
/// <param name="caption">����ı���</param>
void showBuffer(char* buffer, int n, int m, char* caption) {
	static int flag = 0;	//����ʹ������buffer
	DWORD bytes = 0;
	COORD coord = { 2, 0 };
	WriteConsoleOutputCharacterA(consoleBuffers[flag], caption, strlen(caption), coord, &bytes);
	for (int i = 0; i < m; i++) {
		coord.Y = i + 1;
		WriteConsoleOutputCharacterA(consoleBuffers[flag], buffer + i * n, n, coord, &bytes);
	}
	//��д���壬������ΪActive��˳���ܷ���
	SetConsoleActiveScreenBuffer(consoleBuffers[flag]);
	flag = ~flag; //����ʹ��Buffer
	Sleep(500);
}

/// <summary>
/// ��ʼ������������
/// </summary>
void initDoubleBuffer() {
	//���������������Ĺ��
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	//�����µĿ���̨������
	for (int i = 0; i < 2; i++) {
		consoleBuffers[i] = CreateConsoleScreenBuffer(
			GENERIC_WRITE,//������̿�����������д����
			FILE_SHARE_WRITE,//���建�����ɹ���дȨ��
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL
		);
		SetConsoleCursorInfo(consoleBuffers[i], &cci);
	}
}
