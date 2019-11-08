#ifndef RECORDLIB_H
#define RECORDLIB_H

#include <string>
#include <ctime>
#include<fstream>
#include<cstring>
#include<vector>

using namespace std;


template<class T>
int getLength(T &arr);

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

class RecordTime{
private:
    time_t unixTime;
    tm timeStruct;
    bool isEmpty;

public:
    RecordTime(time_t ut);
    RecordTime();
    RecordTime(RecordTime *p);
    string toString();
    string toShortString();
    void setNow();
    static void sort(RecordTime *data, int length);
};

class PersonalInfo{
public:
    char name[30],phoneNumber[30],studentID[30];
    PersonalInfo(const char *n,const char *p,const char*s);
    PersonalInfo();
    PersonalInfo(PersonalInfo *p);
    string toString();
    string getName();
    string getPhone();
    string getID();
};
class Record{
private:
  char name[30],place[30];
  RecordTime lostTime,pickUpTime;
  RecordState state;
  PersonalInfo info;
  RecordType type;
public:
    Record(const char *n,const char *p,RecordTime &l);
    Record();
    Record(string &n,string &p,RecordTime &l);
    void verify();
    void pickUp(PersonalInfo *p,RecordTime *pt);
    string toString();
    string getLostDay();
    string getName();
    string getPickUpTime();
    string getPlace();
    string getState();
    PersonalInfo getInfo();
};

class Admin{
private:
    bool isSuper;
    char username[30],password[30];
public:
    Admin(const char*u,const char *p);
    void setSuper();
    Admin();
    bool vefify(string u,string p);
    string toString();
    bool getSuper();
    string getName();
};

class Util{
public:
    static string DAT_PATH;
    static string recordPath(string &filename);
    static bool generateRecord(Record &r);
    static bool generateRecord(Record *r);
    static bool addAdmin(Admin &a);
    static bool addRecord(Record &a);
    static vector<Admin> getAdmin();
    static vector<Record> getRecord();
    static bool syncAdmin(vector<Admin> &a);
    static bool syncRecord(vector<Record> &r);
    
    template <class T>
    static vector<T> getStorageSync(const char filename[]){
        vector<T> dest;
        ifstream inF(DAT_PATH + string(filename) + ".dat", ios::in | ios::binary);
        if (inF.is_open())
        {
          T temp;
          while (inF.read((char *)&temp, sizeof(T)))
          {
            dest.push_back(temp);
          }
          inF.close();
          return dest;
        }
    }

    template <class T>
    static bool setStorageSync(const char filename[], vector<T> &t){
        try{
            ofstream outF(DAT_PATH + string(filename) + ".dat", ios::out | ios::binary);
            if(outF.is_open()){
                T *ta = new T[t.size()];
                memcpy(ta, &t[0], t.size() * sizeof(t[0]));
                outF.write((char *)ta, sizeof(ta[0])*t.size());
                outF.close();
                delete ta;
                return true;
            }
        }
        catch(exception e){
            return false;
        }
    }
};

#endif // RECORDLIB_H
