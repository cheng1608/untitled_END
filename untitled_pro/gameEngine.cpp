
#include "gameEngine.h"

#include"enemyZomble.h"
#include"enemyZombleFire.h"
#include"enemyZombleFireGiant.h"
#include"enemyZombleWind.h"
#include"enemyZombleWindGiant.h"
#include"enemyZombleEarth.h"
#include"enemyZombleEarthGiant.h"

#include"enemyWizard.h"

#include "enemyExplosiveSkeleton.h"

#include "magicBall.h"

#include "magicIce.h"
#include "magicFire.h"
#include"magicWater.h"

GameEngine::GameEngine(QString magic):magic(magic)

{
    QFontDatabase::addApplicationFont(":/font/fusion-pixel-proportional.ttf");
    setFixedSize(1500, 1000);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainScene = new QGraphicsScene(this);

    //平时背景
    QColor bgColor = QColor(200, 200, 255);//紫色
    QSize bgSize = QSize(4000, 2400);
    QPixmap bgPixmap(bgSize);
    bgPixmap.fill(bgColor);

    //boss战背景
    QColor bossBgColor = QColor(255, 200, 200);//粉色
    QPixmap bossBgPixmap(bgSize);
    bgPixmap.fill(bossBgColor);

    QPixmap background(":/images/ts1at-oznr4.png");

    mainBackground = new QGraphicsPixmapItem;
    mainBackground->setPixmap(background);
    mainBackground->setZValue(-0x3ffffff);
    mainScene->addItem(mainBackground);//把创建的主背景添加到场景中
    mainScene->setSceneRect(0, 0, 1500, 1000);
    setScene(mainScene);

    // 角色生成
    mainPlayer = new Player(this, this);
    mainPlayer->setParentItem(mainBackground);
    mainScene->addItem(mainPlayer);

    mainPlayer->moveBy(2000+650, 1200+400); // 移动player至地图中央
    centerOn(mainPlayer->pos());//玩家固定窗口中央
    mainBackground->moveBy(-2000, -1200);



    // 血条生成
    setHealthBar();
    connect(mainPlayer, &Player::playerHurt, this, &GameEngine::setHealthBar);
    connect(mainPlayer, &Player::playerRegen, this, &GameEngine::setHealthBar);
    
    //魔法选择
    if(magic=="magicFire"||magic==""){
        mainMagic = new MagicFire(mainPlayer, mainScene, this);
    }
    else if (magic=="magicIce"){
        mainMagic = new MagicIce(mainPlayer, mainScene, this);
    }
    else if (magic=="magicWater"){
        mainMagic = new MagicWater(mainPlayer, mainScene, this);
    }
    mainMagic->setParentItem(mainBackground);
    mainMagic->moveBy(2000+650,1200+400);//虚点位置和player重合

    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // 主计时器(所有绑定放这里下面)
    mainTimer = new QTimer(this);
    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



    // player移动和贴图加载
    connect(mainTimer, &QTimer::timeout, mainPlayer, &Player::updateCoordinate);
    connect(mainTimer, &QTimer::timeout, mainPlayer, &Player::load);
    connect(mainTimer, &QTimer::timeout, this, &GameEngine::updateBackground);
    connect(mainPlayer, &Player::playerDeath, this, &GameEngine::endgame_lose);

    EnemyBase::enemyTimer = mainTimer;//连接敌人计时器
    connect(mainTimer, &QTimer::timeout, this, &GameEngine::enemyGenerator);
    
    MagicBall::attackTimer = mainTimer; // Bullet计时器
    // 武器移动，加载贴图，开火wwww
    connect(mainTimer, &QTimer::timeout, mainMagic, &MagicBase::updatePos);
    connect(mainTimer, &QTimer::timeout, mainMagic, &MagicBase::cast);


    enemyNumberMax=5;
    //初始化怪物生成比例（注意，按照百分比）（巨人化的比例独立）
    enemyZombleRate=60;//普通僵尸
    enemyZombleFireRate=30;//火僵尸
    enemyZombleEarthRate=0;//土僵尸
    enemyZombleWindRate=0;//风僵尸
    enemyWizardRate=0;//巫妖
    enemyExplosiveSkeletonRate=10;//爆炸骷髅

    enemyBeGiantRate=0;//巨人化
    connect(mainTimer, &QTimer::timeout, this, &GameEngine::phaseUp);


    // 倒计时初始化
    countdown_text = new QGraphicsTextItem();
    mainScene->addItem(countdown_text);
    countdown_text->setFont(QFont("fusion pixel proportional", 32));
    countdown_text->setPos(1300, 10);
    countdown_text->setDefaultTextColor(Qt::black);
    countdown_time = QTime(0 ,0, 30);//游戏阶段初始值 mm和ss
    countdown_text->setPlainText(countdown_time.toString("mm:ss"));
    // 倒计时刷新
    connect(mainTimer, &QTimer::timeout, this, &GameEngine::updateCountdown);

    //#################################################################################################
    mainTimer->start(10);
}

