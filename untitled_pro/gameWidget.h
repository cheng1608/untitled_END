#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsView>

#include"gameEngine.h"
#include"startMenu.h"


class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);

private:
    StartMenu *pointStartMenu;
    GameEngine *pointGameEngine;


    QString power;
    QString lastAccount;

    void InitStartMenu();
    void InitStartMenu(QString account);
    void StartGameEngine();
    void EndGame();
    void onAccountInfoEntered(QString account);

};
#endif // GAMEWIDGET_H
