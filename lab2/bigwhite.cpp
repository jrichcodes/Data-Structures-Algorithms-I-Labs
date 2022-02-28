//File: bigwhite.cpp
//Name: Josephine Rich
//Date: September 7, 2021

/*Description: This program takes in two ints from the command line to form a PMG file on the standard output with all white pixels. I used a for-loop to print out the correct number of rows and columns.
 */

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int main (int argc, char *argv[]) {

	int r, c, i, j;

	//making sure that enough arguments were passed
	if(argc != 3) {
		cerr << "usage: bigwhite rows cols\n";
		return 0;
	}

	//changing the chars into ints
	r = atoi(argv[1]);
	c = atoi(argv[2]);

	//checking to make sure that rows and columns aren't negative numbers
	if(r <= 0 || c <= 0){ 
		cerr << "usage: bigwhite rows cols\n";
		return 0;
	}

	//printing out the start of the file
	cout << "P2 \n" << c  << " " << r << "\n" << "255\n";

	//using a for loop to print out white pixels
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			
			// 255 is the pixel value for white
			cout << "255 ";
		}
		cout << "\n";
	}

	return 0;
}
