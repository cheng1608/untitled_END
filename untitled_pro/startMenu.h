#ifndef STARTMENU_H
#define STARTMENU_H

#include <QGraphicsView> //显示图片
#include <QGraphicsScene> //管理图片
#include <QGraphicsItem>  //2D图形基类
#include <QGraphicsEffect> //图形效果

#include <QObject>

#include <QPushButton> //按钮
#include <QToolButton> //工具按钮
#include <QRadioButton> //单选按钮
#include <QButtonGroup> //管理按钮

#include<QFontDatabase>//字体
#include <QSoundEffect> //音效
#include <QEvent> //事件
#include <QFile> //文件
#include <QUrl> //URL
#include <QLabel>

#include <QGraphicsProxyWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QtNetwork>//http服务器
#include <QString>
#include <QByteArray>

class StartMenu: public QGraphicsView
{
    Q_OBJECT
public:
    StartMenu();
    StartMenu(QString account);
    void openPreparePage();
    void openMainPage();
    void openStartPage();
    
    void sendGetCoinRequest(QString account);
    void updateCoinLabel(QString coinCount);

    void sendLoginRequest(QString account, QString password);
    void sendChangeCoinRequest(QString account, QString targetCoin);
    QString getAccount() const { return account; }
    QString getMagic() const{return magic;}
signals:
    void startGame();
    void loginSuccess();


private:
    QGraphicsScene *pointMain;
    QGraphicsScene *pointPrepare;
    QGraphicsScene *pointLogin;

    QString magic;
    QString account;
    bool loginResult;
    QGraphicsTextItem *coinText;
    QString coinCount;

};

#endif // STARTMENU_H
