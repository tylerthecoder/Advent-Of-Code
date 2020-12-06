#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool parseLine(int pos1, int pos2, char letter, string password) {
  int count = 0;

  if (password.length() >= pos1 && letter == password.at(pos1-1)) count++;
  if (password.length() >= pos2 && letter == password.at(pos2-1)) count++;

  return count == 1;
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
