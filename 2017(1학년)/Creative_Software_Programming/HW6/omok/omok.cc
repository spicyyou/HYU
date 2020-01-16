#include "omok.h"
#include <iostream>
#include<vector>
using namespace std;
int Omok::Put(int x, int y)
{
	x_ = x;
	y_ = y;
	omok_pan.resize(height_);
	for (int i = 0; i < width_; i++) {
		omok_pan[i].resize(width_);
	}
	if (omok_pan[y][x] == 1 || omok_pan[y][x] == 2
		|| x < 0 || y < 0 || x>18 || y>18) {
		cout << "Can not be placed there" << endl;
		return NOBODY;
	}
	turn_++;
	cout << turn_ << endl;
	if (turn_ % 2 == 1)
	{
		omok_pan[y][x] = 1;

	}
	else if (turn_ % 2 == 0) {
		omok_pan[y][x] = 2;
	}
	return turn_;
}

void Omok::IsOmok(int winner) const
{
	if (winner / 2 == 0) {	cout << "Winner: White player" << endl;}
	else { cout << "Winner: Black player" << endl; }
}

int Omok::check_omok()
{
	int cnt[4] = { 1, 1, 1, 1 };
	int col, row, i;
	int move_col[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int move_row[8] = { 1, 0, -1, 1, -1, 0, 1, -1 };
	int recent_turn = omok_pan[y_][x_];
	for (i = 0; i < 8; i++) {
		col = x_;
		row = y_;
		while (true) {
			col += move_col[i];
			row += move_row[i];
			if (col < 0 || row < 0 || col > 18 || row > 18) {
				break;
			}
			else if (omok_pan[row][col] == recent_turn) {
				cnt[i % 4]++;
			}
			else {
				break;
			}
		}
	}
	for (i = 0; i < 4; i++) {
		if (cnt[i] == 5) {
			if (recent_turn == 1) {
				return 1;
			}
			else {
				return 2;
			}
		}
	}
	return 0;
}

ostream& operator<<(std::ostream& os, const Omok& omok_) {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			switch (omok_.omok_pan[i][j]) {
			case 0: {
				os << ". ";
				break;
			}
			case 1: {
				os << "o ";
				break;
			}
			case 2: {
				os << "x ";
				break;
			}
			}
		}
		os << endl;
	}
	//omok_.IsOmok(omok_.Turn());
	return os;
}