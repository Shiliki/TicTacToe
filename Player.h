#pragma once
#include <string>

using namespace std;

/* Player class
Author: Irene Zaugg, S02672231
Class: CSC 234-601
Instructor: Robert Gilanyi

Very simple player class for Tic-Tac-Toe game.
Stores a player's name and game piece. */
class Player
{
public:
	Player(string name, char gamePiece); // Constructor.

	string getName(); // Returns name.
	char getGamePiece(); // Returns game piece.

private:
	string name; // Player's entered name.
	char gamePiece; // Player's entered game piece.
};

