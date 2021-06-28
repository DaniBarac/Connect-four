#pragma once
#include "Board.h"
#include "hash_map.h"
#include <unordered_map>

namespace ai {
	class BoardHasher
	{
	public:
		//using boost::hash_combine
		template <class T>
		static inline void hash_combine(std::size_t& seed, T const& v)
		{
			seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		size_t operator()(Board const& in) const
		{
			size_t seed = 0;
			for (int x = 0; x < 8; x++)
				for (int y = 0; y < 7; y++)
					//Combine the hash of the current vector with the hashes of the previous ones
					hash_combine(seed, in.grid[x][y]);
			hash_combine(seed, in.turn);
			return seed;
		}
	};
	//static std::unordered_map<Board, int, BoardHasher> seen_boards;
	int findBestMove(Board, int = 10);
}