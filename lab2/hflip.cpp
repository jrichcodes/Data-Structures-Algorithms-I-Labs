//File: hflip.cpp
//Name: Josephine Rich
//Date: September 7, 2021

/*Description: This lab takes in a PMG file from standard input and flips it horizontally. 
 * I allocated a matrix by making a vector of vectors. I then read in all of the pixels and 
 * print them out in reverse order of columns in the given row. 
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
	if (!(cin >> c  >> r) ||  r < 0) {
		cerr << "Bad PGM file -- No row specification\n";
		return 0;
		}
	if( c < 0) {
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
			if (!(cin >> n) || (n > 255) || (n < 0)) {
					cerr << "Bad PGM file -- pixel " << t <<  " is not a number between 0 and 255\n";
					cin.clear();
					return 0;
			}
			else {
				//adding to the counter t for the number of pixels read
				t++;

				//checking to make sure there are not too many pixels
				if ( t > (r*c)) {
					cerr << "Bad PGM file -- Extra stuff after the pixels\n";
					return 0;
				}

			}
			
			//storing the read in pixel in the correct spot in the matrix
			pmg[i][j] = n;
		}
	}
	
	//printing out the new pmg file that's horizontally flipped
	cout << "P2\n" << c << " " << r << "\n" << "255\n";

	for(i=0; i < pmg.size(); i++) {
		for(j=0; j < pmg[i].size(); j++) {
			
			//changing the column number by printing out the last pixel first and so on 
			cout << pmg[i][(c-1) - j] << " ";
		}

		//newline after each row is done printing
		cout << "\n";
	}

	return 0;
}		
