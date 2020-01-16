#include "minesweeper.h"
#include <iostream>
#include<vector>
using namespace std;

int dx[8] = { 1,1,1,0,0,-1,-1,-1 };
int dy[8] = { 1,0,-1,1,-1,0,1,-1 };

Minesweeper::Minesweeper()
{
	vector<string> map_str;
	width_ = 0;
	height_ = 0;
	char **map;
	vector<string>playmap;
	touch_cnt=0;
}

Minesweeper::~Minesweeper()
{
}

bool Minesweeper::setMap(size_t _width, size_t _height, vector<string>& _map)
{
	map_alloc.clear();
	map_str.clear();
	width_ = _width;
	height_ = _height;
	for (vector<string> ::iterator it = _map.begin(); it != _map.end(); it++) {
		map_str.push_back(*it);
	}
	map_alloc.resize(height_);
	for (int i = 0; i < map_alloc.size(); i++) {
		map_alloc[i].resize(width_);
	}
	int map_count=0;
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			for (int k = 0; k < 8; k++) {
				if (i + dx[k] >= 0 && j + dy[k] >= 0 && i + dx[k] < _height&&j + dy[k] < _width) {
					if (map_str[i + dx[k]][j + dy[k]] == '*')
					{
						map_count++;
					}
				}
			}
			map_alloc[i][j] = map_count + '0';
			if (map_str[i][j] == '*')
				map_alloc[i][j] = '*';
			map_count = 0;
		}
	}

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			cout << map_alloc[i][j];
		}
		cout << endl;
	}
	_map.clear();

	return true;
}

bool Minesweeper::toggleMine(int _x, int _y)
{
	if (map_str[_y][_x] == '*') {
		map_str[_y][_x] = '.';

		map_alloc.resize(height_);
		for (int i = 0; i < map_alloc.size(); i++) {
			map_alloc[i].resize(width_);
		}
		int map_count = 0;
		for (int i = 0; i < height_; i++) {
			for (int j = 0; j < width_; j++) {
				for (int k = 0; k < 8; k++) {
					if (i + dx[k] >= 0 && j + dy[k] >= 0 && i + dx[k] < height_&&j + dy[k] < width_) {
						if (map_str[i + dx[k]][j + dy[k]] == '*')
						{
							map_count++;
						}
					}
				}
				map_alloc[i][j] = map_count + '0';
				if (map_str[i][j] == '*')
					map_alloc[i][j] = '*';
				map_count = 0;
			}
		}

		for (int i = 0; i < height_; i++) {
			for (int j = 0; j < width_; j++) {
				cout << map_alloc[i][j];
			}
			cout << endl;
		}
	}
	else if (map_str[_y][_x] == '.') {
		map_str[_y][_x] = '*';
		map_alloc.resize(height_);
		for (int i = 0; i < playmap.size(); i++) {
			map_alloc[i].resize(width_);
		}
		int map_count = 0;
		for (int i = 0; i < height_; i++) {
			for (int j = 0; j < width_; j++) {
				for (int k = 0; k < 8; k++) {
					if (i + dx[k] >= 0 && j + dy[k] >= 0 && i + dx[k] < height_&&j + dy[k] < width_) {
						if (map_str[i + dx[k]][j + dy[k]] == '*')
						{
							map_count++;
						}
					}
				}
				map_alloc[i][j] = map_count + '0';
				if (map_str[i][j] == '*')
					map_alloc[i][j] = '*';
				map_count = 0;
			}
		}

		for (int i = 0; i < height_; i++) {
			for (int j = 0; j < width_; j++) {
				cout << map_alloc[i][j];
			}
			cout << endl;
		}
	}
	return true;
}

size_t Minesweeper::width() const
{
	return width_;
}

size_t Minesweeper::height() const
{
	return height_;
}

char Minesweeper::get(int _x, int _y) const
{
	return 1;
}

bool Minesweeper::setPlay()
{
	touch_cnt = 0;
	playmap.resize(height_);
	for (int i = 0; i < playmap.size(); i++) {
		playmap[i].resize(width_);
	}
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			playmap[i][j]='_';
		}
	}
	for (int i = 0; i <  height_; i++) {
		for (int j = 0; j <width_; j++) {
			cout<< playmap[i][j];
		}
		cout << endl;
	}
	return true;
}
bool Minesweeper::touchMap(int _x2, int _y2)
{
	playmap[_y2][_x2] = map_alloc[_y2][_x2];
	touch_cnt++;
	if (map_alloc[_y2][_x2] == '*') {
		return true;
	}
	else {
		for (int i = 0; i < height_; i++) {
			for (int j = 0; j < width_; j++) {
				cout << playmap[i][j];
			}
			cout << endl;
		}
	return false;
	}
	
}

int Minesweeper::touchCount() const
{
	return touch_cnt;
}
