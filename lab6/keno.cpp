//file: keno.cpp
//Name: Josephine Rich
//Date: October 19, 2021

//Description: This program calculates the probabilty of catching a certain amount of balls and the expected return
//of winning table of a keno game. 

#include<iostream>
#include<fraction.hpp>
#include<cstdio>
using namespace std;

int main() {

	double bet, payout, prob, exr, sum=0;
	int bp, c;
	Fraction F;

	//reading in the first two numbers for the bet and number of balls picked
	cin >> bet;
	cin >> bp;

	//printing bet and balls picked out
	printf("Bet: %.2lf\n", bet);
	printf("Balls Picked: %d\n", bp);
	
	//reading in from standard input and storing it into catch(c) and payout
	while(cin >> c >> payout) {
		//resetting Fraction for each pair of catch and payout
		F.Clear();

		//calculating the probability by using fraction methods
		F.Multiply_Binom(80-bp, 20-c);
		F.Multiply_Binom(bp, c);
		F.Divide_Binom(80, 20);
		prob = F.Calculate_Product();
		
		//calculating the expected return for each winning table
		exr = prob * payout;
		sum += exr;

		cout << "  Probability of catching " << c << " of " << bp << ": " << 
			prob << " -- " << "Expected return: " << exr << endl; 
	}

	printf("Your return per bet: %.2lf\n" , sum-bet);
	printf("Normalized: %.2lf\n", (sum-bet)/bet);

	return 0;
}
