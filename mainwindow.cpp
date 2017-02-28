#include "mainwindow.h"

#include <QGridLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setWindowFlags(Qt::Dialog);
    QWidget* centralPane = new QWidget (this);
    QGridLayout* centralLayout = new QGridLayout;
    setCentralWidget(centralPane);
    centralPane->setLayout(centralLayout);

    QWidget* PuzzleArea = new QWidget (centralPane);
    centralLayout->addWidget(PuzzleArea,1,1);
    centralLayout->addWidget( new QWidget(this),2,2);
    QGridLayout* Grids = new QGridLayout;
    PuzzleArea -> setLayout(Grids);
    
    centralLayout->setColumnStretch(0,1);
    centralLayout->setColumnStretch(1,0);
    centralLayout->setColumnStretch(2,1);

    //centralPane->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    
    const int blockMargin = 10;
    Grids->setSpacing(blockMargin);
    for (int blockRow = 0; blockRow<3; blockRow++){
        for (int blockCol = 0; blockCol<3; blockCol++){
            QGridLayout* minorLayout = new QGridLayout;
            Grids->addLayout(minorLayout,blockRow,blockCol,1,1);
            for (int minorRow=0; minorRow<3; minorRow++){
                for (int minorCol=0; minorCol<3; minorCol++){
                    Cell* newCell = new Cell(this, &Puzzle, 
                        blockRow*3+minorRow, blockCol*3+minorCol);
                    cellList.push_back(newCell);
                    minorLayout->setSpacing(1);
                    minorLayout->addWidget(newCell,minorRow, minorCol,1,1);
                    connect (newCell, &Cell::numberUpdated, this, &updatePuzzle);
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::updatePuzzle()
{
    //Puzzle.autoFill();
    Puzzle.update();
    for (int iCell =0; iCell<81; iCell++) {
        cellList[iCell]->updateNumber();
        cellList[iCell]->repaint();
    }
}
