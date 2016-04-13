#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

long long const one = 1;

/******************************************************************************
	MASKS FOR PIECES
*/
#define WHITE_PAWN 1
#define WHITE_KNIGHT 2
#define WHITE_BISHOP 3
#define WHITE_ROOK 4
#define WHITE_QUEEN 5
#define WHITE_KING 6
#define BLACK_PAWN 9
#define BLACK_KNIGHT 10
#define BLACK_BISHOP 11
#define BLACK_ROOK 12
#define BLACK_QUEEN 13
#define BLACK_KING 14

#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6


/******************************************************************************
	BITMASKS
*/
long long H_MASK[64];
long long V_MASK[64];
long long D1_MASK[64];
long long D2_MASK[64];
long long N_MASK[64];
long long K_MASK[64];
long long WP_MASK_ALL[64];
long long WP_MASK_DIFF[64];
long long BP_MASK_ALL[64];
long long BP_MASK_DIFF[64];

void printMasks(long long mask) {
	char* output = (char*)malloc(sizeof(char) * 8 * 9);
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			output[(7 - row) * 9 + col] = (((mask >> (row * 8 + col)) & 1) == 1) ? '1' : '0';
		}
		output[row * 9 + 8] = '\n';
	}
	std::cout << std::string(output, 8 * 9) << '\n';
}

void initMasks() {
	int row, col;
	long long d1, d2, n, k, wpa, bpa, wpd, bpd;

	int n_moves[16]{ 1,2, 2,1, -1,2, 2,-1, 1,-2, -2,1, -1,-2, -2,-1 };
	int k_moves[16]{ 0,1, 1,1, 1,0, 1,-1, 0,-1, -1,-1, -1,0, -1,1 };

	for (int i = 0; i < 64; i++) {
		// find row and column from iterator
		row = i / 8;
		col = i % 8;

		// make row
		H_MASK[i] = 0xff << (row * 8);

		// make column
		V_MASK[i] = 0x101010101010101 << col;

		// make diagonal masks 1 and 2
		d1 = d2 = 0;
		for (int i = -7; i <= 7; i++) {
			if (0 <= row + i && row + i < 8) {
				if (0 <= col + i && col + i < 8) d1 |= one << ((row + i) * 8 + col + i);
				if (0 <= col - i && col - i < 8) d2 |= one << ((row + i) * 8 + col - i);
			}
		}
		D1_MASK[i] = d1;
		D2_MASK[i] = d2;

		// make knight masks
		n = 0;
		for (int i = 0; i < 16; i += 2) {
			int x = n_moves[i];
			int y = n_moves[i + 1];
			if (0 <= row + x && row + x < 8 && 0 <= col + y && col + y < 8)
				n |= one << ((row + x) * 8 + col + y);
		}
		N_MASK[i] = n;

		// make king masks
		k = 0;
		for (int i = 0; i < 16; i += 2) {
			int x = k_moves[i];
			int y = k_moves[i + 1];
			if (0 <= row + x && row + x < 8 && 0 <= col + y && col + y < 8)
				k |= one << ((row + x) * 8 + col + y);
		}
		K_MASK[i] = k;

		// make white and black pawn masks
		wpa = bpa = wpd = bpd = 0;
		if (row != 0 && row != 7) {
			if (row == 1)
				wpa |= one << ((row + 2) * 8 + col);
			wpa |= one << ((row + 1) * 8 + col);
			
			if (row == 6)
				bpa |= one << ((row - 2) * 8 + col);
			bpa |= one << ((row - 1) * 8 + col);

			if (col != 0) {
				wpd |= one << ((row + 1) * 8 + col - 1);
				bpd |= one << ((row - 1) * 8 + col - 1);
			}
			
			if (col != 7) {
				wpd |= one << ((row + 1) * 8 + col + 1);
				bpd |= one << ((row - 1) * 8 + col + 1);
			}
		}
		WP_MASK_ALL[i] = wpa;
		BP_MASK_ALL[i] = bpa;
		WP_MASK_DIFF[i] = wpd;
		BP_MASK_DIFF[i] = bpd;
	}
}


