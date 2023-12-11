#include "gameWidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}
{
    QPixmap cursorPic(":/images/star-shuriken.png");//鼠标指针
    QCursor cursor(cursorPic, -cursorPic.width()/2, -cursorPic.height()/2);
    setCursor(cursor);

    setMouseTracking(true);
    setFixedSize(1500, 1000);
    setWindowTitle("Avan");
    setWindowIcon(QIcon(":/images/genshin_icon2.png"));//图标

    InitStartMenu();
}

//初始化开始页面
void GameWidget::InitStartMenu(){
    pointStartMenu = new StartMenu();
    pointStartMenu->setParent(this);
    connect(pointStartMenu, &StartMenu::startGame, this, &GameWidget::StartGameEngine);
    pointStartMenu->show();
    pointStartMenu->setFocus();
}

void GameWidget::InitStartMenu(QString account){
    pointStartMenu = new StartMenu(account);
    pointStartMenu->setParent(this);
    connect(pointStartMenu, &StartMenu::startGame, this, &GameWidget::StartGameEngine);

    pointStartMenu->show();
    pointStartMenu->setFocus();
}

//开始游戏
void GameWidget::StartGameEngine() {
    QString account = pointStartMenu->getAccount();
    this->lastAccount = account; // 保存账号信息

    QString magic = pointStartMenu->getMagic();

    pointStartMenu->hide();
    pointGameEngine = new GameEngine(magic);
    pointGameEngine->setParent(this);
    connect(pointGameEngine, &GameEngine::Endgame, this, &GameWidget::EndGame);
    pointGameEngine->show();
    pointGameEngine->setFocus();
}

//结束游戏回到开始页面
void GameWidget::EndGame() {
    pointGameEngine->hide();
    disconnect(pointGameEngine, &GameEngine::Endgame, this, &GameWidget::EndGame);
    InitStartMenu(lastAccount);
}

