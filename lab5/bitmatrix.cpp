//File Name: bitmatrix.cpp
//Name: Josephine Rich
//Date: October 4, 2021

/*Description: This lab implements the Bitmatrix class. There are methods within the class that can be used to manipulate the matrix
 * which is stored in vector of vector of strings. There are four procedures that are outside the Bitmatrix class that use the methods
 * of the Bitmatrix class. There is a hash table to store and retrieve bitmatrices.*/

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.hpp"
#include<iostream>
using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols)
{
	size_t i;

	//checking the rows and cols
	if(rows <= 0) throw((string)"Bad rows");
	if(cols <= 0) throw((string)"Bad cols");

	//resizing the matrix and setting everything to 0
	M.resize(rows);
	for(i=0; i < M.size(); i++) {
		M[i].resize(cols, '0');
	}
}
           
Bitmatrix::Bitmatrix(const string &fn)
{
	ifstream fin;
	size_t columns=0;
	string line;
	char k;
	int i=0;
	string temp;

	fin.open(fn.c_str());
	if (fin.fail()) throw((string)"Can't open file");

	//getting the first row and number of columns
	while(getline(fin, line)) {
		//ignoring empty lines
		if(line == "") continue;
		temp = "";
		for(i=0; i < line.size(); i++) {
			k = line[i];
			if(k != '0' && k != '1' && k != ' ') throw((string)"Bad file format");
			//ignoring spaces otherwise pushing into M
			if(k == ' '){}
			else temp.push_back(k);
		}
		M.push_back(temp);
		//checking that all columns are the same size
		if(columns == 0) columns = temp.size();
		else if (columns != temp.size()) throw((string)"Bad file format");
	}
	fin.close();
	if(M.size() == 0) throw((string)"Bad file format");
}
Bitmatrix *Bitmatrix::Copy() const
{
	//pointer to an instance of the Bitmatrix class
	Bitmatrix *bmp;
	//allocating new memory for the Bitmatrix
	bmp = new Bitmatrix(1,1);

	//setting the new Bitmatrix M equal to the current one
	bmp->M = M;

	return bmp;
}
                 
bool Bitmatrix::Write(const string &fn) const
{
	ofstream stream;
	size_t i, j, r, c;
	
	stream.open(fn.c_str());
	if(stream.fail()) return false;
	
	r = M.size();
	c = M[0].size();

	//looping through all the pixels and printing them to the file
	for(i=0; i < r; i++) {
		for(j=0; j < c; j++) {
			stream << M[i][j];
		}
		stream << "\n";
	}
	return true;
}

 
void Bitmatrix::Print(size_t w) const
{
	size_t  r, c, i, j;
	
	r = M.size();
	c = M[0].size();

	//looping throught the Bitmatrix
	for(i=0; i < r; i ++){
		//printing an extra newline after every w rows
		if(w == 0) {}
		else if(i%w == 0 && i != 0) cout << "\n";
		for(j=0; j < c; j++) {
			//printing a space afer every w characters
			if ((j%c) == 0 || w == 0){} 
			else if((j) % w == 0) cout << " ";
			cout << M[i][j];
		}
		cout << "\n";
	}
}
                 
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
  ofstream stream;
  size_t r, c, i, j, ip, jp, k=0, l=0;
  r = M.size();
  c = M[0].size();

  vector<vector <int> > temp;

  //checking border and p
  if(p < 0 || border < 0) return false;

  //using file stream to open up file
  stream.open(fn.c_str());
  if(stream.fail()) return false;

  //resizing temp and setting everything to the boarder
  temp.resize(((r+1) * border) + (r*p));
  for(i=0; i < temp.size(); i++) {
	  temp[i].resize((c+1) * border + (c*p), 0);
  }

  //looping through temp and placing correct values from M bitmatrix
  for(i=border; i < (temp.size()-border); i+=(p+border)) {
	  for(j=border; j < (temp[0].size()-border); j+=(p+border)) {
		  for(ip=0; ip < p; ip++){
			  for(jp=0; jp < p; jp++) {
				  if(M[k][l] == '0') temp[i+ip][j+jp] = 255;
				  else temp[i+ip][j+jp] = 100;
			  }
		  }
		  l++;
	  }
	  l=0;
	  k++;
  }

  //printing to the file
  stream << "P2" << endl;
  stream << temp[0].size() << " " << temp.size() << endl;
  stream << "255" << endl;

  //looping through the temp vector to print
  for(i=0; i < temp.size(); i++){
	  for(j=0; j < temp[0].size(); j++) {
		  stream << temp[i][j] << " ";
	  }
  }

  stream.close();
  return true;
}

