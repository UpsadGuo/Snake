#include <QPainter>

#include "snake.h"
#include "constants.h"
#include "gamecontroller.h"

static const qreal SNAKE_SIZE = 10;

Snake::Snake(GameController &controller):
    head(0,0),
    growing(7),
    speed(10),
    moveDirection(NoMove),
    controller(controller),
    tickCounter(0)
{
}

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    foreach(QPointF p,tail){
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }
    QPointF t1 = mapFromScene(QPointF(minX,minY));
    QPointF br = mapFromScene(QPointF(maxX,maxY));

    QRectF bound = QRectF(t1.x(),t1.y(),br.x()-t1.x()+SNAKE_SIZE,br.y()-t1.y()+SNAKE_SIZE);

    return bound;
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(QRectF(0,0,SNAKE_SIZE,SNAKE_SIZE));

    foreach(QPointF p,tail){
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(),itemp.y(),SNAKE_SIZE,SNAKE_SIZE));
    }

    return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->fillPath(shape(),Qt::yellow);
    painter->restore();
}

void Snake::setMoveDirection(Snake::Direction direction)
{
    moveDirection = direction;
}

void Snake::setSpeed(int s)
{
    speed = s;
}

Snake::Direction Snake::getMoveDirection()
{
    return moveDirection;
}

int Snake::getLength()
{
    return tail.length();
}

int Snake::getSpeed()
{
    return speed;
}

void Snake::advance(int step)
{
    if(!step){
        return;
    }
    if(tickCounter++%speed != 0){
        return;
    }
    if(moveDirection == NoMove){
        return;
    }
    if(growing > 0){
        QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    }
    else{
        tail.takeFirst();
        tail << head;
    }
    switch(moveDirection){
    case MoveLeft:
        moveLeft();
        break;
    case MoveRight:
        moveRight();
        break;
    case MoveUp:
        moveUp();
        break;
    case MoveDown:
        moveDown();
        break;
    default:
        break;
    }

    setPos(head);
    handleCollisions();
}

void Snake::moveLeft()
{
    head.rx() -= SNAKE_SIZE;
    if(head.rx() < -100){
        head.rx() = 100;
    }
}

void Snake::moveRight()
{
    head.rx()  += SNAKE_SIZE;
    if(head.rx() > 100){
        head.rx() = -100;
    }
}

void Snake::moveUp()
{
    head.ry() -= SNAKE_SIZE;
    if(head.ry() < -100){
        head.ry() = 100;
    }
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    if(head.ry() > 100){
        head.ry() = -100;
    }
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    foreach(QGraphicsItem *collidingItem,collisions){
        if(collidingItem->data(GD_Type) == GO_Food){
            controller.snakeAteFood((Food *)collidingItem);
            growing += 1;
        }
    }

    if(tail.contains(head)){
        controller.snakeAteItself();
    }
}
