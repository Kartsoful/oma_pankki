#include "addcustomermenu.h"
#include "ui_addcustomermenu.h"

addcustomermenu::addcustomermenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addcustomermenu)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->btnSendCustomerData, &QPushButton::clicked, this, &addcustomermenu::btnGetCustomerData);
}

addcustomermenu::~addcustomermenu()
{
    delete ui;
}

QString addcustomermenu::getCustomerAdd_base_url() const
{
    return "api/customer";
}

void addcustomermenu::setToken(const QByteArray &newToken)
{
    token = newToken;
}

void addcustomermenu::btnGetCustomerData()
{
    QString url = environment::base_url() + addcustomermenu::getCustomerAdd_base_url();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject customerObject;
    customerObject.insert("fname", ui->textFirstName->text());
    customerObject.insert("lname", ui->textLastName->text());
    customerObject.insert("street_address", ui->textStreetAddress->text());
    customerObject.insert("city", ui->textCity->text());

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    QJsonDocument customerJsonDoc(customerObject);
    reply = manager->post(request, customerJsonDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, &addcustomermenu::addCustomerSlot);
}

void addcustomermenu::addCustomerSlot()
{
    response_data = reply->readAll();
    qDebug() << response_data;
    reply->deleteLater();
}

