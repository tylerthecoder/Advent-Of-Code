#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector<long> serial;

void readData() {
  fstream file;
  file.open("data.txt");
  if (!file.is_open()) return;

  long number;
  while(file >> number){
    serial.push_back(number); 
    cout << number << endl;
  }
}

bool hasSum(set<int> data, int num) {
  set<int> inverses; 
  for (const int n : data) {
    if (inverses.count(n)) return true; 
    inverses.insert(abs(n - num));
  }
  return false;
}

int findNonSum() {  
  set<int> pastNums;
  int pc = 0;
  for (; pc < 25; pc++) {
    pastNums.insert(serial[pc]);
  }
  
  while (hasSum(pastNums, serial[pc])) {
    pastNums.erase(serial[pc-25]); 
    pastNums.insert(serial[pc]);
    pc++;
  }
  
  cout << pc << endl;

  return serial[pc];
}

int main() {
  readData();
  int res = findNonSum();
  cout << res << endl;
}


