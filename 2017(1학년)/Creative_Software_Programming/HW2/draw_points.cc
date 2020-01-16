#include<stdio.h>
#include<iostream>

using namespace std;

int arr[55][105];
int main() {
	int x, y;
	int max1 = 0, max2 = 0;
	while (1) {
		cin >> x;
		cin >> y;
		if (x < 0 || y < 0)
			break;
		arr[x][y] = 1;
		if (max1 < x)
			max1 = x;
		if (max2 < y)
			max2 = y;
		for (int i = 0; i <= max2; i++) {
			for (int j = 0; j <= max1; j++) {
				if (arr[j][i] == 0)
					cout << ".";
				if (arr[j][i] == 1)
					cout << "*";
			}
			cout << endl;
		}
	}
	return 0;
}
