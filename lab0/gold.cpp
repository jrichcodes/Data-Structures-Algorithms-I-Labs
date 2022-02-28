#include<iostream>
using namespace std;

int main () {
	
	char c;
	int t = 0;

	while (cin >> c) {
		if (c == '.' ||  c == '-') {

		}
		else {
			int g;
			g = c - 64;
			t = t + g;

		}
	}

	cout << t << "\n";

	return 0;
}