void GameEngine::updateBackground(){
    QPointF bias = mainPlayer->getCoordinateBias();
    mainBackground->moveBy(bias.x(), bias.y());
}

void GameEngine::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_W:
        mainPlayer->addVelocity(0, -1);
        break;
    case Qt::Key_S:
        mainPlayer->addVelocity(0, 1);
        break;
    case Qt::Key_A:
        mainPlayer->addVelocity(-1, 0);
        break;
    case Qt::Key_D:
        mainPlayer->addVelocity(1, 0);
    default:
        break;
    }
}

void GameEngine::keyReleaseEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_W:
        mainPlayer->addVelocity(0, 1);
        break;
    case Qt::Key_S:
        mainPlayer->addVelocity(0, -1);
        break;
    case Qt::Key_A:
        mainPlayer->addVelocity(1, 0);
        break;
    case Qt::Key_D:
        mainPlayer->addVelocity(-1, 0);
    default:
        break;
    }
}

void GameEngine::mouseMoveEvent(QMouseEvent *event){
    mainMagic->rotateToCursor(event->pos());//用于计算魔法释放的方向
    QGraphicsView::mouseMoveEvent(event);
}

void GameEngine::mousePressEvent(QMouseEvent *event){
    switch (event->button()) {
    case Qt::LeftButton:
        mainMagic->startCasting();//释放魔法
        break;
    default:
        break;
    }
    QGraphicsView::mousePressEvent(event);
}

void GameEngine::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        mainMagic->stopCasting();//停止释放
        break;
    default:
        break;
    }
    // 将事件传递给视图
    QGraphicsView::mouseReleaseEvent(event);
}

