#include <iostream>

using namespace std;
int memo[50];
int fibonacci(int n) {
	if (memo[n] != 0) {
		return memo[n];
	}
	else if (n <= 1) {
		if (n == 1)cout << 1 << ' ';
		return memo[n] = n;
	}
	else {
		memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
		cout << memo[n] << ' ';
		return memo[n];
	}

}

int main() {
	int n;
	cin >> n;
	fibonacci(n);
	cout << endl;
	return 0;
}

