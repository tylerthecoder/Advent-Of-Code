#include <fstream>
#include <iostream>
#include <vector>

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
  // 0: East, 1: South, 2: West, 3: North
  int facing = 0;
  for (const MoveData move: moves) {
    switch (move.action) {
      case 'N':
        north += move.amount;
        break;
      case 'S':
        north -= move.amount;
        break;
      case 'E':
        east += move.amount;
        break;
      case 'W':
        east -= move.amount; 
        break;
      case 'R':
        facing = (facing + move.amount / 90) % 4;
        break;
      case 'L':
        facing = ((facing+4) - move.amount / 90) % 4;
        break;
      case 'F':
        if (facing == 0) east += move.amount;
        if (facing == 1) north -= move.amount;
        if (facing == 2) east -= move.amount;
        if (facing == 3) north += move.amount;
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

