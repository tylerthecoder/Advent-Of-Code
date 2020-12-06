#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> seatCoords = {};
vector<int> seatIds = {};

void readData() {
  fstream file;
  file.open("data.txt",ios::in);
  if (!file.is_open()) return;

  string line = "";

  while(getline(file, line)){
    seatCoords.push_back(line);
  }
  file.close();
}


int findSeat(string seatCoord) {
  int maxy = 127;
  int miny = 0;
  int maxx = 7;
  int minx = 0;
  for (const char dir : seatCoord) {
    if (dir == 'F') {
      maxy = ((maxy - miny) / 2) + miny;
    } else if (dir == 'B') {
      miny = ((maxy - miny) / 2) + miny;
    } else if (dir == 'L') {
      maxx = ((maxx - minx) / 2) + minx;
    } else if (dir == 'R') {
      minx = ((maxx - minx) / 2) + minx;
    }
  }
  
  return maxy * 8 + maxx;
}

void findAllSeats() {
  for (string seatCoord : seatCoords) {
    int seatId = findSeat(seatCoord);
    seatIds.push_back(seatId);
  }
}

int findMySeat() {
  sort(seatIds.begin(), seatIds.end());
  for (int i = 1; i < seatIds.size(); i++) {
    if (seatIds[i] > seatIds[i-1] +1) {
      return seatIds[i] - 1;
    }
  }
  return 0;
}

int main() {
  readData();
  findAllSeats();
  int mySeatId = findMySeat();
  cout << mySeatId << endl;

  return 0;
}

