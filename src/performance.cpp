#include <performance.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

uLong getRandomState(int _size)
{
	int n = _size * _size;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, n - 1);

	byte* temp = new byte[n];
	int len = 0;
	for(int i = 0; i < n; i++) {
		while(len < n) {
			int num = dis(gen);
			bool flag = true;
			for(int j = 0; j < len; j++) {
				if((int)temp[j] == num) {
					flag = false;
					break;
				}
			}
			if(flag) {
				temp[len++] = num + 48;
			}
		}
	}
	uLong state = getBitRep(temp, n);

	delete[]temp;
	return state;

}

void PerformanceTester::Start()
{
	start = clock();
}

void PerformanceTester::Stop()
{
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("  运行时间:%lf秒\n", totaltime);


}

void PerformanceTester::OutputToFile(std::string filename, std::string path, byte* init, byte* goal, int size)
{
	// 写文件
	std::string initState;
	std::string goalState;
	for(int i = 0; i < size * size; i++) {
		initState.append(std::to_string(init[i]));
		goalState.append(std::to_string(goal[i]));
	}


	std::ofstream outFile;
	outFile.open(filename, std::ios::in);
	if(!outFile) {
		outFile.close();
		outFile.open(filename, std::ios::app);
		outFile << "初始状态," << "目标状态," <<"输出路径," << "运行时间(s)" << std::endl;
	}
	else {
		outFile.close();
		outFile.open(filename, std::ios::app);
	}
	outFile << initState << ',' << goalState << ',' <<path << ',' << totaltime << std::endl;
	outFile.close();
}
