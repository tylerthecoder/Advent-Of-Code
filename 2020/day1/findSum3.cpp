#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

vector<int> numbers = {};

void readInNumbers() {
  fstream newfile;
  newfile.open("data.txt",ios::in); //open a file to perform read operation using file object
  if (newfile.is_open()){   //checking whether the file is open
    string tp;
    while(getline(newfile, tp)){ //read data from file object and put it into string.
        cout << tp << "\n"; //print the data of the string
        int num = stoi(tp);
        numbers.push_back(num);
    }
    newfile.close(); //close the file object.
  }
}

int find3Addends() {
  for (int i : numbers) {
    for (int j : numbers) {
      for (int k : numbers) {
        if (i+j+k == 2020) {
          cout << "Found Numbers" << endl;
          cout << i * j * k << endl;
        }
      }
    }
  }

  return 0;
}

int main() {
  readInNumbers();
  find3Addends();
  return 0;
}
