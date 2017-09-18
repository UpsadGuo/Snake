#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QGraphicsView;
class QGraphicsScene;

class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void adjustViewSize();
private:
    void initView();
    void initViewBg();

    QAction *newGame;
    QAction *easyMode;
    QAction *commonMode;
    QAction *hardMode;

    QAction *pause;
    QAction *resume;

    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *game;
};

#endif // MAINWINDOW_H
