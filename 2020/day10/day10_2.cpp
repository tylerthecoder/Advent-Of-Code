#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> jolts = {0};

void readData() {
  fstream file;
  file.open("data.txt", ios::in);
  if (!file.is_open()) return;

  int num;
  while (file >> num) {
    jolts.push_back(num);
  }
}

long countJolts() {
  sort(jolts.begin(), jolts.end()); 

  // Add my devices
  jolts.push_back(jolts.back() + 3);

  vector<long> comboCount(jolts.size());
  
  comboCount[jolts.size() - 1] = 1;

  for (int i = jolts.size()-2; i >= 0; i--) {
    long comboNumber = 0;      
    int reach = i+1;
    while (reach < jolts.size() && jolts[reach] - jolts[i] <= 3) {
      comboNumber += comboCount[reach]; 
      reach++;
    }
    comboCount[i] = comboNumber;
  }

  return comboCount[0];
}

int main() {
  readData();
  long res = countJolts();
  cout << "Result: " << res << endl;
}

