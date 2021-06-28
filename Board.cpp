#include "Board.h"
#include <iostream>


Board::Board() {
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 7; y++)
			grid[x][y] = 0;
	turn = 1;
	filledCollsCount = 0;
	gameOver = false;
	moveCount = 0;
}

void Board::make_move(int x) {
	if (!grid[x][6]) {
		int k = 0;
		while (grid[x][k] != 0)
			k++;
		grid[x][k] = turn;
		turn = turn % 2 + 1;
		if (k == 5) {
			grid[x][6] = 1;
			filledCollsCount++;
		}
		moveCount++;
	}
	isGameOverAfterMove(x);
}

void Board::print() {
	system("cls");
	for (int y = 5; y >= 0; y--){
		std::cout << '|';
		for (int x = 0; x < 8; x++) {
			if (grid[x][y] == 0)
				std::cout << ' ';

			// Weird stuff for colored output
			else {
				if (grid[x][y] == 1)
					system("echo|set /p=\u001B[91mx");
				else
					system("echo|set /p=\u001B[93mo");
				system("\necho|set /p=\u001B[97m");
			}
			std::cout << '|';
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------" << std::endl;
	std::cout << "|0|1|2|3|4|5|6|7|" << std::endl;
}

static bool isGGAfterMove(int x, char grid[8][7]) {
	if (x < 0 || x >= 8)
		return false;
	int y = 0;
	while (grid[x][y] != 0 && y < 6)
		y++;
	y--;

	// horizontal
	int i = x - 1;
	int count = 1;
	while (i >= 0 && grid[x][y] == grid[i][y] && count < 4) {
		count++;
		i--;
	}
	if (count < 4) {
		i = x + 1;
		while (i < 8 && grid[x][y] == grid[i][y] && count < 4) {
			count++;
			i++;
		}
		if (count == 4)
			return true;
	}
	else return true;

	// vertical
	i = y - 1;
	count = 1;
	while (i >= 0 && grid[x][y] == grid[x][i] && count < 4) {
		count++;
		i--;
	}
	if (count < 4) {
		i = y + 1;
		while (i < 6 && grid[x][y] == grid[x][i] && count < 4) {
			count++;
			i++;
		}
		if (count == 4)
			return true;
	}
	else return true;

	// slanted up
	i = x - 1;
	int j = y - 1;
	count = 1;
	while (i >= 0 && j >= 0 && grid[x][y] == grid[i][j] && count < 4) {
		count++;
		i--;
		j--;
	}
	if (count < 4) {
		i = x + 1;
		j = y + 1;
		while (i < 8 && j < 6 && grid[x][y] == grid[i][j] && count < 4) {
			count++;
			i++;
			j++;
		}
		if (count == 4)
			return true;
	}
	else return true;

	// slanted down
	i = x - 1;
	j = y + 1;
	count = 1;
	while (i >= 0 && j < 6 && grid[x][y] == grid[i][j] && count < 4) {
		count++;
		i--;
		j++;
	}
	if (count < 4) {
		i = x + 1;
		j = y - 1;
		while (i < 8 && j >= 0 && grid[x][y] == grid[i][j] && count < 4) {
			count++;
			i++;
			j--;
		}
		if (count == 4)
			return true;
	}
	else return true;

	return false;
}

bool Board::isGameOverAfterMove(int x) {
	gameOver = isGGAfterMove(x, grid);
	return gameOver;
}

bool Board::isFull() {
	return filledCollsCount == 8;
}

bool Board::isGameOver() {
	return gameOver;
}

Board::Board(int x) {
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 7; y++)
			grid[x][y] = 0;
	turn = 1;
	filledCollsCount = 0;
	gameOver = false;
	grid[0][0] = grid[1][0] = 1;
	grid[7][0] = grid[7][1] = 2;
}

bool Board::isFullCol(int x) {
	return grid[x][6];
}

bool Board::operator==(Board b) const {
	if (this->moveCount != b.moveCount)
		return false;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 7; y++) {
			if (this->grid[x][y] != b.grid[x][y]) {
				return false;
			}
		}
	}
	return true;
}