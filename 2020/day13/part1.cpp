#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>

using namespace std;

int startTime;
vector<int> busIds;

void readData() {
  fstream file;
  file.open("data.txt", ios::in);
  if (!file.is_open()) return;

  file >> startTime;

  string data;
  while (getline(file, data, ',')) {
    if (data == "x") continue;
    int busId = stoi(data);
    busIds.push_back(busId);
  }
}

int waitTime(int busId) {
  return busId - (startTime % busId);
}

int findClosest() {
  int clostedBusId = min_element(busIds.begin(), busIds.end(),
    [](int a, int b) {
      return waitTime(a) < waitTime(b);
    }
  )[0];
  return clostedBusId * waitTime(clostedBusId);
}

int main() {
  readData();
  int res = findClosest();
  cout << "Result: " << res << endl;
}


