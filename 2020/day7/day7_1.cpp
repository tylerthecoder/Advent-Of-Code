#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;


map<string, vector<string>> bagsData;


void readLine(string line) {
  stringstream ss(line);

  string adj, color, bags, contains;
  ss >> adj >> color >> bags >> contains;

  string bagName = adj + " " + color; 

  // cout << bagName << endl;

  int count;

  do {
    if (ss >> count >> adj >> color >> bags) {
      bagsData[bagName].push_back(adj + " " + color);
      //cout << "Adding: " << adj + " " + color << endl;
    } else {
      // this normally means there was "no bags"
      return;
    }
  } while (bags.back() == ',');

}

void readData() {
  fstream file;
  file.open("data.txt", ios::in);
  if (!file.is_open()) return;

  string line = "";
  while(getline(file, line)) {
    readLine(line);
  }
}


set<string> goodBags;
set<string> badBags;

bool isGoodBag(string bagName) {
  if (goodBags.count(bagName)) return true;
  for (const string otherBagName : bagsData[bagName]) {
    if (isGoodBag(otherBagName)) {
      goodBags.insert(bagName);
      return true;
    }
  }

  return false;
}

int countBags() {
  goodBags.insert("shiny gold");

  int count = 0;

  map<string, vector<string>>::iterator it;
  for (it = bagsData.begin(); it != bagsData.end(); it++) {
    string bagName = it->first;
    cout << "Checking: " << bagName << endl;
    if (bagName == "shiny gold") continue;
    if (isGoodBag(bagName)) {
      cout << "Isa good bag" << endl;
      count++;
    }
  }

  return count;
}

int main() {
  readData();
  int numOfGoodBags = countBags();
  cout << numOfGoodBags << endl;

  return 0;
}
