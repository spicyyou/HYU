#include <iostream>

using namespace std;
int arr[100000];
void number_factorization(int number) {
	int j = 0;
	int cnt = 1;
	int a = 0;
	for (int i = 2; i <= number; i++) {
		while (1) {
			if (number%i == 0)
			{
				arr[j] = i;
				j++;
				number /= i;
				a = j;
			}
			else
				break;
		}
	}
	int num = 0;
	int i = 0;
	while (arr[i] != 0) {
		int cnt = 1;
		while (arr[i + 1] == arr[i]) {
			i++;
			cnt++;
		}
		cout << arr[i] << '^' << cnt;
		if (arr[i + 1] != '\0') {
			cout << " x ";
		}
		i++;
	}
	cout << endl;
}
int main(int argc, char** argv) {
	if (argc < 1)
		return -1;
	unsigned int Number;
	sscanf(argv[1], "%u", &Number);
	number_factorization(Number);
}