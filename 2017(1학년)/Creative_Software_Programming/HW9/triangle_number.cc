
#include<iostream>

int arr[46] = {0,1,3,6,10,15,21 };
using namespace std;
int main() {
	int arr2[1000] = { 0, };
	int isOkay = 0;
	int num;
	int input;
	cin >> num;
	//test case
	for (int i = 0; i < num; i++) {
		cin >> input;
		for (int j = 7; j < 46; j++) {
			arr[j] = (j*(j + 1)) / 2;
		}
		for(int j = 1; j < 46; j++) {
			for (int k = 1; k < 46; k++) {
				for (int l = 1; l < 46; l++) {
					if (arr[j] + arr[k] + arr[l] == input) {
						isOkay = 1;
						break;
					}
				}
				if (isOkay == 1) break;
			}
			if (isOkay == 1) break;
		}

		if (isOkay == 1) {
			cout << "1" << endl;
		}
		else {
			cout << "0" << endl;
		}
		isOkay = 0;
	}
	return 0;
}