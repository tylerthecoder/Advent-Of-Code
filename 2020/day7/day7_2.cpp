#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct BagData {
  string bagName; 
  int amount;
};

map<string, vector<BagData>> bagsData;

void readLine(string line) {
  stringstream ss(line);

  string adj, color, bags, contains;
  ss >> adj >> color >> bags >> contains;

  string bagName = adj + " " + color; 

  int count;
  do {
    if (ss >> count >> adj >> color >> bags) {
      BagData bagData;
      bagData.amount = count;
      bagData.bagName = adj + " " + color;
      bagsData[bagName].push_back(bagData);
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

int countBags(string bagName) {
  int count = 0;
  for (const BagData otherBag : bagsData[bagName]) {
    count += otherBag.amount * countBags(otherBag.bagName);
  }
  return 1 + count;
}

int main() {
  readData();
  int numOfGoodBags = countBags("shiny gold")-1;
  cout << numOfGoodBags << endl;
}

