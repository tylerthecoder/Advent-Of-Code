#include <iostream>

using namespace std;

int main() {
	int x = 0, y = 0;
	while(!cin.eof()) {
		int units;
		string dir;
		cin >> dir >> units;
		if (dir == "forward") {
			x += units;
		} else if (dir == "up") {
			y -= units;
		} else if (dir == "down") {
			y += units;
		}
	}
	cout << x * y << endl;
}