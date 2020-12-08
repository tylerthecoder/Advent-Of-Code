#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int countAnswers(vector<string> answers) {
  set<char> answerSet = {};
  for (const string answer : answers) {
    for (const char letter : answer) {
      answerSet.insert(letter);
    }
  }
  return answerSet.size();
}

int readData() {
  fstream file;
  file.open("data.txt",ios::in);
  if (!file.is_open()) return 0;

  string line = "";

  vector<string> answers;

  int count = 0;
  while(getline(file, line)){
    if (line.length() > 0) {
      answers.push_back(line); 
    } else {
      count += countAnswers(answers);
      answers.clear();
    }
  }
  count += countAnswers(answers);
  file.close();

  return count;
}

int main() {
  int num = readData();
  cout << num << endl;


  return 0;
}

