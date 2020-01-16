#ifndef minesweeper_h
#define minesweeper_h

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Minesweeper
{
public:
	////////// 4-3-1 (7 score) //////////
	Minesweeper();
	~Minesweeper();

	// return false when input is incorrect
	bool setMap(size_t _width, size_t _height, vector<string>& _map);
	bool toggleMine(int _x, int _y);

	// return map width, height, and char
	size_t width() const;
	size_t height() const;
	char get(int _x, int _y) const; // return ' ' if input is illegal

									////////// 4-3-2 (3 score) //////////
	bool setPlay(); // return false when map is not set
	bool touchMap(int _x, int _y); // return true when dead
	int touchCount() const;
	/*char** map_alloc() {
		char **map = new char*[height_];
		for (int i = 0; i < width_; i++) {
			map[i] = new char[width_];
		}
		return map;
	};
	void map_delete(char **map) {
		delete[]map;
	}*/
private:
	vector<string> map_str;//메인에서 받은 .과 *달린 맵
	vector<vector<char> > map_alloc;//숫자 달린 맵,*과 숫자
	size_t height_;
	size_t width_;
	vector<vector<char> > playmap;//_가 있는맵
	int touch_cnt;
	char **map;
	// add private member variables and functions if it is needed.
};

#endif /* minesweeper_h */
