//File: ss_solver.cpp
//Name: Josephine Rich
//Date: November 9, 2021

/*Description: This program takes in a grid from the command line and shapes from standard in.
 * This simulates a shape shifter games with bits. The function Find_Solution recursively calls 
 * itself to solve the game. */

#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;
class Shifter {

	public:
		bool Read_Grid_And_Shapes(int argc, const char **argv);
		bool Apply_Shape(int index, int r, int c);
		bool All_Ones();
		bool Find_Solution(size_t index);
		void Print_Solution() const;
	protected: 
		vector <string> Grid;
		vector < vector <string> > Shapes;
		vector <int> Solution_Rows;
		vector <int> Solution_Cols;

};

bool Shifter::Read_Grid_And_Shapes(int argc, const char ** argv) {
	vector<string> s;
	string line, row;
	stringstream ss;
	size_t i=0;

	/*reading from command line and initalizing grid*/
	for(i=1; (int)i < argc; i++) {
		ss.clear(); 
		ss.str(argv[i]); /*using stringstream to change c_string into string*/
		ss >> line;
		Grid.push_back(line); /*pushing back each line onto the Grid*/
	}

	/*reading from standard input to get shapes*/
	while(getline(cin, line)) {
		ss.clear();
		ss.str(line);
		s.clear(); /*clearing the vector so that it doesn't have the perious row*/
		while(ss >> row) {
			s.push_back(row);
		}
		Shapes.push_back(s); /*pushing back the vector which is a shape onto the Shapes vector*/
	}

	return true;
}

bool Shifter::Apply_Shape(int index, int r, int c) {
	size_t shape_rows, shape_cols, grid_rows, grid_cols;
	size_t i, j;

	/*size of Shape*/
	shape_cols = Shapes[index][0].size();
	shape_rows = Shapes[index].size();

	/*size of the Gid*/
	grid_cols = Grid[0].size();
	grid_rows = Grid.size();

	/*making sure the shape fits in the grid*/
	if ((shape_rows + r > grid_rows) || (shape_cols + c > grid_cols)) return false; /*the shape doesn't fit so do nothing*/
	else {
		/*iterating through all the shape bits*/
		for(i=0; i < shape_rows; i++) {
			for(j=0; j < shape_cols; j++) {
				if(Shapes[index][i][j] == '0') {}  /*zero means it's nothing*/
				else {
					if(Grid[i+r][j+c] == '1'){ /*shape and gid bit are both 1*/
						Grid[i+r][j+c] = '0';  /*setting the Grid bit to 0*/
					}
					else {
						Grid[i+r][j+c] = '1'; /*shape bit is 1 and grid bit is 0 -> setting grid bit to 1*/
					}
				}
			}
		}
	}

	return true;
}

bool Shifter::All_Ones() {
	size_t i, j;
	
	/*iterating through all the grid bits to check that they are all 1*/
	for(i=0; i < Grid.size(); i++) {
		for(j=0; j < Grid[i].size(); j++) {
			if(Grid[i][j] == '0') return false;
		}
	}

	return true;
}

bool Shifter::Find_Solution(size_t index){
	size_t  r, c;

	if(index == Shapes.size()) {
		/*the last shape*/
		if(All_Ones() == true) {
			return true;
		}
		else{
			return false;
		}
	}
	
	/*not the last shape and trying every possible spot of that shape*/
	for(r=0; r < Grid.size(); r++) {
		for(c=0; c < Grid[r].size(); c++) {
			if(Apply_Shape(index, r, c) == false){} /*shape did not fit move on to next spot*/
			else {
				/*shape did fit*/
				Solution_Rows.push_back(r); /*storing row and col for solution*/
				Solution_Cols.push_back(c);
				/*calling Find_Solution with next shape*/
				if(Find_Solution(index+1) == false) { /*didn't work so back tracking*/
					Solution_Rows.pop_back(); /*poping off solution row and cols*/
					Solution_Cols.pop_back();
					Apply_Shape(index, r, c); /*applying shape again to undo changes to grid*/
				}
				else {
					return true; /*did find solution with next shape and returning*/
				}
			}
		}
	}

	return false;
}

void Shifter::Print_Solution() const {
	size_t i, j;
	for(i=0; i < Shapes.size(); i++) {
		for(j=0; j < Shapes[i].size(); j++) {
			cout << Shapes[i][j] << " ";
		}
			cout << Solution_Rows[i] << " " << Solution_Cols[i] << endl;
	}
}


int main(int argc, const char **argv) {

	Shifter Game;                           /*new instance of shifter class*/

	Game.Read_Grid_And_Shapes(argc, argv); /*reading in the grid and shapes*/

	if(Game.Find_Solution(0) == true) {
		Game.Print_Solution();             /*printing out solution if solution was found*/
	}	

	return 0;                            /*solution was not found -> exiting program*/
}
