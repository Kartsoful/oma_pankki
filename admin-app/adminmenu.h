#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "environment.h"
#include "customersmenu.h"

namespace Ui {
class adminmenu;
}

class adminmenu : public QDialog
{
    Q_OBJECT

public:
    explicit adminmenu(QWidget *parent = nullptr);
    ~adminmenu();

    void setToken(const QByteArray &newToken);

private:
    Ui::adminmenu *ui;
    QByteArray token;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

private slots:
    void btnCustomersMenu();
};

#endif // ADMINMENU_H
