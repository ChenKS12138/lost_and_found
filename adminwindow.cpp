#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "recordlib.h"
#include <vector>
#include<QString>
#include<QInputDialog>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    ui->adminTable->setColumnCount(3);
    ui->adminTable->setColumnWidth(0,80);
    ui->adminTable->setColumnWidth(1,80);
    ui->adminTable->setColumnWidth(2,80);
    ui->adminTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->adminTable->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->adminTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->adminTable->verticalHeader()->setVisible(true);
    QStringList sListHeader;
    sListHeader<<"账号"<<"密码"<<"类型";
    ui->adminTable->setHorizontalHeaderLabels(sListHeader);
    vector<Admin> allAdmin = Util::getStorageSync<Admin>("admin");
    this->syncTalbe(allAdmin);
}

void AdminWindow::syncTalbe(vector<Admin> &allAdmin){
    int length = allAdmin.size();
    ui->adminTable->setRowCount(length);
    for(int i=0;i<length;i++){
        string username = allAdmin[i].getName();
        string password = allAdmin[i].getPassword();
        string type("普通管理员");
        ui->adminTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(username)));
        ui->adminTable->setItem(i,1,new QTableWidgetItem(QString::fromStdString(password)));
        ui->adminTable->setItem(i,2,new QTableWidgetItem(QString::fromStdString(type)));
    }
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
