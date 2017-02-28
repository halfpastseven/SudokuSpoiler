#include "mainwindow.h"
#include <QApplication>

/*#include <cstdio>
#include <fstream>
#include <iostream>
#include <QTime>
#include "sudoku.h"*/

/*char convertDigit (sudoku::cellNumber NUMBER){
    switch (NUMBER){
    case sudoku::ZERO: return ' ';
    case sudoku::N1:   return '1';
    case sudoku::N2:   return '2';
    case sudoku::N3:   return '3';
    case sudoku::N4:   return '4';
    case sudoku::N5:   return '5';
    case sudoku::N6:   return '6';
    case sudoku::N7:   return '7';
    case sudoku::N8:   return '8';
    case sudoku::N9:   return '9';
    }
    return 0;
}*/

//std::ofstream Debug ("Debug.txt");
/*
void printSdk (const sudoku& Puzzle){
    for (int row=0; row<9; row++) {
        for (int col=0; col<9; col++){
            char charToPrint = ' ';
            if (Puzzle.countCands(row,col)==1){
                charToPrint = '0'+sudoku::DigToNum(Puzzle.get(row,col));
            }
            std::cout<<charToPrint<<" ";
            if (col==2||col==5) std::cout<<" | ";
        }
        std::cout<<"\n";
        if (row==2||row==5) {
            for (int i=0; i<25; i++) std::cout<<"-";
            std::cout<<"\n";
        }
    }
    std::cout<<std::endl;
}*/

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}

    /** sudoku testing module **/
    
    /*int PuzzleNumbers[9][9]= {
        {0,0,0, 0,8,7, 0,4,6},
        {0,3,0, 0,0,6, 0,0,0},
        {0,0,2, 4,0,3, 5,1,0},
        
        {0,2,6, 0,0,0, 0,3,7},
        {1,0,0, 6,0,0, 0,2,4},
        {0,0,0, 0,0,0, 0,0,0},
        
        {0,0,0, 0,0,1, 2,0,0},
        {0,0,0, 0,0,8, 0,0,0},
        {4,7,1, 3,0,0, 0,0,0}
    };*/
    /*
    int PuzzleNumbers[9][9]= {
            {8,0,0, 0,0,0, 0,0,0},
            {0,0,3, 6,0,0, 0,0,0},
            {0,7,0, 0,9,0, 2,0,0},
            
            {0,5,0, 0,0,7, 0,0,0},
            {0,0,0, 0,4,5, 7,0,0},
            {0,0,0, 1,0,0, 0,3,0},
            
            {0,0,1, 0,0,0, 0,6,8},
            {0,0,8, 5,0,0, 0,1,0},
            {0,9,0, 0,0,0, 4,0,0}
        };
    
    sudoku Puzzle;
    for (int row=0; row<9; row++){
        for (int col=0; col<9; col++){
            if (PuzzleNumbers[row][col]){
                Puzzle.set(row,col,sudoku::NumToDig(PuzzleNumbers[row][col]));
            }
        }
    }

    printSdk(Puzzle);
//    Puzzle.autoFill();
//    printf("\n");
//    printSdk(Puzzle);
    
    sudoku Solution;
    QTime Timer;
    Timer.start();
    sudoku::state Result = Puzzle.solve(Solution,4);
    
    printf ("Time spent: %i, result %i", Timer.elapsed(), Result);
    printf("\n");
    printSdk(Solution);
    return 0;*/
