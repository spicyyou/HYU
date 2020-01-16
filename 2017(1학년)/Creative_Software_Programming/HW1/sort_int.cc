#include <iostream>

using namespace std;
void sort(int N, int* ary) {
	int temp = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N - 1; j++) {
			if (ary[i] > ary[j + 1]) {
				temp = ary[i];
				ary[i] = ary[j + 1];
				ary[j + 1] = temp;
			}
		}
	}


}

int main() {
	int n;
	cin >> n;
	if (n <= 0)
		return 0;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(n, arr);
	for (int i = 0; i < n; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;

	return 0;

}