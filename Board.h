#pragma once

class Board {
	// 0 - empty, 1 - player 1, 2 - player 2
	// last value is 1 if the column is full
	int filledCollsCount = 0;
	bool gameOver;
public:
	int moveCount = 0;
	char grid[8][7];
	// 1 for player 1, 2 for player 2
	int turn;
	Board();
	Board(int);
	void make_move(int);
	void print();
	bool isGameOverAfterMove(int);
	bool isFull();
	bool isFullCol(int);
	bool isGameOver();
	bool operator==(Board) const;
};
