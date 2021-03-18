#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>

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

	void removeNum(int, std::vector<int>&);
	void checkRow(int, int, std::vector<int>&);
	void checkCol(int, int, std::vector<int>&);
	void checkSect(int, int, std::vector<int>&);

public:
	void printBanner();
	void print();
	bool solve(int, int);
	void edit();
};

#endif