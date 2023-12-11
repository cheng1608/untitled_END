#include "httpserver.h"

HttpServer::HttpServer(QObject *parent) : QTcpServer(parent){
    qDebug()<<"创建新的服务器对象";
}

void HttpServer::incomingConnection(qintptr socketDescriptor){
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);

    connect(clientSocket, &QTcpSocket::readyRead, this, &HttpServer::handleRequest);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void HttpServer::handleRequest(){
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    QByteArray requestData = clientSocket->readAll();
    QString requestString(requestData);

    //######################################################################################################################################

    //GET /get_coin_value?account=<account_name> HTTP/1.1

    if (requestString.startsWith("GET /get_coin_value?"))
    {
        QRegularExpression accountRegex("\\?account=([^&\\s]+)");
        QRegularExpressionMatch match = accountRegex.match(requestString);

        if (!match.hasMatch()) {
            qDebug() << "Failed to match account";
            writeToLogFile("Failed to match account");
        } else {
            QString account = match.captured(1);
            qDebug() << "account: " << account;
            QString accountInfo= "account: "+account;
            writeToLogFile(accountInfo);
        }

        if (match.hasMatch()) {
            QString account = match.captured(1);

            int coin_value = getCoinValue(account);

            if (coin_value >= 0) {
                qDebug() << "Successfully retrieved the number of coins for the account" << account << ": " << coin_value;
                QString coinValueInfoSuccess= "Successfully retrieved the number of coins for the account" + account + ": " + coin_value;
                writeToLogFile(coinValueInfoSuccess);
            } else {
                qWarning() << "Failed to retrieve the number of coins for the account" << account;
                QString coinValueInfoFail= "Failed to retrieve the number of coins for the account" +account;
                writeToLogFile(coinValueInfoFail);
            }

            QByteArray responseData = QString::number(coin_value).toUtf8();//返回金币数

            QByteArray response = "HTTP/1.1 200 OK\r\n"
                                  "Content-Length: " + QByteArray::number(responseData.size()) + "\r\n"
                                                                              "Content-Type: text/plain\r\n"
                                                                              "Access-Control-Allow-Origin: *\r\n"
                                                                              "\r\n" +
                                  responseData;

            clientSocket->write(response);
            clientSocket->waitForBytesWritten();
        }
    }

    //######################################################################################################################################

    //POST /login?account=<account_name>&password=<_password> HTTP/1.1

    else if (requestString.startsWith("POST /login"))
    {
        QRegularExpression accountRegex("\\?account=([^&\\s]+)");
        QRegularExpression passwordRegex("\\&password=([^&\\s]+)");

        QRegularExpressionMatch accountMatch = accountRegex.match(requestString);
        QRegularExpressionMatch passwordMatch = passwordRegex.match(requestString);

        if (!accountMatch.hasMatch()) {
            qDebug() << "Failed to capture account for login";
            writeToLogFile("Failed to match account for login");
        } else {
            QString account = accountMatch.captured(1);
            qDebug() << "Login account: " << account;
            QString accountInfo= "account: "+account;
            writeToLogFile(accountInfo);
        }

        if (!passwordMatch.hasMatch()) {
            qDebug() << "Failed to capture password for login";
            writeToLogFile("Failed to capture password for login");
        } else {
            qDebug() << "Successfully captured password for login";
        }

        if (accountMatch.hasMatch() && passwordMatch.hasMatch()) {
            QString account = accountMatch.captured(1);
            QString password = passwordMatch.captured(1);

            bool loginResult = checkLogin(account, password);

            if (!loginResult) {
                qDebug() << "Login failed";
                writeToLogFile("Login failed");
            } else {
                qDebug() << "Login successful";
                writeToLogFile("Login successful");
            }

            QByteArray responseData = loginResult ? "true" : "false";//是否成功

            QByteArray response = "HTTP/1.1 200 OK\r\n"
                                  "Content-Length: " + QByteArray::number(responseData.size()) + "\r\n"
                                                                              "Content-Type: text/plain\r\n"
                                                                              "Access-Control-Allow-Origin: *\r\n"
                                                                              "\r\n" +
                                  responseData;

            clientSocket->write(response);
            clientSocket->waitForBytesWritten();
        }
    }
    //#############################################################################################################################

    //POST /updateCoins?account=<account_name>&targetCoins=<Coins> HTTP/1.1

    else if (requestString.startsWith("POST /updateCoins"))
    {
        QRegularExpression accountRegex("\\?account=([^&\\s]+)");
        QRegularExpression coinsRegex("\\&targetCoins=([^&\\s]+)");

        QRegularExpressionMatch accountMatch = accountRegex.match(requestString);
        QRegularExpressionMatch coinsMatch = coinsRegex.match(requestString);

        if (!accountMatch.hasMatch()) {
            qDebug() << "Failed to capture account for updating coins";
            writeToLogFile("Failed to capture account for updating coins");
        } else {
            QString account = accountMatch.captured(1);
            qDebug() << "account: " << account;
        }

        if (!coinsMatch.hasMatch()) {
            qDebug() << "Failed to capture coin information";
        } else {
            QString coinsStr = coinsMatch.captured(1);
            qDebug() << "Updating coin value for account: " << coinsStr;
        }

        if (accountMatch.hasMatch() && coinsMatch.hasMatch()) {
            QString account = accountMatch.captured(1);
            QString coinsStr = coinsMatch.captured(1);
            qDebug()<<account<<":"<<coinsStr;

            int coins = coinsStr.toInt();
            bool updateResult = updateCoins(account, coins);

            if (updateResult) {
                qDebug() << "Successfully updated coin value for" << account << ": " << coins;
            } else {
                qWarning() << "Failed to update coin value for" << account;
            }

            QByteArray responseData = updateResult ? "true" : "false";//是否成功

            QByteArray response = "HTTP/1.1 200 OK\r\n"
                                  "Content-Length: " + QByteArray::number(responseData.size()) + "\r\n"
                                                                              "Content-Type: text/plain\r\n"
                                                                              "Access-Control-Allow-Origin: *\r\n"
                                                                              "\r\n" +
                                  responseData;


            clientSocket->write(response);
            clientSocket->waitForBytesWritten();
        }
    }
    //############################################################################################################################333
    else {
        qWarning() << "Invalid request received: " << requestString;
        QString invaildRequest="Invalid request received: " + requestString;
        writeToLogFile(invaildRequest);
    }
    clientSocket->disconnectFromHost();
}

