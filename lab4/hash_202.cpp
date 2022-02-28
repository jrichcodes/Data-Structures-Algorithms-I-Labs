//File: hash_202.cpp
//Name: Josephine Rich
//Date: September 20, 2021

/*Description: This lab implements a hash table. The keys are read as hexadecimal and hashed 
 * with the functions XOR or Last7. The two collision resolution options are linear probing and double hashing.*/

#include "hash_202.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <sstream>
#include <iomanip>
using namespace std;

string Hash_202::Set_Up(size_t table_size, const string &fxn, const string &collision){
	
	//error checking the inputs
	if (Keys.size() > 0 || Vals.size() > 0 ) return "Hash table already set up";
	if (table_size < 1) return "Bad table size";
	if (fxn != "Last7" && fxn != "XOR") return "Bad hash function";
	if (collision != "Double" && collision != "Linear") return "Bad collision resolution strategy";
	
	//resizing the Keys and Vals vectors to be the table_size
	Keys.resize(table_size);
	Vals.resize(table_size);

	//setting the hash function and collision variables
	if (fxn == "Last7") Fxn = 'L';
	if (fxn == "XOR") Fxn = 'X';
	if (collision == "Double") Coll = 'D';
	if (collision == "Linear") Coll = 'L';

	//setting Nkeys and Nprobes back to 0
	Nkeys = 0;
	Nprobes = 0;

	return "";
}

int Last7(const string &key) {
	string s, nkey;
	int hash;
	istringstream ss;

	//if the key size is greater than 7, use substring to get last 7 digits
	if(key.size() > 7) {
		nkey = key.substr(key.size()-7);
	}
	else {
		nkey = key;
	}
	//use stringstream to read string as hex and turn into int
	ss.str(nkey);
	ss >> hex >> hash;
	return hash;
}

int Xor(const string &key) {
	string num;
	istringstream ss;
	int i, val=0, hash, num_2;

	//turning key into smaller keys size of 7 by using substring
	for(i=0; i < key.size(); i+=7){
		num = key.substr(i, 7);
		ss.clear();
		ss.str(num);
		ss >> hex >> num_2;
		//Xoring each string
		val = val ^ num_2;
	}

	hash = val;
	
	return hash;
}



string Hash_202::Add(const string &key, const string &val){
	int hash, size, index, nindex, i, a, count=1;
	size = Keys.size();
	
	//error checking
	if(size < 0) return "Hash table not set up";
	if(key == "") return "Empty key";
	
	//checking the key 
	for(i=0; i < key.length(); i++) {
		if ((key[i] < '0' || key[i] > '9') && (key[i] < 'a' || key[i] > 'f')) {
			return "Bad key (not all hex digits)";
		}
	}

	//checking val
	if (val == "") return "Empty val";

	//for Last 7 Hashing
	if(Fxn == 'L') {
		hash = Last7(key);
		index = hash % size;
	}
	
	//for Xor Hashing
	if(Fxn == 'X') {
		hash = Xor(key);
		index = hash % size;
	}
	
	//checking to see if the index is empty or not
	if(Vals[index] == "") {
		Vals[index] = val;
		Keys[index] = key;
		Nkeys += 1;
		return "";
	}
	else {

		//linear collision resolution
		if(Coll == 'L') {
			while(Vals[index] != "") {
				index += 1;
					if (index > Keys.size() -1) index = 0;
					if (Nkeys >= Keys.size()) return "Hash table full";
					if(Keys[index] == key) return "Key already in the table";
				}

				Vals[index] = val;
				Keys[index] = key;
				Nkeys += 1;
				return "";
			}
		
		//setting new index variable to the original index
		nindex = index;

		//double hashing collision resolution
		if(Coll == 'D') {
			
			//doing the double hashing based on what hash function was used before
			if(Fxn == 'L') {
				a = Xor(key) % size;
			}
			else {
				a = Last7(key) % size;
			}

			if(a == 0) a=1;

			//checking each index until there is a blank space
			while(Keys[nindex] != "") {
				//double hashing equation
				nindex = (hash + (a * count)) % size;
				count ++;
				if(Nkeys >= Keys.size()) return "Hash table full";
				if (nindex == index) return "Cannot insert key";
				if(Keys[nindex] == key) return "Key already in the table";
			}


			Vals[nindex] = val;
			Keys[nindex] = key;
			Nkeys += 1;
			return "";
		}
	}

}

string Hash_202::Find(const string &key){
	
	int i, a, size, index, hash, count=0, nindex, count_2=1;
	size = Keys.size();

	//checking to make sure the hash table has been set up
	if (Keys.size() <= 0) return "";
	
	//checking for valid key
	for(i=0; i < key.length(); i++) {
		if ((key[i] < '0' || key[i] > '9') && (key[i] < 'a' || key[i] > 'f')) return "";
	}

	//resetting Nprobes
	Nprobes = 0;

	//for Last7 Hashing 
	if(Fxn == 'L') {
		hash = Last7(key);
		index = hash % size;
	}

	//for Xor Hashing 
	if(Fxn == 'X') {
		hash = Xor(key);
		index = hash % size;
	}

	//checking to see if the keys matches
	if (Keys[index] == key) {
		return Vals[index];
	}
	else {

		//for linear collision
		if(Coll == 'L') {
			//checking each index until keys match
			while(Keys[index] != key) {
				index += 1;
				Nprobes += 1;
				count ++;
				if (index == Keys.size()) index = 0;
				if (count == Keys.size()) return "";
			}

			return Vals[index];
		}
		
		//setting new index variable to the original index
		nindex = index;

		//for double hashing collision resolution
		if(Coll == 'D') {

			if(Fxn == 'L') {
				a = Xor(key) % size;
			}
			else {
				a = Last7(key) % size;
			}

			if(a == 0) a=1;

			//checking each index until finds matching key
			while(Keys[nindex] != key) {
				nindex = (hash + (a * count_2)) % size;
				count_2 ++;
				Nprobes += 1;
				if(nindex == index) return "";
			}

			return Vals[nindex];
		}
	}
}

void Hash_202::Print() const{
	int i;
	//printing out the hash table
	for(i=0; i < Vals.size(); i ++) {
		if (Vals[i] != "") {
				cout << right << setw(5) << i << " " << Keys[i] << " " <<  Vals[i] << "\n";
			}
		}
}

size_t Hash_202::Total_Probes() {
	size_t i, TP=0;
	//looping throught the key vector to calculate the total probes
	for(i=0; i < Keys.size(); i++) {
		if(Keys[i] == "") {
		}
		else {
			Find(Keys[i]);
			TP += Nprobes;
		}
	}

	return TP;
}


