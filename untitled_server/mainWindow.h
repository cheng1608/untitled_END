#include <QMainWindow>
#include <QLabel>
#include "httpserver.h"

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    ServerWindow(QWidget *parent = nullptr);

private:
    HttpServer *server;
};
