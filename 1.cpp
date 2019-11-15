#include<iostream>
#include<ctime>
using namespace std;
int main(void){
  time_t now = time(NULL);
  cout << now << endl
       << now - 1 << endl
       << (now >1) << endl;
}