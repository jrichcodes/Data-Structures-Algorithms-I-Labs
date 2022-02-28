//File: neg.cpp
///Name: Josephine Rich
//Date: September 7, 2021

/*Description: This program uses a for-loop to go through all the pixels and inverting them by doing 255 - the original pixel value.
 * prints each pixels on a newline.
 */

#include<iostream>
#include<cstdio>
using namespace std;

int main () {

	string word;
	int r, c, p, n, i = 0, k , j;

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
	
	//printing out the first parts of a PGM file
	cout << "P2\n" << c << " " << r << "\n" << "255\n";

	//looping through the numbers of rows and columns and reading in each pixels and then printing out the negative
	for(k=0; k < r; k++) {
		for( j=0; j < c; j++) {
			
			//reading in the rest of the pixels
			while (cin >> n) {
			i++;

			//checking to make sure there are not too many pixels
			if ( i > (r*c)) {
				cerr << "Bad PGM file -- Extra stuff after the pixels\n";
				return 0;
			}

			// checking to make sure each pixel value is between 0 and 255
			if (n > 255 || n < 0) {
				cerr << "Bad PGM file -- pixel " << i- 1 << " is not a number between 0 and 255\n";
			}

			//subtracting from 255 to get the negative of the pixel
			cout << 255 -n << "\n";
				}
		}
	}

	return 0;
}	


			
