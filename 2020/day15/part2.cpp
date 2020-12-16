#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> nums;

void readData() {
  fstream file;
  file.open("data.txt", ios::in);

  int num;
  char comma;
  while (file >> num) {
    nums.push_back(num); 
    file >> comma;
  }
}

int playGame() {
  map<int, int> lastSaid;
  int lastNum = 0;

  for (int i = 0; i < 30000000; i++) {
    int nextNum;
    if (i < nums.size()) {
      nextNum = nums[i]; 
    } else if (lastSaid.count(lastNum) == 0) {
      nextNum = 0; 
    } else {
      nextNum = i - (lastSaid[lastNum]+1);
    }

    if (i > 0) {
      lastSaid[lastNum] = i -1;
    }
    lastNum = nextNum;
  }

  return lastNum;
}


int main() {
  readData();
  int res = playGame();
  cout << "Result: " << res << endl;
}
