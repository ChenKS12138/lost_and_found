#include<iostream>
#include<string>
#include<ctime>
#include<fstream>

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

class Time
{
  private:
    time_t unixTime;
    tm timeStruct;
  public:
    Time(time_t ut = time(NULL)) : unixTime(ut){
      timeStruct = *localtime(&ut);
    };
    Time(Time *p) : unixTime(p->unixTime), timeStruct(p->timeStruct){};
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
    static void sort(Time *data ,int length){
      for (int i = 0; i < length; i++)
      {
        for (int j = i + 1; j < length;j++){
          if(data[j].unixTime>data[i].unixTime){
            Time *temp = new Time(data[i]);
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
    PersonalInfo(PersonalInfo *p):name(p->name),phoneNumber(p->phoneNumber),studentID(p->studentID){}
    string toString(){
      return "姓名:" + name + " 手机号:" + phoneNumber + " 学号:" + studentID;
    }
};

class Record
{
  private:
    string name;
    string place;
    Time *lostTime,*pickUpTime;
    RecordState state;
    PersonalInfo *info;
    RecordType *type;
  public:
    Record(const string n,const string p, Time *l) :name(n), place(p), lostTime(l),state(LOST){
      this->info = NULL;
      this->type = NULL;
      this->pickUpTime = NULL;
    };
    ~Record(){
      delete this->info;
      delete this->type;
      delete this->lostTime;
      delete this->pickUpTime;
    }
    void verify(){
      this->state = LOST_AND_VERIFY;
    };
    void pickUp(PersonalInfo *p,Time *pt)
    {
      this->state = FOUND;
      this->pickUpTime = new Time(pt);
      this->info = new PersonalInfo(p);
    }
    string toString(){
      return "物品名称" + name + "位置" + place;
    }
};

class Admin{
  private:
    bool isSuper;
    string username;
    string password;
  public:
    Admin(string u, string p) : username(u), password(p),isSuper(false){};
    void setSuper(){
      this->isSuper = true;
    }
    string toString(){
      return (isSuper ? "管理员: " : "学生: ") + username;
    }
};

class Util{
  static const string DLL_PATH;
  static string recordPath(string &filename){
    return "D:\\LOST_FOUND\\" + filename + ".txt";
  };
  template <class T>
  static bool setStorage(T source)
  {
    ostream ofile(PATH);
    
  }
  template<class T>
  static T getStorage(){

  }
  static bool appendRecord(Record &r){
    
  }
};
const string Util::DLL_PATH = "D:\\LOST_FOUND\\data.dll";

int main(){
  PersonalInfo *p = new PersonalInfo("陈凯森", "19805182292","B18030721");
}