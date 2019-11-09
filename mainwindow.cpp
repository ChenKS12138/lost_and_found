#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recordlib.h"
#include<iostream>
#include<vector>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login(Admin a){
    this->app_win = new AppWindow(a);
    this->app_win->show();
    this->close();
    return;
}

void MainWindow::on_pushButton_clicked()
{
    string username = ui->username->text().toStdString();
    string password = ui->password->text().toStdString();
    vector<Admin> allAdmin = Util::getStorageSync<Admin>("admin");
    Admin super("root","root");
    super.setSuper();
    allAdmin.push_back(super);
    for(int i=0,length=allAdmin.size();i<length;i++){
        if(allAdmin[i].verify(username,password)){
            this->login(allAdmin[i]);
            return;
        }
    }
    QMessageBox::about(NULL, "ERROR", "请检查用户名和密码");
}
