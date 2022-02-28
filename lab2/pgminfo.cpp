//File: pgminfo.cpp
//Name: Josephine Rich
//Date: September 7, 2021

/*Description: This program takes in a PGM file on standard input and reports the number of rows, the number of
 * columns, and the total number of pixels, and the average value of all the pixels. This program error checks the 
 * input to make sure it's a proper PGM file. 
 */

#include<iostream>
#include<cstdio>
using namespace std;

int main () {

	string word;
	int r, c, p, n, i = 0;
	double totalpix, avgpix;

	//checking for P2 as first word in file
	cin >> word;
	if (word == "P2") {
	}
	else {
		cerr << "Bad PGM file -- first word is not P2\n";
		return 0;
	}
		
	//reading in the columns and rows
	if (!(cin >> c  >> r) || c < 0 || r < 0) {
		cerr << "Bad PGM file -- No row specification\n";
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

	//reading in the rest of the pixels
	while (cin >> n) {
		i++;

		//calculating the value of all the pixels
		totalpix += n;

		//checking to make sure there are not too many pixels
		if ( i > (r*c)) {
			cerr << "Bad PGM file -- Extra stuff after the pixels\n";
			return 0;
		}

		// checking to make sure each pixel value is between 0 and 255
		if (n > 255 || n < 0) {
			cerr << "Bad PGM file -- pixel " << i- 1 << " is not a number between 0 and 255\n";
			return 0;
		}
	}

	//calculating the average pixel value
	avgpix = totalpix/i;

	//printing out the info
	printf("# Rows: %11i\n", r);
	printf("# Columns: %8i\n", c);
	printf("# Pixels: %9i\n", i);
	printf("Avg Pixel: %8.3lf\n", avgpix);

	return 0;
}	


			
