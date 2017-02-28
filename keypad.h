#ifndef KEYPAD_H
#define KEYPAD_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
class keyPad : public QWidget
{
    Q_OBJECT
public:
    explicit keyPad(QWidget *parent = 0);
    void toggleKeyEnabled (int num, bool enabled = true);
    
private:
    QVector <QPushButton*> numKeyList;    
signals:
    void numberSelected(int);
public slots:
    
private slots:
    void numberClicked(int i);
    void keyPressEvent(QKeyEvent *event);

};

#endif // KEYPAD_H