void GameEngine::enemyGenerator(){
    enemyNumberNote++;
    if(enemyNumberNote>enemyNumberMax){
        return;//最高上限不会超过
    }
    QPointF enemyPos;
    qreal dist;
    do {//尝试合适的生成位置
        enemyPos.setX(QRandomGenerator::global()->bounded(0, 4000));
        enemyPos.setY(QRandomGenerator::global()->bounded(0, 2400));
        dist = QLineF(mainPlayer->pos(), enemyPos).length();

    } while (dist < 450 || dist > 650);// 不在视野范围或过近时重新生成

    EnemyBase *enemy = nullptr;

    int GenerateRandomNumber = QRandomGenerator::global()->bounded(0, 100);//怪物生成种类
    int BeGiantRandomNumber = QRandomGenerator::global()->bounded(0, 100);//是否巨人化（放在判断完成种类后）

    if(GenerateRandomNumber<enemyZombleRate){
        //普通僵尸
        enemy=new EnemyZomble(mainPlayer,mainScene,this);
    }
    else if(GenerateRandomNumber<enemyZombleRate+enemyZombleFireRate){
        //火僵尸
        if(BeGiantRandomNumber<enemyBeGiantRate){
            enemy =new EnemyZombleFireGiant(mainPlayer,mainScene,this);
        }else{
            enemy=new EnemyZombleFire(mainPlayer,mainScene,this);
        }
    }
    else if(GenerateRandomNumber<enemyZombleRate+enemyZombleFireRate+enemyZombleEarthRate){
        //土僵尸
        if(BeGiantRandomNumber<enemyBeGiantRate){
            enemy =new EnemyZombleEarthGiant(mainPlayer,mainScene,this);
        }else{
            enemy=new EnemyZombleEarth(mainPlayer,mainScene,this);
        }
    }
    else if(GenerateRandomNumber<enemyZombleRate+enemyZombleFireRate+enemyZombleEarthRate+enemyZombleWindRate){
        //风僵尸
        if(BeGiantRandomNumber<enemyBeGiantRate){
            enemy =new EnemyZombleWindGiant(mainPlayer,mainScene,this);
        }else{
            enemy=new EnemyZombleWind(mainPlayer,mainScene,this);
        }
    }
    else if(GenerateRandomNumber<enemyZombleRate+enemyZombleFireRate+enemyZombleEarthRate+enemyZombleWindRate+enemyWizardRate){
        //巫妖
        enemy=new EnemyWizard(mainPlayer,mainScene,this);
    }
    else if(GenerateRandomNumber<enemyZombleRate+enemyZombleFireRate+enemyZombleEarthRate+enemyZombleWindRate+enemyWizardRate+enemyExplosiveSkeletonRate){
        //爆炸骷髅
        enemy=new EnemyExplosiveSkeleton(mainPlayer,mainScene,this);
    }
    else {
        enemy=new BossAlex(mainPlayer,mainScene,this);
        connect(enemy, &EnemyBase::bossDeath, this, &GameEngine::endgame_win);
    }
    if (!enemy) return;
    enemy->setParentItem(mainBackground);
    enemy->setPos(enemyPos);
    enemy->setZValue(1);
    // 将敌人添加到场景中
    mainScene->addItem(enemy);
}

void GameEngine::setHealthBar(){
    int nowHP = mainPlayer->getNowHP();
    int maxHP = mainPlayer->getMaxHP();

    for (auto *p : heartList) {
        if (p) p->deleteLater();
    }
    heartList.clear();

    int numHearts = maxHP / 10; // 十个心心（角色一百血）
    //每颗心代表十点血分四个档
    for (int i = 0; i < numHearts; ++i) {
        HeartLabel *heart = new HeartLabel(this);
        if (nowHP >= (i+1) * 10) { // 满心
            heart->setFullHeart();
        }
        else if(nowHP >= (i+1) * 10-4){//正心
            heart->setPlusHeart();
        }
        else if(nowHP >= (i+1) * 10-8){//负心
            heart->setMinusHeart();
        }
        else {
            heart->setEmptyHeart(); // 空心
        }
        heart->move(heart->x() - i*36, heart->y());
        heartList.append(heart);
    }
}

void GameEngine::updateCountdown(){
    countdown_count++;
    if (countdown_count < 100) return;
    countdown_count = 0;
    countdown_time = countdown_time.addSecs(-1);
    if (countdown_time <= QTime(0, 0,0)) {
        if(!isFightingBoss)countdown_time = QTime(0, 0,30);
        else endgame_lose();
    }
    countdown_text->setPlainText(countdown_time.toString("mm:ss"));
}

