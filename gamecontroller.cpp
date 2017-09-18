#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include "wall.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent):
    QObject(parent),
    scene(scene),
    snake(new Snake(*this)),
    isRunning(false)
{
    timer.start(1000/33);

    Food *al = new Food(0,-50);
    scene.addItem(al);

    scene.addItem(snake);
    scene.installEventFilter(this);

    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
}

GameController::~GameController(){

}

void GameController::snakeAteFood(Food *food)
{
    scene.removeItem(food);
    delete food;
    addNewFood();

    if(snake->getLength()%10 == 0 && snake->getSpeed()){
        snake->setSpeed(snake->getSpeed()-1);
    }
}

void GameController::snakeHitWall(Snake *snake, Wall *wall){

}

void GameController::snakeAteItself(){
    QTimer::singleShot(0,this,SLOT(gameOver()));
}

void GameController::handleKeyPressed(QKeyEvent *event){
    if(!isRunning){
        isRunning = true;
    }
    switch (event->key()) {
    case Qt::Key_Left:
        if(snake->getMoveDirection() != Snake::MoveRight)
            snake->setMoveDirection(Snake::MoveLeft);
        break;
    case Qt::Key_Right:
        if(snake->getMoveDirection() != Snake::MoveLeft)
            snake->setMoveDirection(Snake::MoveRight);
        break;
    case Qt::Key_Up:
        if(snake->getMoveDirection() != Snake::MoveDown)
            snake->setMoveDirection(Snake::MoveUp);
        break;
    case Qt::Key_Down:
        if(snake->getMoveDirection() != Snake::MoveUp)
            snake->setMoveDirection(Snake::MoveDown);
        break;
    default:
        break;
    }
}

void GameController::addNewFood(){
    int x,y;
    do{
        x = (int)(qrand() % 100) / 10;
        y = (int)(qrand() % 100) / 10;

        x *= 10;
        y *= 10;
    }while (snake->shape().contains(snake->mapFromScene(QPointF(x+5,y+5))));

    Food *food = new Food(x,y);
    scene.addItem(food);
}

void GameController::gameOver(){
    scene.clear();

    snake = new Snake(*this);
    scene.addItem(snake);
    isRunning = false;
    addNewFood();
}

void GameController::setEasy()
{
    if(!isRunning)
        snake->setSpeed(15);
}

void GameController::setCommon()
{
   if(!isRunning)
       snake->setSpeed(10);
}

void GameController::setHard()
{
   if(!isRunning)
       snake->setSpeed(5);
}


void GameController::pause(){
    if(isRunning){
        isRunning = false;
        disconnect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
    }
}

void GameController::resume(){
    if(!isRunning){
        isRunning = true;
        connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
    }
}

bool GameController::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    else{
        return QObject::eventFilter(watched,event);
    }
}














