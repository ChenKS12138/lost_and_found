#include "recordlib.h"
#include <string>
#include <ctime>
#include<fstream>
#include<cstring>
#include<vector>

using namespace std;

template<class T>
int getLength(T& arr)
{
    return sizeof(arr) / sizeof(arr[0]);
}

RecordTime::RecordTime(time_t ut):isEmpty(false){
    this->unixTime = ut;
    this->timeStruct = *localtime(&ut);
}
RecordTime::RecordTime():isEmpty(true){}
RecordTime::RecordTime(RecordTime *p) : unixTime(p->unixTime), timeStruct(p->timeStruct),isEmpty(false){}
void RecordTime::setNow(){
    this->isEmpty = false;
    time_t ut = time(NULL);
    this->unixTime = ut;
    this->timeStruct = *localtime(&ut);
}

time_t RecordTime::toUnixTime(){
    return this->unixTime;
}

string RecordTime::toString()
{
    if(isEmpty)
        return string("");
    string year = to_string(this->timeStruct.tm_year + 1900);
    string month = to_string(timeStruct.tm_mon + 1);
    string day = to_string(timeStruct.tm_mday);
    string hour = to_string(timeStruct.tm_hour);
    string minute = to_string(timeStruct.tm_min);
    string second = to_string(timeStruct.tm_sec);
    return year + "年" + month + "月" + day + "日" + " " + (hour.length()<2?"0"+hour:hour) + ":" + (minute.length()<2?"0"+minute:minute) + ":" + (second.length()<2?"0"+second:second);
}
string RecordTime::toShortString(){
    if(isEmpty)
        return string("");
    string year = to_string(timeStruct.tm_year + 1900);
    string month = to_string(timeStruct.tm_mon + 1);
    string day = to_string(timeStruct.tm_mday);
    return year + "-" + month + "-" + day;
}

bool RecordTime::isLastWeek(){
    int ONE_DAY = 86400;
    RecordTime now;
    now.setNow();
    long diff = now.toUnixTime()-this->toUnixTime();
    return diff < (ONE_DAY*7);
}

bool RecordTime::isLastYear(){
    int ONE_YEAR = 31536000;
    RecordTime now;
    now.setNow();
    long diff = now.toUnixTime() - this->toUnixTime();
    return diff > ONE_YEAR;
}

PersonalInfo::PersonalInfo(const char *n,const char *p,const char *s){
    strcpy(name,n);
    strcpy(phoneNumber, p);
    strcpy(studentID, s);
}
PersonalInfo::PersonalInfo():name(""),phoneNumber(""),studentID(""){}
PersonalInfo::PersonalInfo(PersonalInfo *p) {
    strcpy(name, p->name);
    strcpy(phoneNumber, p->phoneNumber);
    strcpy(studentID, p->studentID);
}
string PersonalInfo::toString(){
    return "姓名:" + string(name) + " 手机号:" + string(phoneNumber) + " 学号:" + string(studentID);
}

string PersonalInfo::getName(){
    return string(this->name);
}

string PersonalInfo::getPhone(){
    return string(this->phoneNumber);
}

string PersonalInfo::getID(){
    return string(this->studentID);
}


Record::Record(const char *n,const char *p, RecordTime &l) : lostTime(l),state(LOST){
        strcpy(name, n);
        strcpy(place, p);
    }
Record::Record(string &n,string &p,RecordTime &l):lostTime(l),state(LOST){
    strcpy(name,n.c_str());
    strcpy(place,p.c_str());
}
Record::Record():state(LOST){}
void Record::verify()
{
    this->state = LOST_AND_VERIFY;
}
string Record::getName(){
    return string(this->name);
}

void Record::pickUp(PersonalInfo *p,RecordTime *pt)
{
    this->state = FOUND;
    this->pickUpTime = new RecordTime(pt);
    this->info = new PersonalInfo(p);
}

void Record::pickUp(PersonalInfo &p, RecordTime &pt){
    pickUp(&p,&pt);
}

string Record::toString(){
    string stateString;
    switch(state){
        case LOST:
            stateString = "等待管理员确认";
        break;
    case LOST_AND_VERIFY:
        stateString = "已由管理员确认";
        break;
    case FOUND:
        stateString = "已被认领";
    default:
        stateString = "";
    }
    return "物品名称:" + string(name) + " 位置:" + string(place)+" 丢失时间:"+lostTime.toString() +" " +stateString;
}
string Record::getLostDay(){
    return lostTime.toString();
}

string Record::getPickUpTime(){
    return this->pickUpTime.toString();
}

string Record::getPlace(){
    return string(this->place);
}

string Record::getState(){
    switch(this->state){
        case LOST:
        return "等待管理员确认";
        break;
    case LOST_AND_VERIFY:
        return "管理员已确认";
        break;
    case FOUND:
        return "已拾取";
        break;
    default:
        return "未知状态";
    }
}

PersonalInfo Record::getInfo(){
    return this->info;
}

RecordTime Record::getLostTime(){
    return this->lostTime;
}

RecordTime Record::getFoundTime(){
    return this->pickUpTime;
}

bool Record::lostTimeComp(Record &a,Record &b){
    return difftime(a.getLostTime().toUnixTime(), b.getLostTime().toUnixTime()) > 0;
}

bool Record::pickUpTimeComp( Record &a,Record &b){
    return difftime(a.getFoundTime().toUnixTime(), b.getFoundTime().toUnixTime()) > 0;
}

Admin::Admin(const char *u,const char *p):isSuper(false){
    strcpy(username, u);
    strcpy(password, p);
}
void Admin::setSuper(){
    this->isSuper = true;
}
Admin::Admin():isSuper(false){}
bool Admin::verify(string u,string p){
    if(u==username&&p==password){
        return true;
    }
    else{
        return false;
    }
}
Admin::Admin(string u,string p):isSuper(false){
    strcpy(username,u.c_str());
    strcpy(password,p.c_str());
}
string Admin::toString()
{
    return (isSuper ? "管理员: " : "学生: ") + string(username);
}
bool Admin::getSuper(){
    return this->isSuper;
}
string Admin::getName(){
    return this->username;
}
string Admin::getPassword(){
    return this->password;
}

string Util::DAT_PATH= "./";
string Util::recordPath(string &filename){
    return "./" + filename + ".txt";
}
bool Util::generateRecord(vector<Record> &r){
    RecordTime t;
    t.setNow();
    string result, filename = t.toShortString();
    for(int i=0,length=r.size();i<length;i++){
        result+=(r[i].toString()+"\n");
    }
    ofstream outF(recordPath(filename), ios::out);
    if(outF.is_open()){
        outF<<result<<endl;
        outF.close();
        return true;
    }
    else{
        return false;
    }
}

bool Util::generateRecord(vector<Record> &r,string filename){
    string result;
    for(int i=0,length=r.size();i<length;i++){
        result+=(r[i].toString()+"\n");
    }
    ofstream outF(recordPath(filename), ios::out);
    if(outF.is_open()){
        outF<<result<<endl;
        outF.close();
        return true;
    }
    else{
        return false;
    }
}
