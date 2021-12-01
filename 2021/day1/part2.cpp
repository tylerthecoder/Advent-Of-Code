#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> readings = {};

void readData() {
  fstream file;
  file.open("input.txt", ios::in);
  if (!file.is_open()) return;

  int num;
  while (file >> num) {
    readings.push_back(num);
  }
}

int countIncreses() {
	int count = 0;
	for (int i = 3; i < readings.size(); i++) {
		int sum1 = readings[i - 3] + readings[i - 2] + readings[i - 1];
		int sum2 = readings[i - 2] + readings[i - 1] + readings[i];
		if (sum1 < sum2) {
			count++;
		}
	}
	return count;
}


int main() {
	readData();
	cout << countIncreses() << endl;
}