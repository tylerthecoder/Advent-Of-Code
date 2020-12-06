#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> map = {};

void readMap() {
  fstream newfile;
  newfile.open("data.txt",ios::in);
  if (newfile.is_open()){
    string tp;
    while(getline(newfile, tp)){
        cout << tp << "\n";
        map.push_back(tp);
    }
    newfile.close(); //close the file object.
  }
}

int countTrees() {
  int x, y, count = 0;
  for (const string line : map) {
    if (line[x] == '#') count++;
    x += 3;
    x %= line.length();
  }
  return count;
}

int main() {
  readMap(); 
  int numOfTrees = countTrees();
  cout << "Num of Trees: " << numOfTrees << endl;

  return 0;
}
