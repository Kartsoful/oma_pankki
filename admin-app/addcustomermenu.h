#ifndef ADDCUSTOMERMENU_H
#define ADDCUSTOMERMENU_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "environment.h"

namespace Ui {
class addcustomermenu;
}

class addcustomermenu : public QDialog
{
    Q_OBJECT

public:
    explicit addcustomermenu(QWidget *parent = nullptr);
    ~addcustomermenu();
    QString getCustomerAdd_base_url() const;
    void setToken(const QByteArray &newToken);

private:
    Ui::addcustomermenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray token;
    QByteArray response_data;
    /*
    QString lname;
    QString fname;
    QString streetAddress;
    QString city;
    */

private slots:
    void btnGetCustomerData();
    void addCustomerSlot();
};

#endif // ADDCUSTOMERMENU_H
