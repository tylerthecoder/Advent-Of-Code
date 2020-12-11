#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

vector<long> serial;
int target = 1309761972;

void readData() {
  fstream file;
  file.open("data.txt");
  if (!file.is_open()) return;

  long number;
  while(file >> number){
    serial.push_back(number); 
  }
}

long findAddends() {
  vector<long> addends;   

  long sum = 0;
  int pc = 0;
  while (sum != target) {
    long currentNum = serial[pc];
    addends.push_back(currentNum);
    sum += currentNum;
    while (sum > target && sum > 0) {
      sum -= addends[0];
      addends.erase(addends.begin());
    }
    pc++;
    if (pc > serial.size()) {
      return -1;
    }
  }

  sort(addends.begin(), addends.end());
  return addends.back() + addends.front();
}

int main() {
  readData();
  long res = findAddends();
  cout << res << endl;
}
