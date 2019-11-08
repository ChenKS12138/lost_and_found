#include<iostream>
#include<vector>
using namespace std;
int main(){
  vector<int> a = {1, 2, 3};
  a.erase(a.begin() + 1);
  for (int i = 0; i < a.size(); i++)
  {
    cout << a[i] << endl;
  }
}