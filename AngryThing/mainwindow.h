#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>

#include <QLabel>
#include <math.h>
#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <bluebird.h>
#include <yellowbird.h>
#include <whitebird.h>
#include <egg.h>
#include <enemy.h>
#include <invwall.h>
#include <obstacle.h>
#include <newcursor.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);

    void generate_nextbird();
    void showScore();
    void restartfunc();
public slots:
    void ifcolliding();
    void on_pushButton_exit_clicked();
    void on_pushButton_restart_clicked();

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void detect();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    Land *land;
    yellowbird *ybird;
    bluebird *bbird;
    bluebird *a;
    bluebird *b;
    whitebird *wbird;
    Bird *rbird;
    egg *eggy;
    int once;
    int y_once;
    int b_once;
    int w_once;
    int redgenerated;
    int whichbird;
    QTimer *timer_detect;
    QTimer *timer_collide;
    enemy *piggy, *piggy2;
    obstacle *ob1, *ob2, *ob3, *ob4, *ob5, *ob6;
    QString scoretext;
    int displayscore;
    invwall *launcher;
    int defeat1;
    int defeat2;

};

#endif // MAINWINDOW_H
