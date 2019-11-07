#include "appwindow.h"
#include "ui_appwindow.h"
#include "recordlib.h"
#include <vector>
#include<QString>
#include<QInputDialog>
#include<iostream>
#include<QString>

using namespace std;

AppWindow::AppWindow(Admin a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppWindow)
{
    ui->setupUi(this);
    ui->welcome->setText(QString::fromStdString("你好, "+string(a.getName())));
    if(a.getSuper()){
        ui->confirmRecord->setDisabled(false);
        ui->manageAdmin->setDisabled(false);
        ui->found->setDisabled(false);
    }
    ui->recordTable->setColumnCount(8);
    ui->recordTable->setColumnWidth(0,120);
    ui->recordTable->setColumnWidth(1,120);
    ui->recordTable->setColumnWidth(2,120);
    ui->recordTable->setColumnWidth(3,120);
    ui->recordTable->setColumnWidth(4,120);
    ui->recordTable->setColumnWidth(5,120);
    ui->recordTable->setColumnWidth(6,120);
    ui->recordTable->setColumnWidth(7,200);
    ui->recordTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->recordTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->recordTable->verticalHeader()->setVisible(true);
    QStringList sListHeader;
    sListHeader<<"物品名称"<<"丢失时间"<<"丢失地点"<<"状态"<<"认领人姓名"<<"认领人学号"<<"认领人学号"<<"认领时间";
    ui->recordTable->setHorizontalHeaderLabels(sListHeader);
    vector<Record> allRecord = Util::getRecord();
    int length = allRecord.size();
    ui->recordTable->setRowCount(length);
    for(int i=0;i<length;i++){
        string name = allRecord[i].getName();
        string lostTime = allRecord[i].getLostDay();
        string place = allRecord[i].getPlace();
        string state = allRecord[i].getState();
        string personName =allRecord[i].getInfo().getName();
        string personPhone =allRecord[i].getInfo().getPhone();
        string personId =allRecord[i].getInfo().getID();
        string pickUpTime =allRecord[i].getPickUpTime();
        ui->recordTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(name)));
        ui->recordTable->setItem(i,1,new QTableWidgetItem(QString::fromStdString(lostTime)));
        ui->recordTable->setItem(i,2,new QTableWidgetItem(QString::fromStdString(place)));
        ui->recordTable->setItem(i,3,new QTableWidgetItem(QString::fromStdString(state)));
        ui->recordTable->setItem(i,4,new QTableWidgetItem(QString::fromStdString(personName)));
        ui->recordTable->setItem(i,5,new QTableWidgetItem(QString::fromStdString(personPhone)));
        ui->recordTable->setItem(i,6,new QTableWidgetItem(QString::fromStdString(personId)));
        ui->recordTable->setItem(i,7,new QTableWidgetItem(QString::fromStdString(pickUpTime)));
    }

}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::on_pushButton_clicked()
{
    bool nameOk,placeOk;
    string nameText = QInputDialog::getText(NULL, "新建记录","请输入物品名称",QLineEdit::Normal,"物品名称",&nameOk).toStdString();
    if(!nameOk) return;
    string placeText = QInputDialog::getText(NULL, "新建记录","请输入丢失地点",QLineEdit::Normal,"物品地点",&placeOk).toStdString();
    if(!placeOk) return;
    RecordTime t;
    t.setNow();
    Record a(nameText,placeText,t);
    Util::generateRecord(a);
    Util::addRecord(a);
    vector<Record> allRecord = Util::getRecord();
    ui->recordTable->clear();
    int length = allRecord.size();
    ui->recordTable->setRowCount(length);
    for(int i=0;i<length;i++){
        string name = allRecord[i].getName();
        string lostTime = allRecord[i].getLostDay();
        string place = allRecord[i].getPlace();
        string state = allRecord[i].getState();
        string personName =allRecord[i].getInfo().getName();
        string personPhone =allRecord[i].getInfo().getPhone();
        string personId =allRecord[i].getInfo().getID();
        string pickUpTime =allRecord[i].getPickUpTime();
        ui->recordTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(name)));
        ui->recordTable->setItem(i,1,new QTableWidgetItem(QString::fromStdString(lostTime)));
        ui->recordTable->setItem(i,2,new QTableWidgetItem(QString::fromStdString(place)));
        ui->recordTable->setItem(i,3,new QTableWidgetItem(QString::fromStdString(state)));
        ui->recordTable->setItem(i,4,new QTableWidgetItem(QString::fromStdString(personName)));
        ui->recordTable->setItem(i,5,new QTableWidgetItem(QString::fromStdString(personPhone)));
        ui->recordTable->setItem(i,6,new QTableWidgetItem(QString::fromStdString(personId)));
        ui->recordTable->setItem(i,7,new QTableWidgetItem(QString::fromStdString(pickUpTime)));
    }
}

void AppWindow::on_pushButton_2_clicked()
{
    //点击认领
}

void AppWindow::on_pushButton_3_clicked()
{
    // 点击管理管理员
}

void AppWindow::on_confirmRecord_clicked()
{
    //点击确认记录
}
