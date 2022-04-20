#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------
extern int unsolved;
extern int SIZE_ROWS;
extern int SIZE_COLS;
//-------------------------------------------------------
typedef struct Sudoku
{
    struct Square ***squares;
    struct Box **boxes;

} Sudoku;
//-------------------------------------------------------
typedef struct Box
{
    struct Square **squares;
    struct Box *next;
    int num;
    int check[9];
    int solvable = 9;

} Box;
//-------------------------------------------------------
typedef struct Square
{
    int number;
    int check[9];
    int solvable;
    Box *box;
    int row;
    int col;

} Square;
//-------------------------------------------------------
int **create();
void print(Square ***sudoku);
Sudoku *setUp(int **sudoku);

Sudoku *createSudoku(Square ***squares, Box **boxes);

int solveSquare(Square *square);

int check(Square ***ThisSudoku, Box **boxes);
int update(Square ***ThisSudoku, int row, int col);

Box **createBoxes();
int updateBoxes(Square ***ThisSudoku, int row, int col);
int boxCheck(Square ***sudoku, Box **boxes);

int checkRows(Square ***sudoku, Box **boxes);
//-------------------------------------------------------
#endif // HEADER_H_INCLUDED
