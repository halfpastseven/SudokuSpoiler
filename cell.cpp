#include "cell.h"
#include "sudoku.h"
#include <QPainter>

Cell::Cell(QWidget *parent, sudoku* Puzzle, int row, int col) : QWidget(parent),
     puzzle (Puzzle),Row(row), Col (col),numbers(511)
  
{
    setFixedSize(numPadSize*3+marginSize*4,numPadSize*3+marginSize*4);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    keys = new keyPad(this);
    connect (keys,SIGNAL(numberSelected(int)), this,SLOT(setDigit(int)));
}

void Cell::updateNumber(){
    setNumbers(puzzle->get (Row,Col));
    int availableNums = puzzle->checkPossibleBits(Row, Col);
    
    for (int num = 1; num<=9; num++){
        keys->toggleKeyEnabled(num,availableNums & sudoku::NumMapBits[num]);
    }
}

void Cell::setDigit(int Decim) {
    if (sudoku::countPossibles(numbers)==1) puzzle->putBack(Row,Col,sudoku::BitsToNum(numbers));
    numbers = Decim ? sudoku::NumToBits(Decim) : 511;
    puzzle->set(Row,Col,numbers);
    emit numberUpdated();
}

void Cell::paintEvent(QPaintEvent *)
{
    
    QPainter painter(this);
    painter.setBrush(QBrush(QColor::fromHsv(200,150,255)));
    
    if (sudoku::countPossibles(numbers)==1){
        keys->toggleKeyEnabled(0,1);
        painter.drawRect(marginSize, marginSize,
                         numPadSize*3+marginSize*4,
                         numPadSize*3+marginSize*4);
        painter.setFont(QFont("Arial",14,QFont::Bold));
        
        painter.setPen (Qt::black);
        painter.drawText(marginSize, marginSize,numPadSize*3+marginSize*2,
                         numPadSize*3+marginSize*2,Qt::AlignHCenter|Qt::AlignVCenter,
                         QString::number(sudoku::BitsToNum(numbers)));
    }
    else{
        keys->toggleKeyEnabled(0,0);
        int Digits = numbers;
        for (int iDig = 1; iDig<=9; iDig++){
            
            int row = (iDig-1)/3;
            int col = (iDig-1)%3;
            
            if (Digits & 1) {
                painter.drawRect(col*(numPadSize+marginSize)+marginSize,
                                 row*(numPadSize+marginSize)+marginSize,
                                 numPadSize, numPadSize);
            }
            Digits >>= 1;
        }
    }
    
}

void Cell::mousePressEvent(QMouseEvent *)
{
    //keys->setParent(this,Qt::Tool|Qt::FramelessWindowHint);
    keys->show();
    keys->setFocus();
}


