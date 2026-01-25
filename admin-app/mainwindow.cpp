#include "adminmenu.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::btnLoginSlot);
    manager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnLoginSlot()
{
    QString url = environment::base_url()+"login";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject jObject;
    jObject.insert("idcard", ui->textCardId->text());
    jObject.insert("pin", ui->textPin->text());
    QJsonDocument jsonDoc(jObject);
    reply = manager->post(request, jsonDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, &MainWindow::loginAction);
}

void MainWindow::loginAction()
{
    QByteArray responseData = reply->readAll();
    if (responseData.length()==0) {
        ui->labelInfo->setText("Tarkista backend");
        qDebug()<<"Tarkista backend";
    } else {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonDoc.object();
        if(jsonObject.contains("token")) {
            QString token = jsonObject["token"].toString();
            QByteArray tokenBytes = token.toUtf8();
            adminmenu *objAdminMenu = new adminmenu(this);
            objAdminMenu->setToken(tokenBytes);
            objAdminMenu->show();
        }

        if(jsonObject.value("message").toString()== "Tunnus lukittu"){
            ui->labelInfo->setText("Tunnus lukittu");
            ui->labelInfo->show();

            QTimer::singleShot(3000, this, [this]() {
                ui->labelInfo->clear();
            });

            ui->textCardId->clear();
            ui->textPin->clear();
        }
        qDebug()<<jsonObject;
        qDebug()<<responseData;
    }
    reply->deleteLater();
}
