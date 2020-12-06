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
        map.push_back(tp);
    }
    newfile.close();
  }
}

int countTrees(int dx, int dy) {
  int x = 0;
  int count = 0;
  for (int y = 0; y < map.size(); y+=dy) {
    if (map[y][x] == '#') count ++;
    x += dx;
    x %= map[0].length();
  }
  return count;
}

int main() {
  readMap(); 
  int product = countTrees(1,1) * countTrees(3, 1) * countTrees(5,1) * countTrees(7,1) * countTrees(1,2);
  cout << "Product: " << product << endl;

  return 0;
}