/******************************************************************************
	BITMASK MOVES
*/
std::unordered_map<long long, std::vector<short>> H_MOVES_F[64];
std::unordered_map<long long, std::vector<short>> H_MOVES_E[64];
std::unordered_map<long long, std::vector<short>> V_MOVES_F[64];
std::unordered_map<long long, std::vector<short>> V_MOVES_E[64];
std::unordered_map<long long, std::vector<short>> D1_MOVES_F[64];
std::unordered_map<long long, std::vector<short>> D1_MOVES_E[64];
std::unordered_map<long long, std::vector<short>> D2_MOVES_F[64];
std::unordered_map<long long, std::vector<short>> D2_MOVES_E[64];
std::unordered_map<long long, std::vector<short>> N_MOVES[64];
std::unordered_map<long long, std::vector<short>> K_MOVES[64];
std::unordered_map<long long, std::vector<short>> WP_MOVES_F[64];
std::unordered_map<long long, std::vector<short>> WP_MOVES_E[64];
std::unordered_map<long long, std::vector<short>> BP_MOVES_F[64];
std::unordered_map<long long, std::vector<short>> BP_MOVES_E[64];

short encodeMove(int start, int end) {
	return (short)(start << 6 | end);
}

std::vector<short> encodeBitmask(long long bitboard, int start) {
	std::vector<short> output = std::vector<short>();
	for (int index = 0; index < 64; index++) {
		if (((bitboard >> index) & 1) == 1) {
			output.push_back(encodeMove(start, index));
		}
	}
	return output;
}

void initMoves() {
	int row, col, pos, index;
	int combo, enemy, friendly;
	long long h_combo, h_friendly, h_enemy, v_combo, v_friendly, v_enemy;
	
	// horizontal and vertical move options given piece occupations
	// combo represents 8 bits comprising row and pieces occupying row
	for (combo = 0; combo < 256; combo++) {

		for (pos = 0; pos < 8; pos++) {
			enemy = friendly = 0;

			// generate enemy and friendly move options
			for (index = pos - 1; index >= 0; index--) {
				enemy |= (char)1 << index;
				if (((combo >> index) & 1) == 0)
					friendly |= (char)1 << index;
				else break;
			}

			for (index = pos + 1; index < 8; index++) {
				enemy |= (char)1 << index;
				if (((combo >> index) & 1) == 0)
					friendly |= (char)1 << index;
				else break;
			}

			// iterate through possible rows this could apply to with pos acting as columns
			for (row = 0; row < 8; row++) {
				h_combo = (long long)(combo << (row * 8));
				h_friendly = (long long)(friendly << (row * 8));
				h_enemy = (long long)(enemy << (row * 8));
				H_MOVES_F[row * 8 + pos].insert(
					std::pair<long long, std::vector<short>>(h_combo, encodeBitmask(h_friendly, row * 8 + pos)));
				H_MOVES_E[row * 8 + pos].insert(
					std::pair<long long, std::vector<short>>(h_combo, encodeBitmask(h_enemy, row * 8 + pos)));
			}

			// reshape horizontal bitmask to a vertical bitmask
			v_combo = v_friendly = v_enemy = 0;
			for (index = 0; index < 8; index++) {
				v_combo |= (long long)((h_combo >> index) & 1) << (index * 8);
				v_friendly |= (long long)((h_friendly >> index) & 1) << (index * 8);
				v_enemy |= (long long)((h_enemy >> index) & 1) << (index * 8);
			}

			// iterate through possibles columns this could apply to with pos acting as row
			for (col = 0; col < 8; col++) {
				V_MOVES_F[pos * 8 + col].insert(
					std::pair<long long, std::vector<short>>(v_combo, encodeBitmask(v_friendly, pos * 8 + col)));
				V_MOVES_E[pos * 8 + col].insert(
					std::pair<long long, std::vector<short>>(v_combo, encodeBitmask(v_enemy, pos * 8 + col)));
				// shift everything over 1 place
				v_combo <<= 1;
				v_friendly <<= 1;
				v_enemy <<= 1;
			}
		}
	}
}