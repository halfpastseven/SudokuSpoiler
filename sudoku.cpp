#include "sudoku.h"
#include <cstdio>
#include <fstream>
#include <string>

extern printSdk(const sudoku& Puzzle);
//extern std::ofstream Debug;

inline std::string expressNumber (int i){
    std::string SNumber(9,'.');
    for (int dig=1; dig<=9; dig++){
        if (i & sudoku::NumMapBits[dig]) SNumber[9-dig]='0' + dig;
    }
    return SNumber;
}


sudoku::sudoku():cells(std::vector<int>(81,511))
{
    
}

bool sudoku::checkValid(int row, int col, int decimNum) const
{
    for (int testRow = 0; testRow<9; testRow++){
        if (testRow!=row && countPossibles(testRow,col)==1 &&
                (get(testRow,col) & NumMapBits[decimNum])) return 0;//testRow*9+col;
    }
    for (int testCol = 0; testCol<9; testCol++){
        if (testCol!=col && countPossibles(row,testCol)==1 && 
                (get(row,testCol) & NumMapBits[decimNum])) return 0;//row*9+testCol;
    }
    for (int testRow=(row/3)*3; testRow<(row/3)*3+3; testRow++){
        for (int testCol=(col/3)*3; testCol<(col/3)*3+3; testCol++){
            if (testRow!=row && testCol!=col && countPossibles(row,testCol)==1 &&
                    (get(testRow,testCol)& NumMapBits[decimNum])) {
                return 0; //testRow*9+testCol;
            }
        }
    }
    return 1;
}

int sudoku::checkPossibleBits(int row, int col) const
{
    int NumbersPossible = 511;
    
    for (int testRow = 0; testRow<9; testRow++){
        if (testRow!=row && countPossibles(testRow,col)==1) {
            NumbersPossible &= (511-get (testRow, col));
        }
    }
    for (int testCol = 0; testCol<9; testCol++){
        if (testCol!=col && countPossibles(row,testCol)==1)
            NumbersPossible &= (511-get (row, testCol));
    }
    for (int testRow=(row/3)*3; testRow<(row/3)*3+3; testRow++){
        for (int testCol=(col/3)*3; testCol<(col/3)*3+3; testCol++){
            if (testRow!=row && testCol!=col && countPossibles(row,testCol)==1){
                NumbersPossible &= (511-get (testRow, testCol));
            }
        }
    }
    return NumbersPossible;
}

sudoku::state sudoku::update(int maxBranch)
{
    autoFill();
    sudoku solution;
    state Result = solve (solution, maxBranch);
    if (Result==sudoku::single) cells = solution.cells;
    return Result;
}

void sudoku::putBack(int row, int col, int decimalDigit)
{
    for (int testRow = 0; testRow<9; testRow++){
        if (testRow!=row) {
            cell(testRow,col) |= NumMapBits[decimalDigit];
        }
    }
    for (int testCol = 0; testCol<9; testCol++){
        if (testCol!=col){
            cell(row,testCol) |= NumMapBits[decimalDigit];
        }
    }
    for (int testRow=(row/3)*3; testRow<(row/3)*3+3; testRow++){
        for (int testCol=(col/3)*3; testCol<(col/3)*3+3; testCol++){
            if (testRow!=row && testCol!=col ) {
                cell (testRow, testCol) |= NumMapBits[decimalDigit];
            }
        }
    }
}

sudoku::state sudoku::solve(sudoku& solution, int maxBranch)
{
    if (maxBranch<2) return invalid;
    
    //Debug<<"Before autofill"<<std::endl;
    //printSdk (*this);
    
    int Filled = autoFill();

    /*Debug<<"Autofill: ";
    if (Filled==-1 ) Debug<<"failed!"<<std::endl;
    else {
        Debug<<"filled "<<Filled<<"\n";
        printSdk (*this);
        Debug<<"\n";
    }*/
    
    if (Filled == -1 )return invalid;
    
    /** Check if every cell is filled already **/

    bool solved = 1;
    for (int i = 0; i<81; i++){
        if (countPossibles(cells[i])!=1) {
            solved=0;
            break;
        }
    }
    if (solved) {
        solution.cells = cells;
        /*
        Debug<<"Got one answer: \n";
        printSdk(*this);*/
        
        return single;
    }
    
    for (int row = 0; row<9; row++){
        for (int col=0; col<9; col++){
            int countNumbers = countPossibles(row,col);
            if (countNumbers>1&&countNumbers<=maxBranch){
                int CellNums = get (row,col);/*
                Debug << "Cell ["<<row+1<<","<<col+1<<"] has possible : "<<
                         expressNumber(CellNums)<<std::endl;*/
                int digit = 1;                
                state Result = invalid; // Initialize
                
                //iterate through all possible values of a single 
                while (CellNums){
                    
                    //if (Result == multi) break;
                    if (CellNums%2) {
                        sudoku SubPuzzle = *this;
                        SubPuzzle.set(row,col,NumMapBits[digit]);
                        
                        /*Debug<<"Try ("<<row+1<<","<<col+1<<") = "<< digit <<std::endl;*/
                        
                        state SubResult = SubPuzzle.solve(solution,maxBranch);
                        
                        if (SubResult == multi) return multi;
                        else if (SubResult == single){
                            if (Result==invalid) {
                                Result = single;
                            }
                            else{ //implies single
                                return multi;
                            }
                        }
                    }
                    CellNums>>=1;
                    digit++;
                }
                return Result;
            }
        }
    }
    //return solve(*this,maxBranch+1); //Only happens if there is no branch <= maxBranch
    return sudoku::multi;
}

int sudoku::autoFill()
{
    int countFilled=0; //Store the number of new cells to be filled
    bool filled=1; //Whether a cell has been filled (options decrease to 1)
    bool cellChanged [9][9];
    
    for (int row=0;row<9;row++) {
        for (int col=0;col<9;col++) {
            cellChanged[row][col] = 0;            
        }
    }    
    
    while (filled){
        filled=0;        
        
        for (int row =0; row<9; row++){
            for (int col=0; col<9; col++){
                
                int currentCountPossible = countPossibles(row,col);
                
                if (!currentCountPossible) return -1;
                else if (currentCountPossible>1) continue;
                
                //At this point, countCurrentPossible is 1
                
                if (!cellChanged[row][col]){
                    
                    cellChanged[row][col] = 1;
                    countFilled++;

                    for (int otherRow = 0; otherRow<9; otherRow++){
                        if (row!=otherRow){ //remove the digit from the other cell
                            cell(otherRow, col) &= 511-get (row, col);
                        }
                    }
                    
                    for (int otherCol=0; otherCol<9; otherCol++){
                        if (col!=otherCol){
                            cell(row, otherCol) &= 511-get(row, col);
                        }
                    }
                    
                    for (int otherRow=row/3*3; otherRow<row/3*3+3;otherRow++){
                        for (int otherCol=col/3*3; otherCol<col/3*3+3;otherCol++){
                            if (row!=otherRow && col!=otherCol){
                                cell (otherRow, otherCol) &= 511-get(row, col);
                            }
                                
                        }
                    }
                }
            }
        }
    }
    
    return countFilled;
}

const sudoku::Bits sudoku::NumMapBits [] = {
    sudoku::ZERO,
    sudoku::N1,
    sudoku::N2, 
    sudoku::N3,
    sudoku::N4,
    sudoku::N5, 
    sudoku::N6,
    sudoku::N7, 
    sudoku::N8, 
    sudoku::N9};
