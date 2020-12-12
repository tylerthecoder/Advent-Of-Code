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
  // loop thru the direction
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      int cx = x+i;
      int cy = y+j;
      while (true) {
        if (cx < 0 || cy < 0 || cx >= seats.size() || cy >= seats[0].length()) break;
        char seat = seats[cx][cy];
        if (seat == '#') { 
          count++;
          break;
        }
        if (seat == 'L') break;
        cx += i;
        cy += j;
      }
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
          getAdjacentCount(i, j) >= 5
      ) {
        numChanged++;
        seatsCopy[i][j] = 'L';
      }
    }
  }

  seats = seatsCopy;
  for (const string row : seats) {
    cout << row << endl;
  }
  cout << endl;

  return numChanged;
}

int doAllSeats() {
  int numChanged = 0;
  do {
    numChanged = doSeats();
  } while(numChanged > 0);


  int numOfTakenSeats = 0;
  for (const string row : seats) {
    cout << row << endl;
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

