#include<iostream>
#include<string>
using namespace std;
int number;

int Ok;
int main() {

	while (1) {
		string arr;
		getline(cin, arr);

		string *argv = new string[arr.length()];
		string token;
		size_t pos;
		int argc = 0;
		int token_count = 0;
		pos = arr.find(' ');
		token = arr.substr(0, pos);
		int token_count2 = token[0] - '0';
		if (isdigit(token[token.length() - 1])) number = atoi(token.c_str());
		else return NULL;
		arr.erase(0, pos + 1);
		while (true) {
			pos = arr.find(' ');
			token = arr.substr(0, pos);
			argv[argc++] = token;
			token_count++;
			if (pos >= arr.length()) break;
			else arr.erase(0, pos + 1);
		}
		if (token_count != token_count2) return NULL;
		int sum = 0;
		int isOkay = 0;
		for (int i = 0; i < argc; i++) {
			if (argv[i] == "J") sum += 10, Ok = 1;
			else if (argv[i] == "Q") sum += 10, Ok = 1;
			else if (argv[i] == "K") sum += 10, Ok = 1;
			else if (argv[i] == "A") {
				isOkay = 0; Ok = 1;
			}
			else
				sum += argv[i][0] - '0';
		}
		for (int i = 0; i < argc; i++) {
			if (argv[i] == "1" && argv[i + 1] == "0")
			{
				sum += 10;
				Ok = 1;
			}
		}
		//¼ýÀÚ
		//A
		if (isOkay == 0) {
			if (sum > 11) {
				sum += 1;
			}
			else if (sum == 11 && sum + 11 > 21)
				sum += 1;
			else
				sum += 11;
		}

		//
		if (sum == 21)
			cout << "BlackJack" << endl;
		else if (sum > 21)
			cout << "Exceed" << endl;
		else
			cout << sum << endl;
		sum = 0;

		arr = "";
		delete[]argv;
	}
}


