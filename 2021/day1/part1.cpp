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
	for (int i = 1; i < readings.size(); i++) {
		if (readings[i - 1] < readings[i]) {
			cout << readings[i] << " " << readings[i - 1] << endl;
			count++;
		}
	}
	return count;
}


int main() {
	readData();
	cout << countIncreses() << endl;
}