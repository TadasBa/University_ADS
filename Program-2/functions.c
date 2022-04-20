#include "header.h"
//-------------------------------------------------------

Sudoku *createSudoku(Square ***squares, Box **boxes)
{
    /* Function to  */

    Sudoku *sudoku;

    sudoku = malloc(sizeof(Sudoku));

    sudoku->squares = squares;
    sudoku->boxes = boxes;

    return sudoku;
}
//-------------------------------------------------------
Sudoku *setUp(int **sudoku)
{
    Square ***ThisSudoku;
    Box **boxes;
    int currentBox = 0;

    ThisSudoku = (Square***)malloc(sizeof(Square**)*9);

    boxes = createBoxes();

    for(int i=0; i<SIZE_ROWS; i++)
    {
        ThisSudoku[i] = (Square**)malloc(sizeof(Square*)*9);

        for(int j=0; j<SIZE_COLS; j++)
        {
            ThisSudoku[i][j] = (Square*)malloc(sizeof(Square)*9);

            ThisSudoku[i][j]->number = sudoku[i][j];

            ThisSudoku[i][j]->row = i;
            ThisSudoku[i][j]->col = j;
            ThisSudoku[i][j]->solvable = 9;

            boxes[currentBox]->squares[boxes[currentBox]->num] = ThisSudoku[i][j];
            ThisSudoku[i][j]->box = boxes[currentBox];
            boxes[currentBox]->num++;

            for(int k=0; k<9; k++)
            {
                ThisSudoku[i][j]->check[k] = 0;
            }

            if(j == 2 || j == 5)
            {
                currentBox++;
            }
        }

        currentBox -= 2;
        if(i == 2)
        {
            currentBox = 3;
        }
        if(i == 5)
        {
            currentBox = 6;
        }

    }

    for(int i=0; i<SIZE_ROWS; i++)
    {

        for(int j=0; j<SIZE_COLS; j++)
        {
            if(ThisSudoku[i][j]->number != 0)
            {
                ThisSudoku[i][j]->solvable = 0;
                update(ThisSudoku, i, j);
                updateBoxes(ThisSudoku, i, j);
                unsolved--;
            }
        }
    }

    return createSudoku(ThisSudoku, boxes);
}
//-------------------------------------------------------
int update(Square ***ThisSudoku, int row, int col)
{
    int index = ThisSudoku[row][col]->number;

    for(int i=0; i<SIZE_ROWS; i++)
    {
        if(ThisSudoku[i][col]->check[index-1] == 0)
        {
            ThisSudoku[i][col]->solvable--;

        }
        ThisSudoku[i][col]->check[index-1] = 1;
    }

    for(int i=0; i<SIZE_COLS; i++)
    {
        if(ThisSudoku[row][i]->check[index-1] == 0)
        {
            ThisSudoku[row][i]->solvable--;

        }
        ThisSudoku[row][i]->check[index-1] = 1;
    }

}
//-------------------------------------------------------
int checkRows(Square ***sudoku, Box **boxes)
{
    int sum[9], place[9];

    // initialize sum and place to 0
    for(int i=0; i<9; i++)
    {
        place[i] = 0;
        sum[i] = 0;
    }

    // loop through all rows
    for(int i=0; i<9; i++)
    {

        // loop through each square in the row
        for(int j=0; j<9; j++)
        {
            if(sudoku[i][j]->number != 0)
            {
                continue;
            }

            // loop through all possibles
            for(int k=0; k<9; k++)
            {
                // check if number (k) is possible
                if(sudoku[i][j]->check[k] == 0)
                {
                    sum[k]++;
                    place[k] = j;
                }
            }
        }

        for(int z=0; z<9; z++)
        {
            if(sum[z] == 1)
            {
                sudoku[i][place[z]]->number = z + 1;
                sudoku[i][place[z]]->solvable = 0;
                unsolved--;

                update(sudoku, i, place[z]);
                updateBoxes(sudoku, i, place[z]);
                return 1;
            }
        }
    }

    return 0;
}
//-------------------------------------------------------
int updateBoxes(Square ***ThisSudoku, int row, int col)
{
    int number = ThisSudoku[row][col]->number;
    Box *box;
    box = ThisSudoku[row][col]->box;

    for(int i=0; i<9; i++)
    {
        if(box->squares[i]->check[number - 1] == 0)
        {
            box->squares[i]->solvable--;
            box->squares[i]->check[number - 1] = 1;
        }
    }
}
//-------------------------------------------------------
int boxCheck(Square ***sudoku, Box **boxes)
{
    int count, temp;

    // loop through boxes
    for(int i=0; i<9; i++)
    {
        // loop through possible array
        for(int j=0; j<9; j++)
        {
            count = 0;

            // loop through squares
            for(int k=0; k<9; k++)
            {
                if(boxes[i]->squares[k]->number != 0)
                {
                    continue;
                }
                if(boxes[i]->squares[k]->check[j] == 0)
                {
                    count++;
                    temp = k;
                }
                if(count == 2)
                {
                    break;
                }
            }

            if(count == 1)
            {
                boxes[i]->squares[temp]->number = j + 1;
                unsolved--;
                boxes[i]->squares[temp]->solvable = 0;

                update(sudoku, boxes[i]->squares[temp]->row, boxes[i]->squares[temp]->col);

                return 1;
            }
        }
    }

    return 0;
}
//-------------------------------------------------------
int check(Square ***ThisSudoku, Box **boxes)
{
    for(int i=0; i<SIZE_ROWS; i++)
    {
        for(int j=0; j<SIZE_COLS; j++)
        {
            if(ThisSudoku[i][j]->solvable == 1)
            {
                solveSquare(ThisSudoku[i][j]);
                update(ThisSudoku, i, j);
                updateBoxes(ThisSudoku, i, j);

                return 1;
            }
        }
    }

    if(boxCheck(ThisSudoku, boxes))
    {
        return 1;
    }

    return checkRows(ThisSudoku, boxes);
}
//-------------------------------------------------------
int solveSquare(Square *square)
{
    for(int i=0; i<SIZE_ROWS; i++)
    {
        if(square->check[i] == 0)
        {
            square->number = i + 1;
            square->solvable = 0;
            unsolved--;
        }
    }
}
//-------------------------------------------------------
Box **createBoxes()
{
    Box **boxes;

    boxes = malloc(sizeof(Box*)*9);

    for(int i=0; i<9; i++)
    {
        boxes[i] = malloc(sizeof(Box));
        boxes[i]->squares = malloc(sizeof(Square*)*9);
        boxes[i]->num = 0;
        boxes[i]->solvable = 9;

        for(int j=0; j<9; j++)
        {
            boxes[i]->check[j] = 0;
        }
    }

    return boxes;
}
//-------------------------------------------------------
int **create()
{
    /* Function to dynamically allocate and initialize 2D array which will contain sudoku data */

    int **sudoku;

    int array0[9][9] =
    {
        {0,0,0,   0,6,0,  0,0,0},
        {0,0,0,   4,0,3,  6,7,0},
        {0,0,5,   0,0,7,  0,0,0},

        {0,9,0,   0,0,0,  4,0,0},
        {1,0,0,   0,0,0,  9,0,3},
        {0,3,2,   0,0,0,  0,5,8},

        {0,1,0,   5,2,0,  0,9,7},
        {0,5,0,   0,0,9,  8,0,0},
        {0,0,0,   0,8,6,  2,0,0}
    };

    int array1[9][9] =
    {
        {0,0,7,   0,0,5,  0,0,9},
        {0,0,0,   0,0,8,  0,0,0},
        {2,0,5,   7,3,0,  0,0,0},

        {3,0,9,   2,1,0,  0,0,0},
        {0,0,0,   0,0,0,  0,0,4},
        {8,0,0,   0,9,3,  0,0,0},

        {0,7,0,   0,0,0,  3,0,0},
        {0,0,0,   0,0,0,  0,9,0},
        {0,0,2,   0,8,0,  6,0,1}
    };

    int array2[9][9] =
    {
        {0,3,0,   7,0,8,  0,0,0},
        {0,0,0,   0,0,0,  2,0,0},
        {0,0,4,   0,0,0,  0,7,1},

        {6,0,1,   0,0,0,  0,0,2},
        {7,0,0,   0,0,5,  0,0,0},
        {0,0,0,   0,0,0,  8,5,0},

        {0,0,3,   0,8,0,  0,0,0},
        {9,2,0,   0,6,0,  0,0,5},
        {1,0,0,   0,0,0,  9,0,6}
    };

    int array3[9][9] =
    {
        {0,3,6,   7,1,8,  5,9,4},
        {5,1,7,   9,3,4,  2,6,8},
        {8,9,4,   2,5,6,  3,7,1},

        {6,5,1,   8,9,3,  7,4,2},
        {7,8,9,   4,2,5,  6,1,3},
        {3,4,1,   6,7,1,  8,5,9},

        {4,6,3,   5,8,9,  1,2,7},
        {9,2,8,   1,6,7,  4,3,5},
        {1,7,5,   3,4,2,  9,8,6}
    };

    int arrayH[9][9] =
    {
        {0,8,0,   0,3,5,  6,0,0},
        {0,1,0,   0,0,0,  0,7,0},
        {0,0,2,   0,0,0,  0,0,4},

        {0,0,5,   0,1,0,  0,0,6},
        {9,0,0,   4,0,6,  0,0,7},
        {1,0,0,   0,7,0,  8,0,0},

        {2,0,0,   0,0,0,  3,0,0},
        {0,5,0,   0,0,0,  0,9,0},
        {0,0,3,   5,8,0,  0,6,0}
    };

    sudoku = (int**)malloc(sizeof(int*)*9);

    for(int i=0; i<SIZE_ROWS; i++)
    {
        sudoku[i] = (int*)malloc(sizeof(int)*9);

        for(int j=0; j<SIZE_COLS; j++)
        {
            sudoku[i][j] = array3[i][j];
        }
    }

    return sudoku;
}
//-------------------------------------------------------
void print(Square ***sudoku)
{
    /* Function to print sudoku */

    for(int i=0; i<SIZE_ROWS; i++)
    {
        if(i % 3 == 0 && i != 0)
        {
            printf(" ................................\n");
        }

        for(int j=0; j<SIZE_COLS; j++)
        {
            printf(" %d ", sudoku[i][j]->number);

            if((j+1) % 3 == 0 && j != 8)
            {
                printf(" : ");
            }
        }
        printf("\n");
    }
}
//-------------------------------------------------------
