//-------------------------------------------------------
/// DATE:    2022.04
/// NAME:    Tadas Baltrūnas
/// LSP:     2110535
/// FACULTY: PROGRAMŲ SISTEMOS
/// GROUP:   5
/// PROGRAM: 8 - Parašyti programą, sprendžiančią Sudoku.
//-------------------------------------------------------
#include "header.h"
//-------------------------------------------------------
int unsolved = 81;
int SIZE_ROWS = 9;
int SIZE_COLS = 9;
//-------------------------------------------------------
int main()
{
    int **sudoku;
    int progress = 0;
    Sudoku *ThisSudoku;

    sudoku = create();

    ThisSudoku = setUp(sudoku);

    print(ThisSudoku->squares);

    while(unsolved > 0)
    {
        progress = check(ThisSudoku->squares, ThisSudoku->boxes);

        if(progress == 0)
        {
            break;
        }
    }

    printf("\n\n");

    print(ThisSudoku->squares);

    return 0;
}
//-------------------------------------------------------


/*  BENCHMARK

    Sudoku solving program that solves sudoku with brute force method execution time:


    Time Complexity: O(m^(n*n))= O(9^(n*n)) n - number of possibilities for one square ; m - number of empty squares

    array0 - 174,580 s
    array1 - 219,944 s
    array2 - 63,105 s
    array3 - 0,022 s

    Sudoku solving program that solves sudoku with algorithm method execution time:

    array0 - 0,034 s
    array1 - 0,036 s
    array2 - 0,037 s
    array3 - 0,035 s

    Time Complexity: O(n^m) = O(9^m) n - number of possibilities for one square ; m - number of empty squares

    COMPARISON:

    1)Brute force

        Best case    - 0,022 s
        Average case - 114.412 s
        Worst case   - 219,944 s

    2)Algorithm

        Best case    - 0,034 s
        Average case - 0,035 s
        Worst case   - 0,037 s

    RESULTS:

        With BEST case brute force method works FASTER approximately 1,54 times than my algorithm

        With AVERAGE case brute force method works SLOWER approximately 3268,91 times than my algorithm

        With WORST case brute force method works SLOWER approximately 5944,43 times than my algorithm

*/
