//File: vflip.cpp
//Name: Josephine Rich
//Date: September 7, 2021

/*Description: This program takes in a pmg file from standard input and flips it vertically. 
 * I allocate a matrix and by making a vector of vectors based on the number of columns and rows.
 * I then read in the pixels and lead them into the matrix. I then print out the matrix on standard
 * output and mainipulate the rows index so that it vertically flips the pmg.  
 */

#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

int main () {

	string word;
	int r, c, p, n, t = 0;
	size_t i;
	size_t j;
	vector<vector <int> > pmg;

	//checking for P2 as first word in file
	cin >> word;
	if (word == "P2") {
	}
	else {
		cerr << "Bad PGM file -- first word is not P2\n";
		return 0;
	}
		
	//reading in the columns and rows
	if (!(cin >> c  >> r) ||  r <= 0) {
		cerr << "Bad PGM file -- No row specification\n";
		return 0;
		}
	if( c <= 0) {
		cerr << "Bad PGM file -- No column specification\n";
		return 0;
	}

	//checking for 255 as the next word
	cin >> p;
	if (p == 255) {
	}
	else {
		cerr << "Bad PGM file -- No 255 following the rows and columns\n";
		return 0;
	}

	//allocating the matrix for the PMG
	pmg.resize(r);
	for (i=0; i < pmg.size(); i++) {
		pmg[i].resize(c);
	}

	for (i=0; i < pmg.size(); i++) {
		for (j=0; j < pmg[i].size(); j++) {

			//reading in the rest of the pixels
			cin >> n;
			t++;

			//checking to make sure there are not too many pixels
			if ( t > (r*c)) {
				cerr << "Bad PGM file -- Extra stuff after the pixels\n";
				return 0;
			}

			// checking to make sure each pixel value is between 0 and 255
			if (n > 255 || n < 0) {
				cerr << "Bad PGM file -- pixel " << t- 1 << " is not a number between 0 and 255\n";
				return 0;
			}	

			pmg[i][j] = n;
		}
	}
	
	//printing out pmg to standard output
	cout << "P2\n" << c << " " << r << "\n" << "255\n";

	for(i=0; i < pmg.size(); i++) {
		for(j=0; j < pmg[i].size(); j++) {
			
			//subtracting one from the number of rows and then subtracting the current row number to flip the pmg vertically
			cout << pmg[(r-1)-i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}		
