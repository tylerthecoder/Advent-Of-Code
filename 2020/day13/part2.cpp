#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>

using namespace std;

struct Bus {
  int id;
  int offset;
};

vector<Bus> buses;

void readData() {
  fstream file;
  file.open("data.txt", ios::in);
  if (!file.is_open()) return;

  int startTime;
  file >> startTime;

  string data;
  int line = -1;
  while (getline(file, data, ',')) {
    line++;
    if (data == "x") continue;
    Bus bus;
    bus.id = stoi(data);
    bus.offset = line;
    buses.push_back(bus);
  }
}

long findMinTime() {
  Bus bus = buses[0];
  long inc = bus.id;
  int busIndex = 1;
  long time = 0;

  while (busIndex < buses.size()) {
    Bus bus = buses[busIndex];
    if (time % bus.id == bus.id - (bus.offset % bus.id)) {
      inc *= bus.id;
      busIndex++;
      if (busIndex >= buses.size()) {
        return time;
      }
    }
    time += inc;
  }

  return -1;
}

int main() {
  readData();
  long res = findMinTime();
  cout << "Result: " << res << endl;
}


