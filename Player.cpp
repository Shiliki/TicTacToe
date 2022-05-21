#include "Player.h"

using namespace std;

/* Constructor.

Precondition:
	Called by GameManager constructor.

	param string name: Player's entered name.
	param char gamePiece: Player's entered game piece.
	
Postcondition:
	Player name and chosen gamePiece are populated.*/
Player::Player(string name, char gamePiece) {
	this->name = name;
	this->gamePiece = gamePiece;
}

/* Returns name. */
string Player::getName() {
	return name;
}

/* Returns gamePiece. */
char Player::getGamePiece() {
	return gamePiece;
}