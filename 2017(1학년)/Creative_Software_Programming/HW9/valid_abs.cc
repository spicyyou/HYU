#include <iostream>
#include<string>
using namespace std;

int main() {
	int num;
	cin >> num;
	string input;
	int isOkay = 0;
	int sum = 0;
	for (int i = 0; i < num; i++) {
		cin >> input;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == '<') {
				sum += 1;
			}
			else if (input[i] == '>') {
				sum += -1;
			}
			if (sum < 0) {
				isOkay = 1;
				break;
			}
		}
		if (sum == 0) {
			cout << "YES" << endl;
		}
		else if (sum != 0 || isOkay == 1) {
			cout << "NO" << endl;
		}
		sum = 0;
	}
	return 0;
}