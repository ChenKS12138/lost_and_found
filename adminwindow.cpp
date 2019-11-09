#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "recordlib.h"
#include <vector>
#include<QString>
#include<QInputDialog>
#include<iostream>

using namespace std;

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    ui->adminTable->setColumnCount(3);
    ui->adminTable->setColumnWidth(0,120);
    ui->adminTable->setColumnWidth(1,120);
    ui->adminTable->setColumnWidth(2,120);
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

int AdminWindow::getSelectedSingleRow(){
    QList<QTableWidgetSelectionRange> ranges =ui->adminTable->selectedRanges();
    int length = ranges.length();
    if(length!=0){
        return ranges[0].topRow();
    }
    else{
        return -1;
    }
}

void AdminWindow::on_addAdmin_clicked()
{
    //点击添加管理员
    bool usernameOk,passwordOk;
    string usernameText = QInputDialog::getText(NULL, "新建管理员","请输入管理员名称",QLineEdit::Normal,"管理员名称",&usernameOk).toStdString();
    if(!usernameOk) return;
    string passwordText = QInputDialog::getText(NULL,"新建管理员","请输入管理员密码",QLineEdit::Normal,"管理员密码",&passwordOk).toStdString();
    if(!passwordOk) return;
    Admin tempAdmin(usernameText,passwordText);
    vector<Admin> allAdmin = Util::getStorageSync<Admin>("admin");
    allAdmin.push_back(tempAdmin);
    Util::setStorageSync("admin",allAdmin);
    this->syncTalbe(allAdmin);
}


void AdminWindow::on_removeAdmin_clicked()
{
    //点击移除管理员
    int index = this->getSelectedSingleRow();
    if(index != -1){
        vector<Admin> allAdmin = Util::getStorageSync<Admin>("admin");
        allAdmin.erase(allAdmin.begin()+index);
        Util::setStorageSync<Admin>("admin",allAdmin);
        this->syncTalbe(allAdmin);
    }
}
