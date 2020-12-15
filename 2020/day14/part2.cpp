#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

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


vector<long> floatBits(long num, vector<long> bitsToFloat) {
  vector<long> res; 

  if (bitsToFloat.size() == 0) return res;

  long indexToFloat = bitsToFloat.back();
  bitsToFloat.pop_back();
  long num0 = num &= ~(1UL << indexToFloat);
  long num1 = num |= 1UL << indexToFloat;

  res.push_back(num0);
  res.push_back(num1);
   
  vector<long> otherRes0 = floatBits(num0, bitsToFloat);
  vector<long> otherRes1 = floatBits(num1, bitsToFloat);

  res.insert(res.end(), otherRes0.begin(), otherRes0.end());
  res.insert(res.end(), otherRes1.begin(), otherRes1.end());

  return res;
}

vector<long> applyMask(string mask, long num) {
  int index = 0;
  int maskSize = mask.size();

  vector<long> floatingBitIndices;

  while (index < maskSize) {
    int numIndex = maskSize - (index+1);
    unsigned long bit = (num >> numIndex) & 1U;
    const char maskBit = mask[index];

    if (maskBit == 'X') {
      // "float" the bit
      floatingBitIndices.push_back(numIndex);
    } else if (maskBit == '1') {
      // write a one
      num |= 1UL << numIndex;
    } else if (maskBit == '0') {
      // don't change the bit
    }
    index++;
  }

  // loop through the floats and create all of the memory addresses
  vector<long> memoryAddresses = floatBits(num, floatingBitIndices);

  return memoryAddresses;
}

long runProgram() {
  map<long, long> memory; 

  for (const ProgData inst : program) {
    vector<long> addresses = applyMask(inst.mask, inst.address); 
    for (const long address : addresses) {
      memory[address] = inst.value;
    }
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

