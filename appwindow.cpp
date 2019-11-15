#include "appwindow.h"
#include "ui_appwindow.h"
#include "recordlib.h"
#include <vector>
#include<QString>
#include<QInputDialog>
#include<iostream>
#include<QString>
#include<vector>
#include<algorithm>
#include<QMessageBox>

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
        ui->removeRecord->setDisabled(false);\
        ui->removeAll->setDisabled(false);
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
    ui->recordTable->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->recordTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->recordTable->verticalHeader()->setVisible(true);
//    QHeaderView *header = ui->recordTable->horizontalHeader();
//    header->setSortIndicator(1,Qt::AscendingOrder);
//    header->setSortIndicator(1,Qt::DescendingOrder);
//    header->setSortIndicator(6,Qt::AscendingOrder);
//    header->setSortIndicator(6,Qt::DescendingOrder);
//    header->setSortIndicatorShown(true);
//    connect(header, SIGNAL(sectionClicked(int)), ui->recordTable, SLOT (sortByColumn(int)));
    QStringList sListHeader;
    sListHeader<<"物品名称"<<"丢失时间"<<"丢失地点"<<"状态"<<"认领人姓名"<<"认领人学号"<<"认领人学号"<<"认领时间";
    ui->recordTable->setHorizontalHeaderLabels(sListHeader);
    vector<Record> allRecord = Util::getStorageSync<Record>("record");
    this->syncTable(allRecord);
}


AppWindow::~AppWindow()
{
    delete ui;
}


void AppWindow::syncTable(vector<Record> &allRecord){
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

int AppWindow::getSelectedSingleRow(){
    QList<QTableWidgetSelectionRange> ranges =ui->recordTable->selectedRanges();
    int length = ranges.length();
    if(length!=0){
        return ranges[0].topRow();
    }
    else{
        return -1;
    }
}

void AppWindow::on_newRecord_clicked()
{
    bool nameOk,placeOk;
    string nameText = QInputDialog::getText(NULL, "新建记录","请输入物品名称",QLineEdit::Normal,"物品名称",&nameOk).toStdString();
    if(!nameOk) return;
    string placeText = QInputDialog::getText(NULL, "新建记录","请输入丢失地点",QLineEdit::Normal,"物品地点",&placeOk).toStdString();
    if(!placeOk) return;
    RecordTime t;
    t.setNow();
    Record a(nameText,placeText,t);
    vector<Record> allRecord = Util::getStorageSync<Record>("record");
    allRecord.push_back(a);
    Util::setStorageSync("record",allRecord);
    this->syncTable(allRecord);
    QMessageBox::about(NULL, "SUCCESS", "记录创建成功");
}

void AppWindow::on_found_clicked()
{
    //点击认领
    bool nameOk,phoneOk,idOk;
    string nameText = QInputDialog::getText(NULL, "认领物品","请输入认领人名称",QLineEdit::Normal,"认领人名称",&nameOk).toStdString();
    if(!nameOk) return;
    string phoneText = QInputDialog::getText(NULL, "认领物品","请输入认领人手机号",QLineEdit::Normal,"认领人手机号",&phoneOk).toStdString();
    if(!phoneOk) return;
    string idText = QInputDialog::getText(NULL, "认领物品","请输入认领人学号",QLineEdit::Normal,"认领人学号",&idOk).toStdString();
    if(!idOk) return;
    PersonalInfo p(nameText.c_str(),phoneText.c_str(),idText.c_str());
    RecordTime t;
    t.setNow();
    vector<Record> allRecord = Util::getStorageSync<Record>("record");
    allRecord[this->getSelectedSingleRow()].pickUp(p,t);
    Util::setStorageSync<Record>("record",allRecord);
    this->syncTable(allRecord);
    QMessageBox::about(NULL, "SUCCESS", "认领成功");
}

void AppWindow::on_confirmRecord_clicked()
{
    //点击确认记录
    vector<Record> allRecord = Util::getStorageSync<Record>("record");
    allRecord[this->getSelectedSingleRow()].verify();
    Util::setStorageSync<Record>("record",allRecord);
    this->syncTable(allRecord);
}


void AppWindow::on_manageAdmin_clicked()
{
    // 点击管理管理员
    this->admin_win = new AdminWindow();
    this->admin_win->show();
}

void AppWindow::on_removeAll_clicked()
{
    vector<Record> allRecord;
    Util::setStorageSync<Record>("record",allRecord);
    this->syncTable(allRecord);
    QMessageBox::about(NULL, "SUCCESS", "所有记录已删除");
}

void AppWindow::on_removeRecord_clicked()
{
    int index = this->getSelectedSingleRow();
    if(index!=-1){
        vector<Record> allRecord = Util::getStorageSync<Record>("record");
        allRecord.erase(allRecord.begin()+index);
        Util::setStorageSync<Record>("record",allRecord);
        this->syncTable(allRecord);
        QMessageBox::about(NULL, "SUCCESS", "记录已删除");
    }
    else{
        QMessageBox::about(NULL, "ERROR", "请选择一项记录");
    }
}

void AppWindow::on_sortByLost_clicked()
{
    // 点击按丢失时间排序
    vector<Record> allRecord = Util::getStorageSync<Record>("record");
    sort(allRecord.begin(),allRecord.end(),Record::lostTimeComp);
    if(this->isSortByLostDesc){
       reverse(allRecord.begin(),allRecord.end());
    }
    this->isSortByLostDesc = !this->isSortByLostDesc;
    this->syncTable(allRecord);
}

void AppWindow::on_sortByFound_clicked()
{
    // 点击按拾取时间排序
    vector<Record> allRecord = Util::getStorageSync<Record>("record");
    sort(allRecord.begin(),allRecord.end(),Record::pickUpTimeComp);
    if(this->isSortByFoundDesc){
        reverse(allRecord.begin(),allRecord.end());
    }
    this->isSortByFoundDesc = !this->isSortByFoundDesc;
    this->syncTable(allRecord);
}

void AppWindow::on_exportRecord_clicked()
{
    // 点击导出文本
    vector<Record> allRecord = Util::getStorageSync<Record>("record");
    Util::generateRecord(allRecord);
    QMessageBox::about(NULL, "SUCCESS", "记录已成功导出");
}

void AppWindow::on_export_last_week_clicked()
{
    vector<Record> allRecord = Util::getStorageSync<Record>("record");
    vector<Record> lastWeek;
    for(int i=0,length=allRecord.size();i<length;i++){
        if(allRecord[i].getLostTime().isLastWeek()){
            lastWeek.push_back(allRecord[i]);
        }
    }
    Util::generateRecord(lastWeek,"last_week_record");
    QMessageBox::about(NULL, "SUCCESS", "上周的记录已成功导出");
}
