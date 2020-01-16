#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

char result[1000000];
string RadixNotation(int num, int n) {
	int cnt = 0;
	int i = 0;
	while (1) {
		cnt = num%n;
		if (cnt<10) {
			result[i] = 48 + cnt;
		}
		else {
			result[i] = 97 + (cnt - 10);
		}
		num /= n;
		i++;
		if (num == 0)
			break;
	}
	string ans;
	for (int j = i - 1; j >= 0; j--) {
		ans += result[j];
	}
	return ans;
}

int main(int argc, char**argv) {
	if (argc < 2) return -1;
	unsigned int radix;
	sscanf(argv[1], "%u", &radix);
	if (radix < 2 || radix >36) return -1;
	for (int i = 2; i < argc; ++i) {
		unsigned int number;
		sscanf(argv[i], "%u", &number);
		cout << RadixNotation(number, radix) << endl;
	}
	return 0;

}
