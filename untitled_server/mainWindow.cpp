#include "mainWindow.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);

    QLabel *label = new QLabel(this);
    setCentralWidget(label);

    server = new HttpServer(this);
    // 启动服务器
    if (!server->listen(QHostAddress::Any, 8080)) {
        label->setText("启动服务器失败");
    } else {
        label->setText("启动服务器，端口为8080");
    }
}
