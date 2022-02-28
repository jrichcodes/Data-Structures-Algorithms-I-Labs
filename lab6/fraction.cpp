//File: fraction.cpp
//Name: Josephine Rich
//Date: October 19, 2021

//Description: This file implements the fraction class methods. Most of the mehtods use simple multiplying 
//factorials to either the numerator or the denominator and removing the number if it already exists in the other part. 

#include<iostream>
#include<set>
#include<fraction.hpp>

using namespace std;

void Fraction::Clear() {

	numerator.clear();
	denominator.clear();
}

bool Fraction::Multiply_Number(int n) {
	
	multiset<int>::iterator it;
	
	//error checking n
	if(n <= 0) return false;
	if(n == 1) return true;

	it = denominator.find(n);

	//if number is already in denominator erasing it
	if(it != denominator.end()) denominator.erase(it);
	//else inserting it into the numberator
	else numerator.insert(n);
	return true;
}

bool Fraction::Divide_Number(int n) {

	multiset<int>::iterator it;
	
	//error checking n
	if(n <= 0) return false;
	if(n == 1) return true;
	
	it = numerator.find(n);
	
	//if number is already in numerator erasing it
	if(it != numerator.end()) numerator.erase(it);
	//else inserting it into the denominator
	else denominator.insert(n);
	return true;
}

bool Fraction::Multiply_Factorial(int n) {
	 int i;
	 if(n <= 0) return false;
	 for(i=2; i <= n; i++) {
		if(!Multiply_Number(i)) return false;
	 }
	 return true;
}

bool Fraction::Divide_Factorial(int n) {
	int i;
	if(n <= 0) return false;
	for(i=2; i <=n; i++) {
		if(!Divide_Number(i)) return false;
	}
	return true;
}

bool Fraction::Multiply_Binom(int n, int k) {
	
	//error checking k
	if(k < 0) return false;
	if(k == 0) return true;
	
	Multiply_Factorial(n);
	Divide_Factorial(k);
	Divide_Factorial(n-k);
	return true;
}

bool Fraction::Divide_Binom(int n, int k) {
	
	//error checking k
	if(k < 0) return false;
	if(k == 0) return true;
	
	Divide_Factorial(n);
	Multiply_Factorial(k);
	Multiply_Factorial(n-k);
	return true;
	
}

void Fraction::Invert() {
	denominator.swap(numerator);
}

void Fraction::Print() const {
	
	multiset <int>::const_iterator it;
	int i;

	//using an iterator to print out the numerator
	if(numerator.size() == 0) cout << "1";
	for((it=numerator.begin()), i=0; it != numerator.end(); it++, i++) {
		if(it !=numerator.begin()) cout << " ";
		cout << *it;
		if(i ==  (int)numerator.size()-1) {}
		else cout << " *";
	}
	
	//using an iterator to print out the denominator
	if(denominator.size() ==0) cout << endl;
	for(it=denominator.begin(), i=0; it != denominator.end(); it++, i++) {
		if(i == (int)denominator.size()-1) cout << " / " << *it << endl;
		else cout << " / " << *it;
	}

}

double Fraction::Calculate_Product() const {
	
	double tnumerator=1, tdenominator=1, result=0;
	multiset<int>::iterator it;
	
	//iterating through the numberator and multiplying all the numbers to find total
	if(numerator.size() == 0) tnumerator = 1;
	else {
		for(it=numerator.begin(); it != numerator.end(); it++) {
			tnumerator *= *it;
		}
	}

	//iterating through the denominator and multiplying all the numbers to find total
	if(denominator.size() == 0) tdenominator = 1;
	else{
		for(it=denominator.begin(); it != denominator.end(); it++) {
		tdenominator *= *it;
		}
	}
	
	result = tnumerator / tdenominator;

	return result;

}


