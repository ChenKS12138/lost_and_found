#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QString>
#include<string>
#include<iostream>
#include<fstream>
#include<ctime>

using namespace std;

template<class T>
int getLength(T& arr)
{
  return sizeof(arr) / sizeof(arr[0]);
}

enum RecordState
{
  LOST,
  LOST_AND_VERIFY,
  FOUND
};

enum RecordType
{
  DEVICE,
  BOOK,
  STATIONERY,
  OTHER
};

class RecordTime
{
  private:
    time_t unixTime;
    tm timeStruct;
  public:
    RecordTime(time_t ut = time(NULL)) : unixTime(ut){
      timeStruct = *localtime(&ut);
    }
    RecordTime(RecordTime *p) : unixTime(p->unixTime), timeStruct(p->timeStruct){}
    string toString()
    {
      string year = to_string(timeStruct.tm_year + 1900);
      string month = to_string(timeStruct.tm_mon + 1);
      string day = to_string(timeStruct.tm_mday);
      string hour = to_string(timeStruct.tm_hour);
      string minute = to_string(timeStruct.tm_min);
      string second = to_string(timeStruct.tm_sec);
      return year + "年" + month + "月" + day + "日" + " " + (hour.length()<2?"0"+hour:hour) + ":" + (minute.length()<2?"0"+minute:minute) + ":" + (second.length()<2?"0"+second:second);
    }
    string toShortString(){
      string year = to_string(timeStruct.tm_year + 1900);
      string month = to_string(timeStruct.tm_mon + 1);
      string day = to_string(timeStruct.tm_mday);
      return year + "-" + month + "-" + day;
    }
    static void sort(RecordTime *data ,int length){
      for (int i = 0; i < length; i++)
      {
        for (int j = i + 1; j < length;j++){
          if(data[j].unixTime>data[i].unixTime){
            RecordTime *temp = new RecordTime(data[i]);
            data[i] = data[j];
            data[j] = *temp;
            delete temp;
          }
        }
      }
    }
};

class PersonalInfo{
  public:
    string name,phoneNumber,studentID;
    PersonalInfo(const string n,const string p,const string s):name(n),phoneNumber(p),studentID(s){ }
    PersonalInfo() : name(string()), phoneNumber(string()), studentID(string()){}
    PersonalInfo(PersonalInfo *p) : name(p->name), phoneNumber(p->phoneNumber), studentID(p->studentID) {}
    string toString(){
      return "姓名:" + name + " 手机号:" + phoneNumber + " 学号:" + studentID;
    }
};

class Record
{
  private:
    string name;
    string place;
    RecordTime *lostTime,*pickUpTime;
    RecordState state;
    PersonalInfo *info;
    RecordType *type;
  public:
    Record(const string n,const string p, RecordTime *l) :name(n), place(p), lostTime(l),state(LOST){
      this->info = NULL;
      this->type = NULL;
      this->pickUpTime = NULL;
    }
    ~Record(){
      delete this->info;
      delete this->type;
      delete this->lostTime;
      delete this->pickUpTime;
    }
    void verify(){
      this->state = LOST_AND_VERIFY;
    };
    void pickUp(PersonalInfo *p,RecordTime *pt)
    {
      this->state = FOUND;
      this->pickUpTime = new RecordTime(pt);
      this->info = new PersonalInfo(p);
    }
    string toString(){
      return "物品名称:" + name + " 位置:" + place+" 丢失时间:"+lostTime->toString();
    }
    string getLostDay(){
      return lostTime->toShortString();
    }
};

class Admin{
  private:
    bool isSuper;
    string username;
    string password;
  public:
    Admin(string u, string p) : username(u), password(p),isSuper(false){}
    void setSuper(){
      this->isSuper = true;
    }
    Admin() : username(string()), password(string()),isSuper(false){}
    bool vefify(string u,string p){
      if(u==username&&p==password){
        return true;
      }
      else{
        return false;
      }
    }
    string toString()
    {
      return (isSuper ? "管理员: " : "学生: ") + username;
    }
};

class Util{
  public:
    static const string DAT_PATH;
    static string recordPath(string &filename){
      return "/mnt/d/74992/Documents/lost_and_found/data/" + filename + ".txt";
    };
    template <class T>
    static bool setStorage(T source)
    {
      ostream ofile(DAT_PATH);

    }
    template<class T>
    static T getStorage(){

    }
    static bool appendRecord( Record &r){
      string filename = r.getLostDay();
      ofstream outF(recordPath(filename),ifstream::app);
      if(outF.is_open()){
        outF << r.toString() << endl;
      }
      else{
        return false;
      }
    }
    static bool appendRecord(Record *r){
      return appendRecord(*r);
    }
};
const string Util::DAT_PATH = "/mnt/d/74992/Documents/lost_and_found/data/data.dat";

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
    Admin a = Admin("root","root");
    a.setSuper();
    if(!a.vefify(username,password)){
        QMessageBox::information(this,QString::fromLocal8Bit("ERROR"),QString::fromLocal8Bit("Wrong username or password"));
    }
    else{
        this->app_win = new AppWindow();
        this->app_win->show();
        this->close();
    }
}
