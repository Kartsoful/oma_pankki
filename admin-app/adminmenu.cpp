#include "adminmenu.h"
#include "ui_adminmenu.h"

adminmenu::adminmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adminmenu)
{
    ui->setupUi(this);
    connect(ui->btnCustomers, &QPushButton::clicked, this, &adminmenu::btnCustomersMenu);
}

adminmenu::~adminmenu()
{
    delete ui;
}

void adminmenu::setToken(const QByteArray &newToken)
{
    token = newToken;
}

void adminmenu::btnCustomersMenu()
{
    customersmenu *objCustomersMenu = new customersmenu(this);
    objCustomersMenu->setToken(token);
    objCustomersMenu->show();
}

