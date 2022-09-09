#include <problem.h>
#include <performance.h>

#include "generateDatabase.h"
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
    printf("Plese input problem size:");
    scanf_s("%d", &size);
    byte* init = getStatus(size * size);
    byte* goal = getStatus(size * size);
    newProblem(goal, init, size);


/// 求解该问题并动画模拟 ///
    char path[100];
    PerformanceTester pt;

    pt.Start();
    //启发函数为曼哈顿距离
    // astar(path, manhattan);
    idaStar(path, manhattan);
    pt.Stop();
    pt.OutputToFile("astar_manhattan.csv", path, init, goal, size);
    // pt.OutputToFile("idaStar_manhattan.csv", path, init, goal, size);

    //启发函数为不相交数据库距离
 //    initDatabase(getGoal(), size);
	// pt.Start();
 //    astar(path, disjoint);
    // idaStar(path, disjoint);
    // pt.Stop();
    // pt.OutputToFile("astar_disjoint.csv", path, init, goal, size);
    // pt.OutputToFile("idaStar_disjoint.csv", path, init, goal, size);



    // drawSolution(path);
    // animation(path);

	free(goal); //释放掉goal和init所占用的空间
    free(init);
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

//官方代码如下：
//
// #include <SFML/Graphics.hpp>
//
// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);
//
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//
//         window.clear();
//         window.draw(shape);
//         window.display();
//     }
//
//     return 0;
// }

