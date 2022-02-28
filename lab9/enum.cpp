//File name: enum.cpp
//Name: Josephine Rich
//Date: November 9, 2021

//Description: This program enumerate all strings of given length that contain fiven number and (length-num) zeros
//and print them on standard output in sorted order.

#include<iostream>
#include<sstream>
using namespace std;

void do_enumeration(string &s, int index, int n_ones) {
	
	/*base case*/
	if(((int)s.size() == index) && (n_ones == 0)) {
		cout << s << endl;
	}

	/*there are no more n_ones to be placed*/
	if((int)s.size() == index){
		return;
	}
	
	/*checking if a 1 or a zero is palced*/
	if((int)s.size() - index !=  n_ones) {
		s[index] = '0';
		do_enumeration(s, index +1, n_ones);
	}

	if(n_ones > 0) {
		s[index] = '1';
		do_enumeration(s, index +1, n_ones -1);	
	}

}

int main(int argc, char **argv) {
	int length, ones;
	istringstream ss;
	string s;

	/*error checking command line arguments*/
	if(argc != 3) {
		cerr << "usage: bin/argc-enum length ones\n";
		return 1;
	}

	/*changing the arguments from strings to ints*/
	ss.str(argv[1]);
	ss >> length;
	ss.clear();
	ss.str(argv[2]);
	ss >> ones;

	/*resizing s to be the length and fill with dashes*/
	s.resize(length, '-');

	/*calling enumeration*/
	do_enumeration(s, 0, ones);

	return 0;
}

