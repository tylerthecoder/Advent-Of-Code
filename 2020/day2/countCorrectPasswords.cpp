#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool parseLine(int min, int max, char letter, string password) {
  int count = 0;
  for (char const &c : password) {
    if (c == letter) {
      count++; 
    }
  }

  return count >= min && count <= max;
}

int readInNumbers() {
  fstream file;
  file.open("data.txt",ios::in); 
  
  int numCorrect = 0;
  // lines are of format "1-3 a: asdf"
  if (file.is_open()){
    int min, max;
    char letter, colon, dash;
    string password;
    while (file >> min >> dash >> max >> letter >> colon >> password) {
      cout << min << max << letter << password << endl;
      if (parseLine(min, max, letter, password)) {
        numCorrect++; 
      }
    }
    file.close();
  }
  return numCorrect;
}


int main() {
  int numCorrect = readInNumbers();

  cout << numCorrect << endl;

  return 0;
}
