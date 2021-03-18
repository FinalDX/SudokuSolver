#include "SudokuSolver.h"

using namespace std;

int main()
{
	SudokuSolver sudoku;
	string line;
	bool done = false;

	while (!done) {
		sudoku.printBanner();
		sudoku.print();

		cout << "Commands:" << endl
			<< "Input 's' to solve the sudoku." << endl
			<< "Input 'e' to edit the sudoku." << endl
			<< "Input 'x' to exit." << endl;

		getline(cin, line);

		if (line == "s") {
			cout << "Solving..." << endl;
			if (!sudoku.solve(0, 0)) {
				cout << "Invalid puzzle. No solution." << endl;
			}
		}
		else if (line == "e") {
			sudoku.edit();
		}
		else if (line == "x") {
			cout << "Exited Sudoku Solver" << endl;
			done = true;
		}
		else {
			cout << "Invalid command!" << endl;
		}
	}
	return 0;
}