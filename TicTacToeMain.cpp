#include "GameManager.h"
#include <iostream>;

using namespace std;
/* Tic-Tac-Toe Main Program
Author: Irene Zaugg, S02672231
Class: CSC 234
Instructor: Robert Gilanyi

Runs main class for a Tic-Tac-Toe game. Collects parameters and passes them to the
GameManager object. Parameters to be set by user are:
	numPlayers: number of players
	rows: number of rows
	cols: number of columns
	toWin: number of game tokens in a row required for victory */
int main() {
	int numPlayers, rows, cols, toWin;

	// Collect numPlayers.
	cout << "Enter number of players (2 - 4): ";
	while (!(cin >> numPlayers)) {
		cout << "Incorrect input. Try again: ";
		cin.clear();
		cin.ignore(100, '\n');
	}

	while (numPlayers < 2 || numPlayers > 4) {
		cout << "Must be between 2 and 4. Try again: ";
		while (!(cin >> numPlayers)) {
			cout << "Incorrect input. Try again: ";
			cin.clear();
			cin.ignore(100, '\n');
		}
	}

	// Collect rows.
	cout << "Enter number of rows (3 - 15): ";
	while (!(cin >> rows)) {
		cout << "Incorrect input. Try again: ";
		cin.clear();
		cin.ignore(100, '\n');
	}

	while (rows < 3 || rows > 15) {
		cout << "Must be between 3 and 15. Try again: ";
		while (!(cin >> rows)) {
			cout << "Incorrect input. Try again: ";
			cin.clear();
			cin.ignore(100, '\n');
		}
	}

	// Collect cols.
	cout << "Enter number of columns (3 - 15): ";
	while (!(cin >> cols)) {
		cout << "Incorrect input. Try again: ";
		cin.clear();
		cin.ignore(100, '\n');
	}

	while (cols < 3 || cols > 15) {
		cout << "Must be between 3 and 15. Try again: ";
		while (!(cin >> cols)) {
			cout << "Incorrect input. Try again: ";
			cin.clear();
			cin.ignore(100, '\n');
		}
	}

	// Collect toWin.
	cout << "How many in a row to win (between 3 and either max rows or columns): ";
	while (!(cin >> toWin)) {
		cout << "Incorrect input. Try again: ";
		cin.clear();
		cin.ignore(100, '\n');
	}

	while (toWin < 3 || toWin > min(rows, cols)) {
		cout << "Must be between 3 and " << min(rows, cols) << ". Try again: ";
		while (!(cin >> toWin)) {
			cout << "Incorrect input. Try again: ";
			cin.clear();
			cin.ignore(100, '\n');
		}
	}

	char playAgain = 'y';
	// Initiate GameManager.
	do {
		GameManager game(numPlayers, rows, cols, toWin);
		game.runGame();
		cout << "Good game. Would you like to play again? (y/n) ";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
	
	return 0;
}