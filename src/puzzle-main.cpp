#include <problem.h>
#include <performance.h>

#include "generateDatabase.h"
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
    printf("Plese input problem size:");
    scanf_s("%d", &size);
    byte* init = getStatus(size * size);
    byte* goal = getStatus(size * size);
    newProblem(goal, init, size);


/// �������Ⲣ����ģ�� ///
    char path[100];
    PerformanceTester pt;

    pt.Start();
    //��������Ϊ�����پ���
    // astar(path, manhattan);
    idaStar(path, manhattan);
    pt.Stop();
    pt.OutputToFile("astar_manhattan.csv", path, init, goal, size);
    // pt.OutputToFile("idaStar_manhattan.csv", path, init, goal, size);

    //��������Ϊ���ཻ���ݿ����
 //    initDatabase(getGoal(), size);
	// pt.Start();
 //    astar(path, disjoint);
    // idaStar(path, disjoint);
    // pt.Stop();
    // pt.OutputToFile("astar_disjoint.csv", path, init, goal, size);
    // pt.OutputToFile("idaStar_disjoint.csv", path, init, goal, size);



    // drawSolution(path);
    // animation(path);

	free(goal); //�ͷŵ�goal��init��ռ�õĿռ�
    free(init);
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

//�ٷ��������£�
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

