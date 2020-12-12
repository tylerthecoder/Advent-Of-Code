#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct MoveData {
  char action;
  int amount;
};

vector<MoveData> moves;

void readData() {
  fstream file;
  file.open("data.txt", ios::in);
  if (!file) return;

  MoveData move;
  while (file >> move.action >> move.amount) {
    moves.push_back(move);  
  }
}

int moveShip() {
  int north = 0;
  int east = 0;
  int wpNorth = 1;
  int wpEast = 10;
  // 0: East, 1: South, 2: West, 3: North
  int facing = 0;
  for (const MoveData move: moves) {
    switch (move.action) {
      case 'N':
        wpNorth += move.amount;
        break;
      case 'S':
        wpNorth -= move.amount;
        break;
      case 'E':
        wpEast += move.amount;
        break;
      case 'W':
        wpEast -= move.amount; 
        break;
      case 'R': {
        for (int i = 0; i < move.amount/90; i++) {
          int tempNorth = wpNorth;
          int tempEast = wpEast;
          wpNorth = -tempEast;
          wpEast = tempNorth;
        }
        break;
      }
      case 'L':
        for (int i = 0; i < move.amount/90; i++) {
          int tempNorth = wpNorth;
          int tempEast = wpEast;
          wpNorth = tempEast;
          wpEast = -tempNorth;
        }
        break;
      case 'F':
        north += wpNorth * move.amount;
        east += wpEast * move.amount;
        break;
    }
  }

  return abs(north) + abs(east);
}

int main() {
  readData();    
  int res = moveShip();
  cout << "Result: " << res << endl;
}

