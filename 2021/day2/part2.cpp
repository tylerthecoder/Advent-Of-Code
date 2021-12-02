#include <iostream>

using namespace std;

int main() {
	string dir;
	int x = 0, y = 0, aim = 0, u = 0;
	while(!cin.eof()) {
		cin >> dir >> u;
		if (dir == "forward") {
			x += u;
			y += aim * u;
		} else if (dir == "up") {
			aim -= u;
		} else if (dir == "down") {
			aim += u;
		}
	}
	cout << x * y << endl;
}