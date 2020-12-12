#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> seats;


void readData() {
  fstream file;
  file.open("data.txt", ios::in);
  if (!file) return;

  string line;
  while(getline(file, line)) {
    seats.push_back(line); 
  }
}

int getAdjacentCount(int x, int y) {
  int count = 0;
  for (int i = x-1; i <= x+1; i++) {
    for (int j = y-1; j <= y+1; j++) {
      if (i == x && j == y) continue;
      if (i < 0 || j < 0 || i >= seats.size() || j >= seats[i].length()) continue;
      if (seats[i][j] == '#') count++;
    }
  }
  return count;
}

int doSeats() {
  vector<string> seatsCopy = seats;
  int numChanged = 0;
  for (int i = 0; i < seats.size(); i++) {
    string row = seats[i];
    for (int j = 0; j < row.length(); j++) {
      char seat = row[j]; 
      if (
          seat == 'L' &&
          getAdjacentCount(i, j) == 0
      ) {
        numChanged++;
        seatsCopy[i][j] = '#';
      }

      if (
          seat == '#' &&
          getAdjacentCount(i, j) >= 4
      ) {
        numChanged++;
        seatsCopy[i][j] = 'L';
      }
    }
  }

  seats = seatsCopy;

  return numChanged;
}

int doAllSeats() {
  int numChanged = 0;
  do {
    numChanged = doSeats();
  } while(numChanged > 0);

  int numOfTakenSeats = 0;
  for (const string row : seats) {
    for (const char seat : row) {
      if (seat == '#') numOfTakenSeats++;
    }
  }
  return numOfTakenSeats;

}

int main() {
  readData();
  int res = doAllSeats();
  cout << "Result: " << res << endl;
}

