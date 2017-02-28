#include "keypad.h"

#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QKeyEvent>

keyPad::keyPad(QWidget *parent) : 
    QWidget(parent,Qt::Tool|Qt::FramelessWindowHint)
{
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    QGridLayout* keyPadLayout = new QGridLayout(this);
    
    QButtonGroup* buttons = new QButtonGroup (this);
    QPushButton* clearButton = new QPushButton (tr("Clear"));
    buttons->addButton(clearButton,0);
    keyPadLayout->addWidget(buttons->button(0),0,0,1,-1);
    numKeyList.push_back(clearButton);
    
    for (int i=1; i<=9; i++){
        numKeyList.push_back(new QPushButton(QString::number(i)));
        buttons->addButton(numKeyList.back(),i);
        keyPadLayout->addWidget(buttons->button(i),(i-1)/3+1,(i-1)%3,1,1);
        buttons->button(i)->setFixedSize(30,30);
    }
    setVisible(0);  
    connect (buttons, SIGNAL(buttonClicked(int)),this, SLOT(numberClicked(int)));
}

void keyPad::toggleKeyEnabled(int num, bool enabled){
    numKeyList[num]->setEnabled(enabled);
}

void keyPad::numberClicked(int i)
{
    this->hide();
    emit numberSelected(i);
}

void keyPad::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
        case Qt::Key_Escape: this->hide(); break;
        case Qt::Key_Delete: numberClicked(0); break;
        case Qt::Key_1: numberClicked(1); break;
        case Qt::Key_2: numberClicked(2); break;
        case Qt::Key_3: numberClicked(3); break;
        case Qt::Key_4: numberClicked(4); break;
        case Qt::Key_5: numberClicked(5); break;
        case Qt::Key_6: numberClicked(6); break;
        case Qt::Key_7: numberClicked(7); break;
        case Qt::Key_8: numberClicked(8); break;
        case Qt::Key_9: numberClicked(9); break;
    }
}
