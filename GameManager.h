#pragma once
#include "Board.h"
#include "Player.h"

/* GameManager class
Author: Irene Zaugg
Class: CSC 234-601
Instructor: Robert Gilanyi

Runs main Tic-Tac-Toe game based on user input from main.
Uses Board class to determine winners and track players' turns.*/

typedef Player* PlayerPtr;
class GameManager
{
public:
	GameManager(int numPlayers, int numRows, int numCols, int toWin); // Constructor

	void runGame(); // Runs the game.

private:
	PlayerPtr* players; // Contains Player objects.
	Board* gameBoard; // Dynamically constructed Board object.
	int numPlayers; // User entered number of players.
	
	void setupPlayers(int numPlayers); // Sets players array.
	bool playTurn(Player& currentPlayer); // Handles individual turns.
	bool endGame(int playedRow, int playedCol, string currentPlayer); // Checks to see if game has ended.
};

