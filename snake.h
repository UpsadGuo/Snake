#ifndef SNAKE_H
#define SNAKE_H
#include <QGraphicsItem>

class GameController;

class Snake : public QGraphicsItem
{
public:
    enum Direction{
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(GameController &controller);

    QRectF boundingRect()const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setMoveDirection(Direction direction);
    void setSpeed(int s);
    Direction getMoveDirection();

protected:
    void advance(int step);
private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleCollisions();

    QPointF head;
    int growing;
    int speed;
    QList<QPointF> tail;
    int tickCounter;
    Direction moveDirection;
    GameController &controller;

};

#endif // SNAKE_H