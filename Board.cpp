#include "Board.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
/* Constructor. Controls for size of rows, columns, and toWin condition.

Precondition:
	GameManager calls new Board object with constructors.
	param int rows: Number of rows in board.
	param int cols: Number of cols in board.
	param int toWin: Number of matching items required to win a game.
	
Postcondition:
	board[][] dynamic array is constructed with given parameters.
	Local variables rows, cols, toWin, and turnsPlayed are set. */
Board::Board(int rows, int cols, int toWin) {
	if (rows >= 3 && rows <= 15)
		this->rows = rows;
	else
		this->rows = 3;
	
	if (cols >= 3 && cols <= 15)
		this->cols = cols;
	else 
		this->cols = 3;
	
	if (toWin < min(rows, cols) && toWin >= 3)
		this->toWin = toWin;
	else
		this->toWin = 3;

	turnsPlayed = 0;

	board = new char*[rows];

	for (int i = 0; i < rows; i++) {
		board[i] = new char[cols];
	}

	clearBoard();
}

/* Creates a blank board filled with BLANK_SPACE characters.

Precondition:
	Board is initialized but either empty or filled with characters from prior game.
	Note that current implementation does not require this to be called for a new game.

Postcondition:
	All columns and rows are filled with designated BLANK_SPACE character ('.'). */
void Board::clearBoard() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			board[i][j] = BLANK_SPACE;
		}
}

/* Prints the board in formatted style.

Precondition:
	Board has been initialized and filled with characters.
	
Postcondition:
	Prints board to output device with numbered rows and columns. */
void Board::printBoard() {
	printf("   | ");
	for (int i = 0; i < cols; i++) {
		cout << i + 1;
		if (i + 1 < 10)
			cout << " ";
		cout << "| ";
	}
	cout << endl;
	cout << "---";

	for (int i = 0; i < cols; i++) {
		printf("----");
	}
	//cout << board[0][0];
	cout << endl;

	for (int i = 0; i < rows; i++) {
		printf("%d", i + 1);
		if (i + 1 < 10)
			printf(" ");
		printf(" | ");

		for (int j = 0; j < cols; j++) {
			cout << board[i][j] << " | ";
		}
		cout << endl;
	}

	printf("----");

	for (int i = 0; i < cols; i++) {
		printf("----");
	}
	cout << endl;
}

/* Handles manipulation of board during a player's turn.
* Returns true if player's position choice is valid.

Precondition:
	Player enters a row and a column.
	
	param int row: Player's chosen row.
	param int col: Player's chosen column.
	param char playerPiece: current player's game piece.
	
Postcondition:
	If the chosen location is available (does not equal BLANK_SPACE)
	position in board[][] array is changed to player's game piece,
	total number of played turns is updated, and returns true. Else
	returns false. */
bool Board::playTurn(int row, int col, char playerPiece) {
	if (board[row][col] != BLANK_SPACE) {
		return false;
	}
	else {
		board[row][col] = playerPiece;
		turnsPlayed++;
		return true;
	}
}

/* Determines if any of the victory conditions are met.

Precondition:
	Uses checkRow, checkCol, and checkDiagional to determine if any
	victory conditions have been met.
	
Postcondition:
	If any helper functions return true, game is won (return true).
	Else return false.*/
bool Board::gameWon(int playedRow, int playedCol) {
	if (checkRow(playedRow) || checkCol(playedCol) || checkDiagonal(playedRow, playedCol))
		return true;
	else
		return false;
}

/* Checks if the number of turns that have been played equals the full
dimensions of the board (number of rows * number of columns).

Precondition:
	Players have played some number of rounds (initiailzed at 0 by constructor).
	
Postcondition:
	If the total number of turns played equals the total number of 
	elements in the board array, return true (game is tied). Else return false. */
bool Board::tiedGame() {
	if (turnsPlayed >= rows * cols)
		return true;
	else
		return false;
}

/* Returns value of rows. */
int Board::getRows() {
	return rows;
}

/* Returns value of cols. */
int Board::getCols() {
	return cols;
}

/* Checks to see if the row used by the player contains suitable matches.

Precondition:
	Player entered a row and column for a new player piece, which was
	successfully inserted.
	
	param int playedRow: Row that player inserted a new piece into.
	
Postcondition:
	If there are enough matching items in a row that are not BLANK_SPACEs,
	returns true. Else returns false.*/
bool Board::checkRow(int playedRow) {
	int counter = 1; // Counts total number of matched items in current sequence.
	for (int i = 0; i < cols - 1; i++) {
		// If there are enough items on the row that match (discounts blank spaces)
		if (board[playedRow][i] == board[playedRow][i + 1] && board[playedRow][i] != BLANK_SPACE) {
			counter++; // Increase counter and return if greater than toWin condition.
			if (counter >= toWin)
				return true;
		}
		else // There was a break in the matching - player tokens might not be next to each other.
			counter = 1;
	}
	
	// Not enough matches found.
	return false;
}

/* Checks to see if the column used by the player contains suitable matches.

Precondition:
	Player entered a row and column for a new player piece, which was
	successfully inserted.

	param int playedCol: Column that player inserted a new piece into.

Postcondition:
	If there are enough matching items in a column that are not BLANK_SPACEs,
	returns true. Else returns false.*/
bool Board::checkCol(int playedCol) {
	int counter = 1; // Counts number of matched items in current sequence.
	for (int i = 0; i < rows - 1; i++) {
		// If two consecutive items match and are not BLANK_SPACEs
		if (board[i][playedCol] == board[i + 1][playedCol] && board[i][playedCol] != BLANK_SPACE) {
			counter++; // Counter is added. If greater than number needed for victory, returns true.
			if (counter >= toWin)
				return true;
		}
		else // Match is not consistent. Return counter to starting point.
			counter = 1;
	}

	// Victory conditions not met.
	return false;
}

/* Checks both diagonals for matching player tokens. If enough are found, returns true.

Precondition:
	Player has entered row and column as part of turn.
	
	param int playedRow: Player's chosen row.
	param int playedCol: Player's chosen column.
	
Postcondition:
	Both left-to-right and right-to-left diagonals have been checked for matches. If
	enough tokens in a row have been found, returns true. Else returns false.*/
bool Board::checkDiagonal(int playedRow, int playedCol) {
	int counter = 1, currentRow = playedRow, currentCol = playedCol;
	
	// Find starting position for left-to-right check. Begins at top of board.
	while (currentRow != 0 && currentCol != 0) {
		currentRow--;
		currentCol--;
	}

	// Check if there is more than one item matching in a row (BLANK_SPACEs discounted).
	while (currentRow < rows - 1 && currentCol < cols - 1) {
		if (board[currentRow][currentCol] == board[currentRow + 1][currentCol + 1] && board[currentRow][currentCol] != BLANK_SPACE)
			counter++;
		else
			counter = 1; // Match not found. Reset counter.

		if (counter >= toWin)
			return true;

		currentRow++;
		currentCol++;
	}

	currentRow = playedRow;
	currentCol = playedCol;
	
	// Reset position to top of board for right-to-left check.
	while (currentRow != 0 && currentCol < cols) {
		currentRow--;
		currentCol++;
	}

	// Check again for matches on this diagonal.
	while (currentRow < rows - 1 && currentCol > 0) {
		if (board[currentRow][currentCol] == board[currentRow + 1][currentCol - 1] && board[currentRow][currentCol] != BLANK_SPACE)
			counter++;
		else
			counter = 1; // Match not found. Reset counter.

		if (counter >= toWin)
			return true;

		currentRow++;
		currentCol--;
	}
	
	// Neither diagonal contains matching tokens.
	return false;
}