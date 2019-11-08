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

void MainWindow::on_pushButton_clicked()
{
    string username = ui->username->text().toStdString();
    string password = ui->password->text().toStdString();
    if(username=="root"&&password=="root"){
        Admin a("root","root");
        a.setSuper();
        this->app_win = new AppWindow(a);
        this->app_win->show();
        this->close();
        return;
    };
    // vector<Admin> allAdmin = Util::getAdmin();
    vector<Admin> allAdmin = Util::getStorageSync<Admin>("admin");
    for (int i = 0, length = allAdmin.size(); i < length; i++)
    {
        cout<<allAdmin[i].toString()<<endl;
        if(allAdmin[i].vefify(username,password)){
            this->app_win = new AppWindow(allAdmin[i]);
            this->app_win->show();
            this->close();
            return;
        }
    }

}
