#ifndef _CELL_H
#define _CELL_H
struct Cell {
    int row;
    int col;
};

typedef struct Cell Cell;

extern void indexToCell(Cell* c, int index, int size);
extern void shiftCell(Cell* c, int offset[]);
extern int validCell(Cell* c, int size);
extern int cellManhattan(Cell* c1, Cell* c2);
#endif