#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<pair<int, int>> intervals;
vector<int> nearbyTickets;

void readData() {
  fstream file;
  file.open("data.txt", ios::in);

  string line;
  do {
    getline(file, line);
    stringstream ss(line);

    char letter;
    while (ss >> letter) {
      if (letter != ':') continue;

      int start, end;
      char hyphen;
      ss >> start >> hyphen >> end;
      intervals.push_back(make_pair(start, end));

      string orString;
      ss >> orString;

      ss >> start >> hyphen >> end;
      intervals.push_back(make_pair(start, end));

      break;
    }

  } while(line.length() != 0);

  // your ticket label
  getline(file, line);
  // your ticket
  getline(file, line);
  // nl
  getline(file, line);
  // nearby tickets label
  getline(file, line);


  while (getline(file, line)) {
    stringstream ss(line);
    int num;
    char comma;
    do {
      ss >> num;
      nearbyTickets.push_back(num);
    } while (ss >> comma);
  }
}

long getErrorRate() { 
  long errorRate = 0;
  for (const int ticket : nearbyTickets) {
    bool found = false;
    cout << ticket << endl;
    for (const pair<int, int> interval : intervals) {
      if (ticket > interval.first && ticket < interval.second) {
        found = true;
        break;
      }  
    }
    if (!found) {
      cout << ticket;
      errorRate += ticket; 
    }
  }

  return errorRate;
}

int main() {
  readData();
  long res = getErrorRate();
  cout << "Result: " << res << endl;
}

