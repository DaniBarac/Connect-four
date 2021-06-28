#include <iostream>
#include <unordered_map>
#include "Board.h"
#include "AI.h"

void game() {
	Board board;
	//std::unordered_map<Board, int, ai::BoardHasher> seed_boards;
	char x;
	int m;
	int winner;
	std::cout << "Enter 1 for a game against the computer or 2 for a 2-player game : ";
	std::cin >> x;

	if (x == '2')
	{
		do {
			board.print();
			std::cout << "Enter move: ";
			std::cin >> x;
			if (x == 'q' || x == 'Q')
				exit;
			while (board.isFullCol(x - '0')) {
				std::cout << "That column is full!" << std::endl;
				std::cin >> x;
			}
			board.make_move(x - '0');
		} while (!board.isGameOverAfterMove(x - '0'));
	}
	else if (x == '1')
	{
		do {
			board.print();
			std::cout << "Enter move: ";
			std::cin >> x;
			if (x == 'q' || x == 'Q')
				exit;
			while (board.isFullCol(x - '0')) {
				std::cout << "That column is full!" << std::endl;
				std::cin >> x;
			}
			board.make_move(x - '0');
			board.print();
			if (board.isGameOver()) {
				winner = 1;
				break;
			}
			winner = 2;

			std::cout << "Calculating move...";
			m = ai::findBestMove(board);
			board.make_move(m);

		} while (!board.isGameOver());
	}
	else
	{
		std::cout << "Invalid input.";
		exit;
	}
	board.print();

	std::cout << "THE WINNER IS " << winner;
}

int main()
{
	game();

	return 0;
}