int Bitmatrix::Rows() const
{
  return M.size();
}
                            
int Bitmatrix::Cols() const
{
  return M[0].size();
}
                            
char Bitmatrix::Val(int row, int col) const
{
  char num;
  
  //checking row and col
  if(row >= Rows() || row < 0) return 'x';
  if(col >= Cols() || col < 0) return 'x';
  num  = M[row][col];
  return num;
}
            
bool Bitmatrix::Set(int row, int col, char val)
{
	char store;

	//error checking the row and col
	if(row >= Rows() || row < 0) return false;
	if(col >= Cols() || col < 0) return false;

	//storing a char if a int or a char is given
	if((val == '0') || (val == 0 )) store = '0';
	else if((val == '1') || (val == 1)) store = '1';
	else return false;
	M[row][col] = store;
	
	return true;
}
        
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
  string temp;
  size_t c, i;
  c = M[r1].size();

  //error checking the rows 
  if(r1 >= Rows() || r1 < 0) return false;
  if(r2 >= Rows() || r2 < 0) return false;

  //storing row1 in a temporary string
  for(i=0; i < c; i++){
	 temp.push_back(M[r1][i]);
  }

  //setting row1 equal to row2
  for(i=0; i < c; i++) {
	M[r1][i] = M[r2][i];
  }

  //setting row2 equal to temporary string
  for(i=0; i < c; i++) {
	  M[r2][i] = temp[i];
  }

  return true;
}
              
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
  string temp;
  size_t i, c;
  char val;


  //checking for valid rows
  if(r1 >= M.size() || r1 < 0) return false;
  if(r2 >= M.size() || r2 < 0) return false;

  c = M[r1].size();
  //adding the two rows and storing result in a temporary string
  for(i=0; i < c; i++) {
	val = (M[r1][i] + M[r2][i]) % 2;
	temp.push_back(val);
  }

  //setting the temporary string equal to r1
  for(i=0; i < c; i++) {
	  M[r1][i] = temp[i] + '0';
  }

  return true;
}
      

Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
  size_t i, j;
  Bitmatrix *bmp;
  char bit;

  //checking to make sure the Bitmatrixs are the same size 
  if((a1->Rows() != a2->Rows()) || (a1->Cols() != a2->Cols())) return NULL;
  
  //setting the pointer equal to a new instance of the Bitmatrix class
  bmp = new Bitmatrix(a1->Rows(), a1->Cols());

  //adding the rows of the two Matrixs
  for(i=0; i < a1->Rows(); i++) {
	  for(j=0; j < a1->Cols(); j++) {
		bit = ((a1->Val(i, j)- '0') + (a2->Val(i, j) - '0') ) % 2;
		bmp->Set(i, j, bit);
	}
  }
 return bmp;
}

Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
	size_t i, j, total= 0, k;
	char bit;
	Bitmatrix *bmp;

	//checking to make sure the given Bitmatrixs can be mulitiplied
	if(a1->Cols() != a2->Rows()) return NULL;

	//setting bmp to a new Bitmatrix 
	bmp = new Bitmatrix(a1->Rows(), a2->Cols());

	//mulitplying the Bitmatrixs
	for(i=0; i < a1->Rows(); i++){
		for(j=0; j < a2->Cols(); j++) {
			for(k=0; k < a1->Cols(); k++){
				//val gives a char so subtracting '0' to get a number
				total += (a1->Val(i, k) - '0') * (a2->Val(k, j) - '0');
			}
			//calculating the bit and then setting it in the new Bitmatrix
			bit = (total % 2);
			bmp->Set(i, j, bit);
			total = 0;
		}
	}
	return bmp;
}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
	Bitmatrix *bmp;
	size_t i, j, r=0;
	char bit;

	//checking rows is not empty
	if(rows.size() == 0) return NULL;

	bmp = new Bitmatrix(rows.size(), a1->Cols());

	//checking rows has valid indices
	for(i=0; i < rows.size(); i++){
		if((rows[i] > (a1->Rows())) || (rows[i] < 0)) return NULL;
	}

	//creatig the new bitmatrix of the given rows
	for(i=0; i < rows.size(); i++) {
		for(j=0; j < a1->Cols(); j++){
			bit  = a1->Val(rows[i], j);
			bmp->Set(r, j, bit);
		}
		r++;
	}
	return bmp;
}

