#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include "keypad.h"
#include "sudoku.h"

class Cell : public QWidget
{
    Q_OBJECT
public:
    explicit Cell(QWidget *parent, sudoku *Puzzle, int row, int col);
    
    void setNumbers(int nums)   { numbers = nums;}
    int size ()const {return numPadSize*3+marginSize*4;}
    void updateNumber();
        
private:
    sudoku* puzzle;
    int Row;
    int Col;
    int numbers; //Numbers use the same format as in sudoku.h
    keyPad* keys;
    const static int numPadSize = 6;
    const static int marginSize = 2;

    
    //bool conflict;
    
signals:
    void numberUpdated();
    
public slots:
    void setDigit (int Decim);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
};

#endif // CELL_H
