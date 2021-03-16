// SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SudokuSolver.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class SudokuSolver {
private:
	static const int SIZE_Y = 9;
	static const int SIZE_X = 9;

	int sudoku[SIZE_Y][SIZE_X] = { {0,7,0,0,0,0,0,0,9},
								   {5,1,0,4,2,0,6,0,0},
								   {0,8,0,3,0,0,7,0,0},
								   {0,0,8,0,0,1,3,7,0},
								   {0,2,3,0,8,0,0,4,0},
								   {4,0,0,9,0,0,1,0,0},
								   {9,6,2,8,0,0,0,3,0},
								   {0,0,0,0,1,0,4,0,0},
								   {7,0,0,2,0,3,0,9,6} };
public:

	void removeNum(int num, vector<int>& vec) {
		auto i = find(begin(vec), end(vec), num);
		if (i != vec.end()) {
			vec.erase(i);
		}
	}

	void checkRow(int y, int x, vector<int>& v) {
		for (int i = 0; i < SIZE_X; i++) {
			if (sudoku[y][i] != 0) {
				removeNum(sudoku[y][i], v);
			}
		}
	}

	void checkCol(int y, int x, vector<int>& v) {
		for (int i = 0; i < SIZE_Y; i++) {
			if (sudoku[i][x] != 0) {
				removeNum(sudoku[i][x], v);
			}
		}
	}


	void checkSect(int y, int x, vector<int>& v) {
		int ySect = y / 3;
		int xSect = x / 3;
		int yLow, yHigh, xLow, xHigh;
		switch (ySect) {
		case 0:
			yLow = 0;
			yHigh = 3;
			break;
		case 1:
			yLow = 3;
			yHigh = 6;
			break;
		case 2:
			yLow = 6;
			yHigh = 9;
			break;
		default:
			yLow = 0;
			yHigh = 0;
		}

		switch (xSect) {
		case 0:
			xLow = 0;
			xHigh = 3;
			break;
		case 1:
			xLow = 3;
			xHigh = 6;
			break;
		case 2:
			xLow = 6;
			xHigh = 9;
			break;
		default:
			xLow = 0;
			xHigh = 0;
		}
		for (int i = yLow; i < yHigh; i++) {
			for (int j = xLow; j < xHigh; j++) {
				if (sudoku[i][j] != 0) {
					removeNum(sudoku[i][j], v);
				}
			}
		}
	}


	void print() {
		// Top border
		cout << "=========================" << endl;
		// Print row
		for (int i = 0; i < SIZE_Y; i++) {
			// For every row print column
			for (int j = 0; j < SIZE_X; j++) {
				// Print section vertical seperator
				if (((j % 3) == 0) && (j != 0)) {
					cout << "|  ";
				}
				// Print cell
				cout << "|";
				if (sudoku[i][j] == 0) {
					cout << "_";
				}
				else {
					cout << sudoku[i][j];
				}
			}

			// Add right border to final cell in each row
			cout << "|" << endl;

			// Print row seperator except for last row
			if (i != (SIZE_Y - 1)) {
				cout << "-------------------------" << endl;
			}

			// Print section horizontal seperator
			if ((((i + 1) % 3) == 0) && ((i + 1) != SIZE_Y)) {
				cout << "-------------------------" << endl;
			}
		}
		// Bottom border
		cout << "=========================" << endl << endl;
	}

	bool solve(int posY, int posX) {
		if (posY >= SIZE_Y) { // End of puzzle
			cout << "Solved!" << endl;
			return true;
		}
		else {
			// If cell is empty, try to insert values
			if (sudoku[posY][posX] == 0) {
				// Generate possible values
				vector<int> nums{ 1,2,3,4,5,6,7,8,9 };
				// Eliminate invalid values
				checkRow(posY, posX, nums);
				checkCol(posY, posX, nums);
				checkSect(posY, posX, nums);

				bool solved = false;
				int i = 0;
				// While the puzzle has not been solved and there are still available numbers
				while (!solved && (i < nums.size())) {
					// Insert next available number
					sudoku[posY][posX] = nums[i];
					// If x is less than 8, move x up 1.
					if (posX < (SIZE_X - 1)) {
						solved = solve(posY, posX + 1);
					}
					// Else x is equal to 8, reset x to 0 and move y up 1.
					else {
						solved = solve(posY + 1, 0);
					}
					i++;
				}
				// If puzzle has not been solved, remove inserted number
				if (!solved) {
					sudoku[posY][posX] = 0;
				}
				return solved;
			}
			// If cell is not empty, move forward
			else {
				// If x is less than 8, move x up 1.
				if (posX < (SIZE_X - 1)) {
					return solve(posY, posX + 1);
				}
				// Else x is equal to 8, reset x to 0 and move y up 1.
				else {
					return solve(posY + 1, 0);
				}
			}
		}
	}
};

int main()
{
	SudokuSolver sudoku;
	sudoku.print();
	cout << "Solving..." << endl;
	if (!sudoku.solve(0, 0)) {
		cout << "Puzzle can NOT be solved." << endl;
	}
	else {
		sudoku.print();
	}
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