void GameEngine::phaseUp() // 渐进式游戏阶段
{
    phase_count++;
    if (phase_count < 3000) return; // 30s
    phase_count = 0;
    phase++;
    switch (phase) {
    case 1:
        enemyNumberMax=5;
        enemyZombleRate=40;
        enemyZombleFireRate=30;
        enemyZombleEarthRate=10;
        enemyZombleWindRate=10;
        enemyWizardRate=0;
        enemyExplosiveSkeletonRate=10;
        enemyBeGiantRate=10;
        enemyNumberNote=0;
        break;
    case 2:
        enemyNumberMax=6;
        enemyZombleRate=20;
        enemyZombleFireRate=30;
        enemyZombleEarthRate=20;
        enemyZombleWindRate=20;
        enemyWizardRate=0;
        enemyExplosiveSkeletonRate=10;
        enemyBeGiantRate=20;
        enemyNumberNote=0;
        break;
    case 3:
        enemyNumberMax=7;
        enemyZombleRate=0;
        enemyZombleFireRate=30;
        enemyZombleEarthRate=20;
        enemyZombleWindRate=30;
        enemyWizardRate=10;
        enemyExplosiveSkeletonRate=10;
        enemyBeGiantRate=30;
        enemyNumberNote=0;
        break;
    case 4:
        enemyNumberMax=8;
        enemyZombleRate=0;
        enemyZombleFireRate=20;
        enemyZombleEarthRate=20;
        enemyZombleWindRate=30;
        enemyWizardRate=10;
        enemyExplosiveSkeletonRate=20;
        enemyBeGiantRate=50;
        enemyNumberNote=0;
        break;
    case 5:
        enemyNumberMax=1;
        enemyZombleRate=-1;
        enemyZombleFireRate=-1;
        enemyZombleEarthRate=-1;
        enemyZombleWindRate=-1;
        enemyWizardRate=-1;
        enemyExplosiveSkeletonRate=-1;
        enemyBeGiantRate=-1;
        enemyNumberNote=0;
        isFightingBoss=1;
        countdown_time = QTime(0 ,2, 0);//两分钟战斗！
        break;
    default:
        break;
    }

}

void GameEngine::endgame_lose() {
    // 读取样式表
    QFile file_sqr_pb(":/style.qss");
    file_sqr_pb.open(QFile::ReadOnly);
    QString style_sqr_pb;
    if (file_sqr_pb.isOpen()) {
        style_sqr_pb = QLatin1String(file_sqr_pb.readAll());
        file_sqr_pb.close();
    }
    // 停止所有计时器
    mainTimer->stop();
    // 删除血条
    for (auto *p : heartList) {
        if (p) p->deleteLater();
    }

    // 显示游戏结束界面
    end_scene = new QGraphicsScene(this);
    end_scene->setSceneRect(0, 0, 1500, 1000);
    setScene(end_scene);
    end_scene->setFocus();
    // 背景
    end_scene->addPixmap(QPixmap(":/images/ABackground.png"));
    // 文字
    QGraphicsTextItem *end_text = new QGraphicsTextItem("You Lose!");
    end_text->setFont(QFont("fusion pixel proportional", 72));
    end_text->setDefaultTextColor(Qt::red);
    end_text->setPos(450, 360);
    end_scene->addItem(end_text);
    // 返回按钮
    QPushButton *return_btn = new QPushButton("BACK");
    end_scene->addWidget(return_btn);
    return_btn->move(100, 700);
    return_btn->setStyleSheet(style_sqr_pb);
    return_btn->resize(110, 110);
    connect(return_btn, &QPushButton::clicked, this, [=](){
        emit Endgame();
        deleteLater();
    });
}

void GameEngine::endgame_win() {
    // 读取样式表
    QFile file_sqr_pb(":/style.qss");
    file_sqr_pb.open(QFile::ReadOnly);
    QString style_sqr_pb;
    if (file_sqr_pb.isOpen()) {
        style_sqr_pb = QLatin1String(file_sqr_pb.readAll());
        file_sqr_pb.close();
    }
    // 停止所有计时器
    mainTimer->stop();
    // 删除血条
    for (auto *p : heartList) {
        if (p) p->deleteLater();
    }
    // 显示游戏结束界面
    end_scene = new QGraphicsScene(this);
    end_scene->setSceneRect(0, 0, 1500, 1000);
    setScene(end_scene);
    // 背景
    end_scene->addPixmap(QPixmap(":/images/ABackground.png"));
    // 文字
    QGraphicsTextItem *end_text = new QGraphicsTextItem("You Win!");
    end_text->setFont(QFont("fusion pixel proportional", 72));
    end_text->setDefaultTextColor(Qt::green);
    end_text->setPos(450, 360);
    end_scene->addItem(end_text);
    // 返回按钮
    QPushButton *return_btn = new QPushButton("BACK");
    end_scene->addWidget(return_btn);
    return_btn->move(100, 700);
    return_btn->setStyleSheet(style_sqr_pb);
    return_btn->resize(110, 110);
    connect(return_btn, &QPushButton::clicked, this, [=](){
        emit Endgame();
        deleteLater();
    });
}
