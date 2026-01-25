#ifndef CUSTOMERSMENU_H
#define CUSTOMERSMENU_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include "environment.h"
#include "customer.h"
#include "addcustomermenu.h"

namespace Ui {
class customersmenu;
}

class customersmenu : public QDialog
{
    Q_OBJECT

public:
    explicit customersmenu(QWidget *parent = nullptr);
    ~customersmenu();

    QString getCustomer_base_url() const;

    void setToken(const QByteArray &newToken);

private:
    Ui::customersmenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString customer_base_url;
    QByteArray response_data;
    QByteArray token;
    QVector<Customer> customerList;


private slots:
    void btnGetCustomers();
    void showCustomerSlot();
    void customersToTableSlot(const QVector<Customer> &customers);
    void btnAddNewCustomerMenuSlot();
};

#endif // CUSTOMERSMENU_H
