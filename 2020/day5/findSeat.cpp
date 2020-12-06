#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> seatCoords = {};

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

int findAllSeats() {
  int max = 0;
  for (string seatCoord : seatCoords) {
    int seatId = findSeat(seatCoord);
    if (seatId > max) max = seatId;
  }
  return max;
}


int main() {
  readData();
  int maxSeatId = findAllSeats();
  cout << maxSeatId << endl;

  return 0;
}

