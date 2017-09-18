#include "mainwindow.h"
#include "gamecontroller.h"
#include <QGraphicsView>
#include <QTimer>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene,this)),
    game(new GameController(*scene,this))

{
    setWindowTitle("贪吃蛇");

    QMenu *menu = menuBar()->addMenu(tr("游戏"));
    QToolBar *toolBar = addToolBar(tr("&N"));

    newGame = new QAction(tr("开局(&N)"),this);
    newGame->setShortcut(QKeySequence("F2"));
    newGame->setStatusTip(tr("开始一局游戏"));
    connect(newGame,&QAction::triggered,game,&GameController::gameOver);
    menu->addAction(newGame);
    menu->addSeparator();

    easyMode = new QAction(tr("简单模式(&E)"),this);
    easyMode->setStatusTip(tr("简单模式"));
    connect(easyMode,&QAction::triggered,game,&GameController::setEasy);
    menu->addAction(easyMode);

    commonMode = new QAction(tr("一般模式(&C)"),this);
    commonMode->setStatusTip(tr("一般模式"));
    connect(commonMode,&QAction::triggered,game,&GameController::setCommon);
    menu->addAction(commonMode);

    hardMode = new QAction(tr("困难模式(&H)"),this);
    hardMode->setToolTip(tr("困难模式"));
    connect(hardMode,&QAction::triggered,game,&GameController::setHard);
    menu->addAction(hardMode);

    pause = new QAction(QIcon(":/icon/pause"),tr("暂停"),this);
    pause->setShortcut(QKeySequence("p"));
    connect(pause,&QAction::triggered,game,&GameController::pause);
    toolBar->addAction(pause);
    resume = new QAction(QIcon(":/icon/resume"),tr("继续"),this);
    resume->setShortcut(QKeySequence("r"));
    connect(resume,&QAction::triggered,game,&GameController::resume);
    toolBar->addAction(resume);
    statusBar();

    setCentralWidget(view);
    resize(1000,1000);

    initView();
    initViewBg();

    QTimer::singleShot(0,this,SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(),Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initView()
{
    scene->setSceneRect(-100,-100,200,200);
}

void MainWindow::initViewBg()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}
