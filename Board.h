#pragma once
/* Board class for Tic Tac Toe

Author: Irene Zaugg, S02672231
Class: CSC 234-601
Instructor: Robert Gilanyi

Creates a dynamic array representing a board for a game of Tic-Tac-Toe.
API allows for construction of board of size 3-15.*/
using namespace std;

typedef char** CharPtrPtr;
class Board
{
public:
	Board(int rows, int cols, int toWin);

	void clearBoard(); // Creates "empty" board.
	void printBoard(); // Prints board.
	bool playTurn(int row, int col, char playerPiece); // Makes all necessary modifications to the board during player's turn.

	bool gameWon(int playedRow, int playedCol); // Check to see if the game has been won.
	bool tiedGame(); // Check to see if board is filled.
	int getRows(); // Returns number of rows.
	int getCols(); // Returns number of columns.

private:
	const char BLANK_SPACE = '.'; // Character representing an unused space on the board
	CharPtrPtr board; // 2-D dynamic array representing game board.
	int rows, cols, toWin, turnsPlayed; // Number rows, columns, and required matches for victory. turnsPlayed tracks if game is tied.

	bool checkRow(int playedRow); // Checks if the row last entered by player is victorious.
	bool checkCol(int col); // Checks if the column last entered by player is victorious.
	bool checkDiagonal(int row, int col); // Checks both diagonals from player entered position for victory.
};

