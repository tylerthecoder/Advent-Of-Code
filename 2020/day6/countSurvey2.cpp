#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

int countAnswers(vector<string> answers) {
  map<char, int> answerCount = {};

  set<char> answerSet = {};

  for (const char letter : answers[0]) {
    answerSet.insert(letter);
  }

  for (int i = 1; i < answers.size(); i++) {
    set<char> copied = answerSet;
    for (const char letter : answers[i]) {
      copied.erase(letter);
    }

    for (const char letter : copied) {
      answerSet.erase(letter);
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

