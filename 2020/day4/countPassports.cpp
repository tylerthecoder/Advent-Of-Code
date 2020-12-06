#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<string> passports = {};

void readData() {
  fstream file;
  file.open("data.txt",ios::in);
  if (!file.is_open()) return;

  char letter;
  string passport = "";
  string line = "";

  while(getline(file, line)){
      passport += line + " ";
      if (line.length() == 0) {
        passports.push_back(passport);
        passport = "";
      }
  }
  passports.push_back(passport);
  file.close();
}

int countValidPassports() {
  int count = 0;
  for (const string passportStr : passports) {
    set<string> tagSet;
    string tag;
    bool foundColon = false;
    for (const char letter : passportStr) {
      if (!foundColon && letter != ':') tag += letter;
      if (!foundColon && letter == ':') {
        foundColon = true;
        tagSet.insert(tag);
        tag = "";
      }
      if (letter == ' ') foundColon = false;
    }

    if (tagSet.count("iyr") && tagSet.count("eyr") && tagSet.count("hgt") && tagSet.count("hcl") && tagSet.count("ecl") && tagSet.count("byr") && tagSet.count("pid")) count++;
  }

  return count;
}

int main() {
  readData();

  int numOfCorrect = countValidPassports();

  cout << numOfCorrect << endl;

  return 0;
}

