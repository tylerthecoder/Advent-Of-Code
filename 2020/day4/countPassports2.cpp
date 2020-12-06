#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <ctype.h>
#include <regex>

using namespace std;

vector<string> passports = {};

void readData() {
  fstream file;
  file.open("data.txt",ios::in);
  if (!file.is_open()) return;

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

bool validateTag(string tag, string value) {
  if (tag == "byr") {
    int year = stoi(value);
    return year >= 1920 && year <= 2002;
    return regex_match(value, regex());
  } else if (tag == "iyr") {
    int year = stoi(value);
    return year >= 2010 && year <= 2020;
  } else if (tag == "eyr") {
    int year = stoi(value);
    return year >= 2020 && year <= 2030;
  } else if (tag == "hgt") {
    stringstream valueStream(value);
    int amount;
    string unit;
    if (valueStream >> amount && valueStream >> unit) {
      if (unit == "cm") {
        return amount >= 150 && amount <= 193;
      } else if (unit == "in") {
        return amount >= 59 && amount <= 76; 
      } else {
        return false;
      }
    }
    return false;
  } else if (tag == "hcl") {
    return regex_match(value, regex("#[0-9a-f]{6}"));
  } else if (tag == "ecl") {
    return regex_match(value, regex("(amb|blu|brn|gry|grn|hzl|oth)"));
  } else if (tag == "pid") {
    return regex_match(value, regex("[0-9]{9}"));
  } else if (tag == "cid") {
    return true;
  }
  return false;
}

bool validatePassport(string passportStr) {
  set<string> tagSet;

  stringstream ss(passportStr);

  string tagData;
  while (ss >> tagData) {
    string tag; 
    string value;
    bool foundSemi = false;
    for (const char letter : tagData) {
      if (letter == ':') foundSemi = true;
      else if (!foundSemi && letter != ' ') tag += letter;
      else if (letter != ' ') value += letter;
    }
    tagSet.insert(tag);

    if (!validateTag(tag, value)) return false;
  }

  return tagSet.count("iyr") && tagSet.count("eyr") && tagSet.count("hgt") && tagSet.count("hcl") && tagSet.count("ecl") && tagSet.count("byr") && tagSet.count("pid");
}

int countValidPassports() {
  int count = 0;
  for (const string passportStr : passports) {
    if (validatePassport(passportStr)) count++;
  }

  return count;
}

int main() {
  readData();

  int numOfCorrect = countValidPassports();

  cout << numOfCorrect << endl;

  return 0;
}

