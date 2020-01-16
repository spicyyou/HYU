#include <iostream>

using namespace std;
void magic(int N, int **ary) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ary[i][j] = 0;
		}
	}
	ary[N - 1][N / 2] = 1;
	int x, y;
	y = N / 2;
	x = N - 1;
	for (int i = 2; i <= N*N; i++) {
		if (x + 1 == N&&y + 1 == N) {
			x--;
		}
		else if (x + 1 == N&&y < N) {
			x = 0;
			y++;
		}
		else if (y + 1 == N&&x < N) {
			y = 0;
			x++;
		}
		else {
			if (ary[x + 1][y + 1] == 0) {
				x = x + 1;
				y = y + 1;
			}
			else
				x--;
		}
		ary[x][y] = i;
	}
}


int main() {
	int n;
	cin >> n;
	if ((n % 2) != 1 || n < 1)
		return 0;
	int** arr = new int*[n];
	for (int i = 0; i < n; ++i)
		arr[i] = new int[n];
	magic(n, arr);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}