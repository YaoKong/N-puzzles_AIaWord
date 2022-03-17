#include <Windows.h>

static HANDLE consoleBuffers[2]; //两个缓冲区

/// <summary>
/// 将具有n*m个字符的buffer，按n行m列的形式，输出到Console缓冲区
/// </summary>
/// <param name="buffer">字符缓冲区</param>
/// <param name="n">行数</param>
/// <param name="m">列数</param>
/// <param name="caption">输出的标题</param>
void showBuffer(char* buffer, int n, int m, char* caption) {
	static int flag = 0;	//交替使用两个buffer
	DWORD bytes = 0;
	COORD coord = { 2, 0 };
	WriteConsoleOutputCharacterA(consoleBuffers[flag], caption, strlen(caption), coord, &bytes);
	for (int i = 0; i < m; i++) {
		coord.Y = i + 1;
		WriteConsoleOutputCharacterA(consoleBuffers[flag], buffer + i * n, n, coord, &bytes);
	}
	//先写缓冲，在设置为Active。顺序不能反。
	SetConsoleActiveScreenBuffer(consoleBuffers[flag]);
	flag = ~flag; //交替使用Buffer
	Sleep(500);
}

/// <summary>
/// 初始化两个缓冲区
/// </summary>
void initDoubleBuffer() {
	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	//创建新的控制台缓冲区
	for (int i = 0; i < 2; i++) {
		consoleBuffers[i] = CreateConsoleScreenBuffer(
			GENERIC_WRITE,//定义进程可以往缓冲区写数据
			FILE_SHARE_WRITE,//定义缓冲区可共享写权限
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL
		);
		SetConsoleCursorInfo(consoleBuffers[i], &cci);
	}
}
