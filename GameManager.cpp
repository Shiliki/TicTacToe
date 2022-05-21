#include "GameManager.h"
#include <iostream>
#include <string>

using namespace std;

/* Constructor.

Precondition:
	Called from main function.

	param int enteredPlayers: number of players (defaulted to 2 if not in bounds).
	param int numRows: number of rows.
	param int numCols: number of columns.
	param int toWin: number of matching items required to win.
	
Postcondition:
	Game initialized with number of rows, columns, and required matches to win. */
GameManager::GameManager(int enteredPlayers, int numRows, int numCols, int toWin) {
	if (numPlayers >= 2 && numPlayers <= 4) {
		numPlayers = enteredPlayers;
		players = new PlayerPtr[numPlayers];
	}
	else {
		numPlayers = 2;
		players = new PlayerPtr[numPlayers];
	}

	setupPlayers(numPlayers);

	// Restrictions for number of rows, columns, and win conditions built into Board class.
	gameBoard = new Board(numRows, numCols, toWin);
}

/* Handles the bulk of the game running.

Precondition:
	GameManager initialized from main function.
	
Postcondition:
	Runs through all steps of players' turns using playTurn() class and checks whether game
	has ended. */
void GameManager::runGame() {
	int currentPlayer = 0;
	bool gameOver = false;

	do {
		gameBoard->printBoard();
		if (playTurn(*players[currentPlayer]))
			gameOver = true;

		if (++currentPlayer >= numPlayers)
			currentPlayer = 0;

	} while (!gameOver);
}

/* Sets up the players dynamic array.

Precondition:
	Called from constructor. Prompts user for name and game piece.
	
	param int numPlayers: Number of Player objects in array.
	
Postcondition:
	All Players in array have been initialized. */
void GameManager::setupPlayers(int numPlayers) {
	string name;
	char gamePiece;

	for (int i = 0; i < numPlayers; i++) {
		cout << "Player " << i + 1 << ", please enter your name: ";
		cin >> name;
		cout << "Enter your game piece: ";
		cin >> gamePiece;
		cin.clear();
		cin.ignore(100, '\n');

		players[i] = new Player(name, gamePiece);
	}
}

/* Takes user inputs for game moves, then checks if game is either
tied or won using endGame function.

Precondition:
	param Player& currentPlayer: passed by reference currently active Player.
	
Postcondition:
	If player enters invalid space on board, recursively runs until appropriate
	choice is made. If game is over (won or tied), returns true. */
bool GameManager::playTurn(Player& currentPlayer) {
	int row, col;
	
	cout << currentPlayer.getName() << "'s turn: " << endl;
	cout << "=================" << endl;

	cout << "Enter a row: ";
	while (!(cin >> row)) {
		cout << "Incorrect input. Please try again: ";
		cin.clear();
		cin.ignore(100, '\n');
	}

	while (row < 0 || row > gameBoard->getRows()) {
		cout << "Out of bounds. Please try again: ";
		cin >> row;
	}

	cout << "Enter a column: ";
	while (!(cin >> col)) {
		cout << "Incorrect input. Please try again: ";
		cin.clear();
		cin.ignore(100, '\n');
	}
	while(col < 0 || col > gameBoard->getCols()){
		cout << "Out of bounds. Please try again: ";
		cin >> col;
	}
	// Adjust for comfortable user entry.
	row--;
	col--;

	// If player chooses a non-empty space on board, run function recursively.
	if (!gameBoard->playTurn(row, col, currentPlayer.getGamePiece())) {
		cout << "That space is not available. Please try again." << endl;
		playTurn(currentPlayer);
	}

	// endGame checks if game has been won or tied.
	if (endGame(row, col, currentPlayer.getName()))
		return true;
	else
		return false;
}

/* Returns true if game has been won or tied.

Precondition:
	param int playedRow: user chosen row.
	param int playedCol: user chosen column.
	param string currentPlayer: name of current player (used for victory message).
	
Postcondition:
	Prints message if game has been won or tied and returns true, else returns false. */
bool GameManager::endGame(int playedRow, int playedCol, string currentPlayer) {
	if (gameBoard->tiedGame()) {
		gameBoard->printBoard();
		cout << "*************" << endl;
		cout << "Game is tied." << endl;
		cout << "*************" << endl;
		return true;
	}

	if (gameBoard->gameWon(playedRow, playedCol)) {
		gameBoard->printBoard();
		cout << "*****************" << endl;
		cout << currentPlayer << " wins!" << endl;
		cout << "*****************" << endl;
		return true;
	}

	return false;
}