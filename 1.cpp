#include <iostream>
#include<fstream>
#include<vector>
#include<cstring>

using namespace std;

class Test{
  public:
    char a[30];
    Test(const char *aa){
      strcpy(a, aa);
    }
    Test(){}
};

class Util
{
public:
  static string DAT_PATH;
  template <class T>
  static vector<T> getStorageSync(const char *filename)
  {
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
  template<class T>
  static bool setStorageSync(const char *filename,vector<T> &t){
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
string Util::DAT_PATH = "./";

int main(void){
  Test a[2] = {Test("hello"), Test("hola")};
  vector<Test> all;
  all.push_back(a[0]);
  all.push_back(a[1]);
  Util::setStorageSync<Test>("test", all);
  vector<Test> all_2 = Util::getStorageSync<Test>("test");
  for (int i = 0; i < all_2.size();i++){
    cout << all_2[i].a << endl;
  }
}