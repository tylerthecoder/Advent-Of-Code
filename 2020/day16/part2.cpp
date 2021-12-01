#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

struct Location {
  string name;
  pair<int, int> start;
  pair<int, int> end;
  int index;
};

vector<Location> locations;
vector<int> myTicket;
vector<vector<int>> nearbyTickets;

void readData() {
  fstream file;
  file.open("data.txt", ios::in);

  string line;
  do {
    getline(file, line);
    stringstream ss(line);

    char letter;
    string fieldName;
    while (ss >> letter) {
      fieldName += letter;
      if (letter != ':') continue;

      Location locData;
      locData.name = fieldName;

      int start, end;
      char hyphen;
      ss >> start >> hyphen >> end;
      locData.start = make_pair(start, end);

      string orString;
      ss >> orString;

      ss >> start >> hyphen >> end;
      locData.end = make_pair(start, end);
      locations.push_back(locData);

      break;
    }
  } while(line.length() != 0);

  // your ticket label
  getline(file, line);
  // your ticket
  getline(file, line);
  stringstream ss(line);
  char comma;
  int num;
  do {
    ss >> num;
    myTicket.push_back(num); 
  } while (ss >> comma);


  // nl
  getline(file, line);
  // nearby tickets label
  getline(file, line);


  while (getline(file, line)) {
    stringstream ss(line);
    int num;
    char comma;
    vector<int> ticket;
    do {
      ss >> num;
      ticket.push_back(num);
    } while (ss >> comma);

    if (ticket.size() > 0) nearbyTickets.push_back(ticket);
  }
}

bool isBadForLocation(int num, Location loc) {
  return !( num > loc.start.first && num < loc.start.second ||
            num > loc.end.first && num < loc.end.second);
}

bool isBad(int ticketPart) {
  return all_of( locations.begin(), locations.end(), [ticketPart](Location loc) {
      return isBadForLocation(ticketPart, loc);
  });
}

void takeOutBad() {
  remove_if(nearbyTickets.begin(), nearbyTickets.end(), [](auto ticket) {
      return any_of(ticket.begin(), ticket.end(), isBad);
  });
}

long getErrorRate() { 
  int i = 0;
  set<int> solvedIndices;
  cout << "hello World" << endl;
  for (Location loc : locations) {
    cout << loc.name << endl;
    for (int j = 0; j < myTicket.size(); j++) {
      cout << j << endl;
      if (solvedIndices.count(j)) continue;
      
      bool allGood = all_of(nearbyTickets.begin(), nearbyTickets.end(), [j, loc](vector<int> ticket) {
        if (ticket.size() == 0) return true;
        return !isBadForLocation(ticket[j], loc); 
      });

      if (!allGood) continue;

      cout << "Good" << endl;

      solvedIndices.insert(j);
      loc.index = j;
    }
  }

  cout << "------------------" << endl;

  long ans = 0;
  for (Location loc : locations) {
    cout << loc.name << loc.index << endl;
    if (loc.name.find("departure") != string::npos) {
      cout << loc.index << endl;
      ans *= myTicket[loc.index]; 
    }
  }
  return ans;

}

int main() {
  readData();
  takeOutBad();
  long res = getErrorRate();
  cout << "Result: " << res << endl;
}

