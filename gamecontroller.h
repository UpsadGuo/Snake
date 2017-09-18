#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QObject>
#include <QTimer>
#include "food.h"
#include "constants.h"

class QGraphicsScene;
class QKeyEvent;
class Snake;
class Food;
class Wall;

class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(QGraphicsScene &scene,QObject *parent);
    ~GameController();
    void snakeAteFood(Food *food);
    void snakeHitWall(Snake *snake,Wall *wall);
    void snakeAteItself();
public slots:
    void pause();
    void resume();
    void gameOver();
    void setLevel(Levels level);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();

    QGraphicsScene &scene;
    QTimer timer;

    bool isRunning;

    Snake *snake;
};

#endif // GAMECONTROLLER_H