Bitmatrix *Inverse(const Bitmatrix *m)
{
	int i, j, r, c;
	Bitmatrix *M, *Inv;
	bool finding = true;

	//getting rows and cols
	r = m->Rows();
	c = m->Cols();

	if(r != c) return NULL;

	//copy of the original Bitmatrix
	M = m->Copy();

	//creating a new Bitmatrix to be Inv
	Inv = new Bitmatrix(r, c);
	
	//creating an identity matrix of the same size called Inv
	for(i=0; i < r; i++) {
		for(j=0; j < c; j++) {
			if(i == j) Inv->Set(i, j, 1);
			else Inv->Set(i, j, 0);
		}
	}

	//going through each row of M from the start
	for(i=0; i < r; i++) {
		if(M->Val(i, i) == '1');
			else {
				j=i;
				finding = true;
				while(finding) {
					j++;
					if( j >= r) return NULL;
					if(M->Val(j,i) == '1')finding = false;
				}
				M->Swap_Rows(i, j);
				Inv->Swap_Rows(i, j);
			}
			//getting rid of everything below
			for(j=i+1; j < r; j++) {
				if(M->Val(j, i) == '1') {
				M->R1_Plus_Equals_R2(j, i);
				Inv->R1_Plus_Equals_R2(j,i);
				}
			}
	}

	//going through each row of M from the bottom
	for(i=r-1; i >= 0; i--) {
		for(j= (i-1); j >= 0; j--) {
			if(M->Val(j, i) == '1') {
			M->R1_Plus_Equals_R2(j, i);
			Inv->R1_Plus_Equals_R2(j, i);
			}
		}
	}

	delete M;

  return Inv;
}

unsigned int djb_hash(const string &s)
{
	size_t i;
	unsigned int h;
	
	h= 5381;

	//hash equation
	for (i=0; i < s.size(); i++) {
		h = (h << 5) + h + s[i];
	}
	return h;
}
BM_Hash::BM_Hash(int size)
{
	//error checking size
	if(size <= 0) throw((string) "Bad size");
	
	//resizing the table vector
	Table.resize(size);
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
	size_t i, index, tsize;
	tsize = Table.size(); 
	HTE entry;
	if(tsize <= 0) return false;

	//setting the public variables of the new instance of the HTE class 
	entry.key = key;
	entry.bm = bm;

	//hashing the key
	index = djb_hash(entry.key) % tsize;
	
	//checking to see if the key already exists 
	for(i=0; i < Table[index].size(); i++) {
		if(Table[index][i].key == entry.key) return false;
	}

	//pushing back the entry onto the table vector
	Table[index].push_back(entry);
	
	return true;
}
    
Bitmatrix *BM_Hash::Recall(const string &key) const
{
	size_t i, index;
	HTE entry;

	//hashing the key
	index = djb_hash(key) % Table.size();
	
	//iterating through the table to find key
	for(i=0; i < Table[index].size(); i++) {
		if(Table[index][i].key == key) {
			entry = Table[index][i];
			return entry.bm;
		}
	}

	return NULL;

}
      
vector <HTE> BM_Hash::All() const
{
  vector <HTE> rv;
  size_t i, j;
  HTE entry;

  //iterating through the hash table and pushing back on to rv
  for(i=0; i < Table.size(); i++) {
	  for(j=0; j < Table[i].size(); j++) {
		  entry = Table[i][j];
		  rv.push_back(entry);
	  }
  }

  return rv;
}
