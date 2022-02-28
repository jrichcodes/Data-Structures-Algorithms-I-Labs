//File: pgm.cpp
//Name: Josephine Rich
//Date: September 13, 2021

//Description: This program defines all the functions for the pgm class functions. 

#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool Pgm::Read(const std::string &file)
{
  ifstream fin;
  string s;
  size_t i, j, r, c, v;

  fin.open(file.c_str());
  if (fin.fail()) return false;
  
  if (!(fin >> s)) return false;
  if (s != "P2") return false;
  if (!(fin >> c) || c <= 0) return false;
  if (!(fin >> r) || r <= 0) return false;
  if (!(fin >> i) || i != 255) return false;

  Pixels.resize(r);
  for (i = 0; i < r; i++) {
    Pixels[i].clear();
    for (j = 0; j < c; j++) {
      if (!(fin >> v) || v > 255) return false;
      Pixels[i].push_back(v);
    }
  }
  if (fin >> s) return false;
  fin.close();
  return true;
}


bool Pgm::Write(const std::string &file) const {

	ofstream stream;
	int i, j, r, c, count=0;

	//using file stream to open up file
	stream.open(file.c_str());
	if(stream.fail()) return false; //checking to see if opening file failed 
	if (Pixels.size() <= 0) return false; //making sure there are pixels in the Pixel vector

	//getting rows and columns based on size of the Pixels vector
	r = Pixels.size();
	c = Pixels[0].size();

	//printing to the file 
	stream << "P2" << endl;
	stream << c << " " << r << endl;
	stream << "255" << endl;
	
	//looping through all the pixels and printing them to the file
	for (i=0; i < r; i++) {
			for (j=0; j < c; j++){
				stream << Pixels[i][j];
				count++; //keeping count of number of Pixels printed

				//checking to see if 20 pixels have been printed out yet, if yes (newline printed), if no (space printed)
				if (count % 20 ==  0 || count == r*c) { stream << endl;}
				else { stream << " ";}

			}
	}

	stream.close();
	
	return true;

}

bool Pgm::Create(size_t r, size_t c, size_t pv) {
		
	int i, j;
	
	//checking to make sure the pv value passed is between 0 and 255
	if (pv > 255) return false;
	//checking to make sure rows and columns is a posivite number
	if (r <= 0 || c <= 0) return false;

	//resizing the Pixels vector to the correct size
	Pixels.resize(r);
	for (i=0; i < Pixels.size(); i++) {
		Pixels[i].resize(c);
	}

	//iterating through the Pixels vector and setting each spot equal to the given pixel value 
	for(i=0; i < r; i++) {
		for(j=0; j < c; j++){
			Pixels[i][j] =  pv;
		}
	}
	return true;
}

bool Pgm::Clockwise() {
	
	int i, j, r, c;
	vector <vector <int> > temp;

	r = Pixels.size();
	c = Pixels[0].size();

	//making a temporary vector that is the size of the original vector
	temp.resize(c);
	for (i=0; i < temp.size(); i++) {
		temp[i].resize(r);
	}

	//rotating pmg clockwise by switching the columns value of the original vector to the rows of the temp
	for (i=0; i < c; i++) {
		for (j=0; j < r; j++) {
			//the rows of the original vector are couting down when temp are countng up
			temp[i][j] = Pixels[(r-1)-j][i];
		}
	}

	//storing temp back into Pixels
	Pixels = temp;

	return true;
}

bool Pgm::Cclockwise() {

	int i, j, r, c;
	vector <vector <int> > temp;

	r = Pixels.size();
	c = Pixels[0].size();

	//making a temporary vector that is the size of the original vector
	temp.resize(c);
	for(i=0; i < temp.size(); i++) {
		temp[i].resize(r);
	}

	//rotating the pmg counterclockwise by switching the original rows for the temp columns 
	for (i=0; i < c; i++) {
		for (j=0; j < r; j++) {
			//the temp columns correspond to the original column size minus one minus the current row of the temp
			temp[i][j] = Pixels[j][(c-1)-i];
		}
	}

	Pixels = temp;

	return true;
}

bool Pgm::Pad(size_t w, size_t pv) {
	
	int r, c, i, j, nr, nc;
	vector <vector <int> > temp;

	//making sure pv value is not more than 255
	if(pv > 255) return false;

	//getting rows and columns based on Pixel vector
	r = Pixels.size();
	c = Pixels[0].size();
	
	//creating a temporary vector that is the correct size
	temp.resize(r+(w*2));
	for (i=0; i < temp.size(); i++) {
		temp[i].resize(c+(w*2));
	}

	nr = temp.size(); //new row size w/ padding
	nc = temp[0].size(); //new column size w/ padding
	
	//iterating throught the temporary vector
	for (i=0; i < nr; i++) {
		for (j=0; j < nc; j++) {

			//when padding occurs 
			if (i <  w || i >= r+w || j < w || j >= c+w) {
			 temp[i][j] = pv;
			}
			else {
				//the middle where the original Pixels go
				temp[i][j] = Pixels[i-w][j-w];
			}
		}
	}

	Pixels = temp;
	return true;
}

bool Pgm::Panel(size_t r, size_t c) {
	
	int i, j, ic, ir;
	vector <vector <int> > temp;
	if (r <= 0 || c <= 0) return false;

	ir = Pixels.size();
	ic = Pixels[0].size();

	//creating a temporary vector
	temp.resize(ir*r);
	for(i=0; i < temp.size(); i++) {
		temp[i].resize(ic*c);
	}

	//iterating through the temporary vector
	for(i=0; i < temp.size(); i++) {
		for(j=0; j < temp[0].size(); j++) {
			//the index for the original Pixels vectors is the remainder of the current
			//row and column divided by the original number of rows and columns
			temp[i][j] = Pixels[i%ir][j%ic];
		}
	}

	Pixels = temp;
	return true;
}

bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols) {
	
	int i, j;
	vector < vector <int> > temp;

	//checking to make sure the rows and columns passed are not bigger than the orignal
	if (r > Pixels.size() || c > Pixels[0].size()) return false;

	//checking to make sure the new pixel and the number of requested rows and cols is not bigger than the original
	if (r +  (rows) > Pixels.size() || c + (cols) > Pixels[0].size()) return false;
	
	//creating a temporary vector based on the given rows and cols
	temp.resize(rows);
	for(i=0; i < temp.size(); i++) {
		temp[i].resize(cols);
	}

	//iterating through the temporary vector 
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			//the new Pixels are the given r and c plus the current row and column
			temp[i][j] = Pixels[(r)+i][(c)+j];
		}
	}
	Pixels = temp;
	return true;
}
