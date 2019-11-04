#include<iostream>
#include<string>
#include<ctime>
using namespace std;
enum RecordState
{
  LOST,
  LOST_AND_VERIFY,
  FOUND
};

enum RecordType
{
  STORAGE,
  BOOK,
  STATIONERY,
  OTHER
};

class Time
{
  public:
    int year,month,day,hour,minute;
    Time() : year(1970), month(1), day(1),hour(0),minute(0){};
    Time(int const y, int const m, int const d,int const h,int const min) : year(y), month(m), day(d),hour(h),minute(min){};
    
    string toString(){
      return to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日" +to_string(hour)+"时"+to_string(minute)+"分";
    };
    long int toNumber(){
      return year * 100000000 + month * 1000000 + day * 10000 + hour * 10 + minute;
    };
    
    void setState(int const y, int const m, int const d)
    {
      this->year = y;
      this->month = m;
      this->day = d;
    };
    static int sort(Time data[],bool isASC = false){
      for (int i = 0,length = sizeof(data) / sizeof(Time); i < length;i++){
        for (int j = i+1; j < length;j++){
          if(data[j].toNumber()>data[i].toNumber()){
            Time *temp = new Time(data[i]);
            data[i] = data[j];
            data[j] = *temp;
          }
        }
      }
    };
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
    string place;
    Time lostTime,pickUpTime;
    RecordState state;
    PersonalInfo *info;
    RecordType *type;

  public:
    Record(const string p, const Time l) : place(p), lostTime(l){};

    void verify(){
      this->state = LOST_AND_VERIFY;
    };
    void pickUp(PersonalInfo *p)
    {
      this->state = FOUND;
      this->info = new PersonalInfo(p);
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
};
void main(){
  Admin *root = new Admin("root", "root");
}