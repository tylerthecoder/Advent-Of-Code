#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct ProgData {
  string mask;
  long address;
  long value;
};

vector<ProgData> program;

void readData() {
  fstream file;
  file.open("data.txt", ios::in);
  if (!file.is_open()) return;

  string op;
  string mask;
  while (file >> op) {
    if (op == "mask") {
      char eq;
      file >> eq >> mask;
    } else {
      char eq;
      ProgData inst;
      inst.mask = mask;
      inst.address = atoi(op.substr(4, op.length() - 2).c_str());
      file >> eq >> inst.value;
      program.push_back(inst);
    }
  }
}

long applyMask(string mask, long num) {
  int index = 0;
  int maskSize = mask.size();

  while (index < maskSize) {
    int numIndex = maskSize - (index+1);
    unsigned long bit = (num >> numIndex) & 1U;
    const char maskBit = mask[index];

    if (maskBit == 'x') {
      num ^= (-0 ^ num) & (1UL << numIndex);
    } else if (maskBit == '1') {
      num |= 1UL << numIndex;
    } else if (maskBit == '0') {
      num &= ~(1UL << numIndex);
    }
    index++;
  }

  return num;
}

long runProgram() {
  map<long, long> memory; 

  for (const ProgData inst : program) {
    long val = applyMask(inst.mask, inst.value); 
    cout << val << endl;
    memory[inst.address] = val;
  }

  long sum = 0;
  for (const pair<long, long>  value : memory) {
    sum += value.second;
  }
  return sum;
}

int main() {
  readData();
  long res = runProgram();
  cout << "Result: " << res << endl;
}

