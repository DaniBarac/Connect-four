#include "Board.h"
#include "AI.h"
//#include "hash_map.h"
#include <unordered_map>
#include <iostream>

using namespace ai;

int min(int a, int b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

// Player 1 minimizes, player 2 maximizes
int minimax(Board board, std::unordered_map<Board, int, BoardHasher>& seen_boards, int depth, int alpha = -1000000, int beta = 1000000) {

	if (board.isGameOver())
		return -((float)board.turn - 1.5f) * 100000000;
	else if (board.isFull())
		return 0;
	else if (depth == 0)
		return 0;

	if (board.turn == 1)
	{
		int bestVal = 1000000;
		Board daughter;
		for (int i = 0; i < 8; i++) {
			if (!board.isFullCol(i)) {
				daughter = board;
				daughter.make_move(i);
				int val;
				auto it = seen_boards.find(daughter);
				if (it != seen_boards.end())
				{
					val = it->second;
				}
				else
				{
					val = minimax(daughter, seen_boards, depth - 1, alpha, beta);
					seen_boards.insert({ daughter, val });
				}
				bestVal = min(bestVal, val);
				beta = min(bestVal, beta);
				if (beta <= alpha)
					break;
			}
		}
		return bestVal;
	}
	else
	{
		int bestVal = -1000000;
		Board daughter;
		for (int i = 0; i < 8; i++) {
			if (!board.isFullCol(i)) {
				daughter = board;
				daughter.make_move(i);
				int val;
				auto it = seen_boards.find(daughter);
				if (it == seen_boards.end()) {
					val = minimax(daughter, seen_boards, depth - 1, alpha, beta);
					seen_boards.insert({ daughter, val });
				}
				else
				{
					val = it->second;
				}
				bestVal = max(bestVal, val);
				alpha = max(bestVal, alpha);
				if (beta <= alpha)
					break;
			}
		}
		return bestVal;
	}
}

int ai::findBestMove(Board board, int depth) {
	int bestVal = -((float)board.turn - 1.5f) * 1000000;
	int bestMove = 0;
	Board daughter; 
	std::unordered_map<Board, int, BoardHasher> seen_boards;
	std::cout << std::endl << "Progress: " << '\r';
	for (int i = 0; i < 8; i++) {
		if (!board.isFullCol(i)) {
			daughter = board;
			daughter.make_move(i);
			int val = minimax(daughter, seen_boards, depth);
			std::cout << "Progress: ";
			for (int j = 0; j <= i; j++)
				std::cout << '\u2580';
			std::cout << '\r';
			if (board.turn == 1)
			{
				if (val <= bestVal)
				{
					bestVal = val;
					bestMove = i;
				}
			}
			else
			{
				if (val >= bestVal)
				{
					bestVal = val;
					bestMove = i;
				}
			}
		}
	}
	return bestMove;
}
