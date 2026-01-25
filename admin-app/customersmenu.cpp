#include "customersmenu.h"
#include "ui_customersmenu.h"
#include <QStandardItemModel>

customersmenu::customersmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::customersmenu)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->btnGetCustomers, &QPushButton::clicked, this, &customersmenu::btnGetCustomers);
    connect(ui->btnAddNewCustomer, &QPushButton::clicked, this, &customersmenu::btnAddNewCustomerMenuSlot);
}

customersmenu::~customersmenu()
{
    delete ui;
}

QString customersmenu::getCustomer_base_url() const
{
    return "api/customer";
}

void customersmenu::setToken(const QByteArray &newToken)
{
    token = newToken;
}

void customersmenu::btnGetCustomers()
{
    QString url = environment::base_url() + getCustomer_base_url();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // WEB TOKEN ALKU
    QByteArray myToken = "Bearer " + this->token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    // WEB TOKEN LOPPU

    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &customersmenu::showCustomerSlot);

}

void customersmenu::showCustomerSlot()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Netwrk error:" << reply->errorString();
        reply->deleteLater();
        manager->deleteLater();
        return;
    }

    QByteArray response_data = reply ->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    customerList.clear();

    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            Customer customer = Customer::mapJson(value.toObject());
            qDebug() << "Test1:" << customer.fname << " " << customer.lname;
            customerList.append(customer);
        }
    }

    customersToTableSlot(customerList);
}

void customersmenu::customersToTableSlot(const QVector<Customer> &customers)
{
    auto *tableModel = new QStandardItemModel(customers.size(), 5, this);
    tableModel -> setHorizontalHeaderLabels({ tr("CustomerID"), tr("First name"), tr("Last name"), tr("Street address"), tr("City") });

    for (int row = 0; row < customers.size(); ++row) {
        const Customer &book = customers[row];
        tableModel->setItem(row, 0, new QStandardItem(QString::number(book.idCustomer)));
        tableModel->setItem(row, 1, new QStandardItem(book.fname));
        tableModel->setItem(row, 2, new QStandardItem(book.lname));
        tableModel->setItem(row, 3, new QStandardItem(book.streetAddress));
        tableModel->setItem(row, 4, new QStandardItem(book.city));
    }
    ui->tableCustomers->setModel(tableModel);
    ui->tableCustomers->verticalHeader()->setVisible(false);
    ui->tableCustomers->resizeColumnsToContents();
}

void customersmenu::btnAddNewCustomerMenuSlot()
{
    addcustomermenu *objAddCustomerMenu = new addcustomermenu(this);
    objAddCustomerMenu->setToken(token);
    objAddCustomerMenu->show();
}


