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

int countJolts() {
  sort(jolts.begin(), jolts.end()); 

  // Add my devices
  jolts.push_back(jolts.back() + 3);

  int numOf3Diff = 0;
  int numOf1Diff = 0;
  for (int i = 1; i < jolts.size(); i++) {
    cout << jolts[i] << endl;
    int diff = jolts[i] - jolts[i-1];
    if (diff == 1) numOf1Diff++;
    if (diff == 3) numOf3Diff++;
  }

  return numOf1Diff * numOf3Diff;
}

int main() {
  readData();
  int res = countJolts();
  cout << res << endl;
}
