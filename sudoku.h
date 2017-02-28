#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <cstdio>
class sudoku
{
public:
    // Types
    enum Bits {ZERO=0x0, N1=0x1, N2=0x2, N3=0x4, 
                               N4=0x8, N5=0x10,N6=0x20,
                               N7=0x40,N8=0x80,N9=0x100};
    static const Bits NumMapBits [];    
    enum state {invalid, single, multi};
    
    // Constructor
    sudoku();
    
    // Methods
    inline static int BitsToNum(int dig){
        for (int i=1; i<=9; i++) if (dig & NumMapBits[i]) return i;
        return 0;
    }
    inline static Bits NumToBits(int i){return NumMapBits[i];}
    
    bool checkValid(int row, int col, int decimNum) const;
    int checkPossibleBits (int row, int col) const;
    
    int autoFill ();
    state update(int maxBranch=2);
    state solve (sudoku &solution,int maxBranch=2 );
    
    //getters and setters
    inline int get(int Row, int Col) const {return cells[Row*9+Col];}
    inline void set(int Row, int Col, int num){cells[Row*9+Col] = num;}
    
    void putBack(int row, int col, int decimalDigit);
    
    inline static int countPossibles (int i) {//return the number of candidates in an int
        int count=0;
        while (i){
            if (i&1)count++;
            i>>=1;
        }
        return count;
    }
    
    inline int countPossibles(int row, int col) const {//return the candidates in a cell
        return countPossibles (get(row, col));
    }
        
private:
    
    std::vector <int> cells;
    inline int& cell(int Row, int Col) {return cells[Row*9+Col];}
};

#endif // SUDOKU_H
