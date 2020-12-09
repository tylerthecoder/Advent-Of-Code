#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

struct OpData {
  int nextPc;
  int potentialNextPc;
  int acc;
  bool isBad;
};

vector<OpData> program;

void readLine(string line) {
  // format: op +12
  stringstream ss(line);

  int pc = program.size();

  char sign;
  int amount;
  string opName;

  ss >> opName >> sign >> amount;

  if (sign == '-') amount *= -1;


  OpData data;
  data.isBad = false;
  if (opName == "nop") {
    data.nextPc = pc+1;
    data.potentialNextPc = pc+amount;
    data.acc = 0;
  } else if (opName == "acc") {
    data.nextPc = pc+1; 
    data.potentialNextPc = -1; 
    data.acc = amount;
  } else if (opName == "jmp") {
    data.nextPc = pc+amount;
    data.potentialNextPc = pc+1;
    data.acc = 0;
  }

  program.push_back(data);
}


void readData() {
  fstream file;
  file.open("data.txt");
  if (!file.is_open()) return;

  string line = "";
  while(getline(file, line)) {
    readLine(line);
  }
}

int hasEnd(int pc, int acc, set<int> alreadySeen) {
  if (pc < 0) return 0;
  set<int> tempSeen = alreadySeen;
  do {
    OpData data = program[pc];
    tempSeen.insert(pc);
    acc += data.acc;
    pc = data.nextPc;
    if (pc == program.size()) return acc;
  } while (tempSeen.count(pc) == 0);
  return 0;
}

int runProgram() {
  int acc = 0;
  int pc = 0;
  set<int> ranLines;

  bool hasChanged = false;
  do {
    OpData op = program[pc];
    acc += op.acc;
    ranLines.insert(pc);

    int hasEndAcc = hasEnd(op.potentialNextPc, acc, ranLines);

    if (hasEndAcc) {
      return hasEndAcc;
    }
    pc = op.nextPc;
  } while (ranLines.count(pc) == 0);

  return acc;
}

int main() {
  readData();
  // changeOp();
  int res = runProgram();
  cout << res << endl;
}

