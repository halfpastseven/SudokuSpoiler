#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sudoku.h"
#include "cell.h"
#include <QVector>
#include <QMainWindow>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    sudoku Puzzle;
    QVector <Cell*> cellList;
    
private slots:
    //void solve();
    void updatePuzzle();
};

#endif // MAINWINDOW_H
