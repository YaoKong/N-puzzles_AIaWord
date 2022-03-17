#include <cell.h>
#include <stdlib.h>

/*
	将index转换为行列坐标，行列坐标均从0开始
*/
void indexToCell(Cell* c, int index, int size) {
	c->row = index / size;
	c->col = index % size;
}

void shiftCell(Cell* c, int offset[]) {
	c->row += offset[1];
	c->col += offset[0];
}

int cellToIndex(Cell* c, int size) {
	return c->row * size + c->col;
}

int validCell(Cell* c, int size) {
	return c->row >= 0 && c->row < size&&
		c->col >= 0 && c->col < size;
}

//求两个Cell的曼哈顿距离
int cellManhattan(Cell* c1, Cell* c2) {
	return abs(c1->row - c2->row) + abs(c1->col - c2->col);
}
