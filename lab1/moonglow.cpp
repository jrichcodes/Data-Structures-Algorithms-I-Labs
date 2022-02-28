//File: moonglow.cpp
//Name: Josephine Rich 
//Date: August 30, 2021

/*Description:  This program reads input and sorts it to find exam scores and name. The if-else statement checks to see if the input is a number or a string. Another if-else statement checks for the word "NAME" and "AVERAGE".
 */

#include<iostream>
#include<string>
using namespace std;

int main () {
  
	string word, text;
	double number, a, b = 0;
	int i = 0;
	double exam_score = 0;
	double average = 0;
	string student_name;
	
//reads input until the end of file is reached 
	while (!cin.eof()) {
		if ( cin >> number ) {

			//if it is a number, it adds it to the exam_score
			exam_score += number;
		}
		else {
			cin.clear();
			cin >> word;

			//tests to see if the word is "NAME" or "AVERAGE"
			if (word  == "NAME") {
				cin >> student_name;
			}
			else if (word  == "AVERAGE") {
				
				//reads in numbers  until it fails and then calculates average
				while ( cin >> a ) {
					b  = b + a;
					i++;
				}

				//tests to see if i = 0 or else something weird happens when you divide by 0
				if (i != 0) {					
					average = b / i;
					exam_score += average;
				}
				cin.clear();

			}
			else {

			}
			
			//resets b and i 
			b = 0;
			i = 0;
		}
	}

	//prints out the name and score once end of file is reached
	cout << student_name << " " << exam_score << endl;

	return 0;
}