//在文件里获取金币数
int HttpServer::getCoinValue(QString account) {
    QFile file("user.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open save file");
        writeToLogFile("Failed to open save file");
        return 0;
    }
    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonArray usersArray = loadDoc.array();

    for (int i = 0; i < usersArray.size(); i++) {
        QJsonObject userObject = usersArray[i].toObject();
        if (userObject["account"].toString() == account) {
            return userObject["coins"].toInt();
        }
    }
    // 没找到用户
    return 0;
}

//检查账号密码是否正确
bool HttpServer::checkLogin(QString account, QString password) {
    QFile file("user.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning("Failed to open save file");
        writeToLogFile("Failed to open save file");
        return false;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonArray usersArray = loadDoc.array();

    QByteArray passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    for (int i = 0; i < usersArray.size(); i++) {
        QJsonObject userObject = usersArray[i].toObject();
        if (userObject["account"].toString() == account) {
            // 找到用户检查密码的hash值
            return userObject["password"].toString() == QString(passwordHash);
        }
    }
    // 没找到用户，创建一个新的用户
    QJsonObject newUser;
    newUser["account"] = account;
    newUser["password"] = QString(passwordHash);
    newUser["coins"] = 0;
    usersArray.append(newUser);
    QJsonDocument saveDoc(usersArray);
    file.close();
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Failed to open save file");
        writeToLogFile("Failed to open save file");
        return false;
    } else {
        file.write(saveDoc.toJson());
        file.close();
    }
    return true;
}

bool HttpServer::updateCoins(QString account, int coins) {
    QFile file("user.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning("Failed to open save file");
        writeToLogFile("Failed to open save file");
        return false;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonArray usersArray = loadDoc.array();

    for (int i = 0; i < usersArray.size(); i++) {
        QJsonObject userObject = usersArray[i].toObject();
        if (userObject["account"].toString() == account) {
            // 找到用户后更新金币
            userObject["coins"] = coins;
            usersArray[i] = userObject; // 更新用户对象
            QJsonDocument saveDoc(usersArray);
            file.resize(0); // 清空文件内容
            file.write(saveDoc.toJson()); // 写入更新后的用户数据
            qDebug () << "changing coins";
            writeToLogFile("changing coins");
            file.close();
            return true;
        }
    }
    // 没有找到用户
    qWarning("Failed to find user: %s", qPrintable(account));
    writeToLogFile("Failed to find user");
    file.close();
    return false;
}

void HttpServer::writeToLogFile(const QString &log){
    QString fileName = "logfile.log"; // 文件名
    QDir logDir("C:/Users/lenovo/Desktop/QtProject/untitled_server");

    if (!logDir.exists()) {
        qWarning() << "Directory does not exist!";
        return;
    }

    QFile logFile(logDir.filePath(fileName));
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)){
        QTextStream logStream(&logFile);
        logStream << log << "/n";
        logFile.close();
    } else {
        qWarning() << "Failed to open log file!";
    }
}
