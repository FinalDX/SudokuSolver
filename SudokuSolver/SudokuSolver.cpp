#include "SudokuSolver.h"

void SudokuSolver::removeNum(int num, std::vector<int>& vec) {
	auto i = find(begin(vec), end(vec), num);
	if (i != vec.end()) {
		vec.erase(i);
	}
}

void SudokuSolver::checkRow(int y, int x, std::vector<int>& v) {
	for (int i = 0; i < SIZE_X; i++) {
		if (sudoku[y][i] != 0) {
			removeNum(sudoku[y][i], v);
		}
	}
}

void SudokuSolver::checkCol(int y, int x, std::vector<int>& v) {
	for (int i = 0; i < SIZE_Y; i++) {
		if (sudoku[i][x] != 0) {
			removeNum(sudoku[i][x], v);
		}
	}
}


void SudokuSolver::checkSect(int y, int x, std::vector<int>& v) {
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
		yLow = -1;
		yHigh = -1;
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
		xLow = -1;
		xHigh = -1;
	}
	for (int y = yLow; y < yHigh; y++) {
		for (int x = xLow; x < xHigh; x++) {
			if (sudoku[y][x] != 0) {
				removeNum(sudoku[y][x], v);
			}
		}
	}
}

void SudokuSolver::printBanner() {
	std::cout << "=========================" << std::endl
		<< "S U D O K U   S O L V E R" << std::endl
		<< "=========================" << std::endl;
}

void SudokuSolver::print() {
	// Top border
	std::cout << "=========================" << std::endl;
	// Print row
	for (int i = 0; i < SIZE_Y; i++) {
		// For every row print column
		for (int j = 0; j < SIZE_X; j++) {
			// Print section vertical seperator
			if (((j % 3) == 0) && (j != 0)) {
				std::cout << "|  ";
			}
			// Print cell
			std::cout << "|";
			if (sudoku[i][j] == 0) {
				std::cout << "_";
			}
			else {
				std::cout << sudoku[i][j];
			}
		}

		// Add right border to final cell in each row
		std::cout << "|" << std::endl;

		// Print row seperator except for last row
		if (i != (SIZE_Y - 1)) {
			std::cout << "-------------------------" << std::endl;
		}

		// Print section horizontal seperator
		if ((((i + 1) % 3) == 0) && ((i + 1) != SIZE_Y)) {
			std::cout << "-------------------------" << std::endl;
		}
	}
	// Bottom border
	std::cout << "=========================" << std::endl << std::endl;
}

bool SudokuSolver::solve(int posY, int posX) {

	if (posY >= SIZE_Y) { // End of puzzle
		std::cout << "Solved!" << std::endl;
		return true;
	}
	else {
		if (sudoku[posY][posX] == 0) { // Empty cell
			// Generate possible values
			std::vector<int> nums{ 1,2,3,4,5,6,7,8,9 };
			// Eliminate invalid values
			checkRow(posY, posX, nums);
			checkCol(posY, posX, nums);
			checkSect(posY, posX, nums);

			bool solved = false;
			int i = 0;
			// While puzzle has not been solved and 
			// there are still available values
			while (!solved && (i < nums.size())) {
				// Insert available value
				sudoku[posY][posX] = nums[i];
				// Change position
				if (posX < (SIZE_X - 1)) {
					solved = solve(posY, (posX + 1));
				}
				else {
					solved = solve((posY + 1), 0);
				}
				i++;
			}
			// If all available values were tried and 
			// puzzle has not been solved, remove inserted value
			if (!solved) {
				sudoku[posY][posX] = 0;
			}
			return solved;
		}
		else {
			if (posX < (SIZE_X - 1)) {
				return solve(posY, (posX + 1));
			}
			else {
				return solve((posY + 1), 0);
			}
		}
	}
}

void SudokuSolver::edit() {
	std::string line; // Input line
	std::string row; // Holds the row number for output
	bool valid = false; // Valid input flag
	bool done = false; // Input done flag

	// Regular Expression pattern for validating input
	std::regex pattern("^[0-9]{9}$");

	print();
	int i = 0;
	while (i < SIZE_Y) {
		std::cout << "Commands:" << std::endl
			<< "Input 'n' to go to the next row." << std::endl
			<< "Input 'b' to return to the previous row." << std::endl
			<< "Input 'e' to end the sudoku editing process." << std::endl
			<< "Input a value for each cell of this row, "
			<< "use 0 for empty spaces." << std::endl
			<< "Press 'Enter' when done." << std::endl;
		// Output row number
		row = "Row " + std::to_string(i + 1) + ": ";
		std::cout << row;
		// Get input line
		std::getline(std::cin, line);

		if (line == "n") {
			if (i == (SIZE_Y - 1)) {
				std::cout << "Currently on the last row." << std::endl;
			}
			else {
				i++;
			}
		}
		else if (line == "b") {
			if (i == 0) {
				std::cout << "Currently on the first row." << std::endl;
			}
			else {
				i--;
			}
		}
		else if (line == "e") {
			std::cout << "Sudoku editing cancelled!" << std::endl;
			break;
		}
		else if (regex_match(line, pattern)) {
			// Insert into row
			for (int j = 0; j < SIZE_X; j++) {
				sudoku[i][j] = (int)(line[j]) - 48;
			}
			print();
			i++;
		}
		else {
			std::cout << "Invalid input!" << std::endl << std::endl;
		}
	}
}