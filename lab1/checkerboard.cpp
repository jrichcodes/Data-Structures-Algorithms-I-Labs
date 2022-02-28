//File: checkerboard.cpp
//Name: Josephine Rich
//Date: 8/25/2021

/* Description: This program prints out a checkerboard pattern based on the given input. The user must enter 
 * a number of rows, number of columns, a starting character, and a cycle size for the program to execute.
 */


#include<iostream>
using namespace std;

int main () {

	int r, c, cs, w;
	int i, iw, j, jw;
	char sc;

	//checking to see if there are enough aruments given otherwise an error message is printed
	if(! (cin >> r >> c >> sc >> cs >> w)) {
		cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W\n";
	}
	
	//checking to make sure that the numbers given are greater than zero
	if (r <= 0 || c <= 0 || cs <= 0 || w <= 0) { 
			return 0;
		}	

	//checking to make sure starting character + cycle size is less than 127
	if (sc + cs >= 127) {
		return 0;
	}

	//prints out checkerboard i keeps track of the rows and j keeps track of the columns
	for (i = 0; i < r; i++) {
		for (iw = 0; iw < w; iw++) {
			for (j=0; j < c; j++) { 
				for (jw=0; jw < w; jw++) {

					//this equation prints out the character based on the current row, column, and cycle size
					cout << char(sc + (i+j)%cs);
				}	
			}	

		//prints out a newline after each row prints
		cout << "\n";
		}
	
	}	
	return 0;
 }
