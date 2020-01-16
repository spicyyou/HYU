#include <iostream>
#include<math.h>
#include<stdlib.h>
#include<string>

using namespace std;

int function(int square, int x_num) {
	int square_a = square - 1;
	int result;
	result = square*pow(x_num, square_a);
	return result;
}

int main() {
	while (1) {
		string input;
		cin >> input;
		//getline(cin, input); //getline이 두번 안받아지는 이유좀..
		if (input.compare("quit") == 0) { break; }
		int input_num;
		cin >> input_num;
		int sum = 0;
		int isOkay = 0;
		while (1) {
			size_t pos_plus = input.find("+");
			string token;
			if (pos_plus == string::npos) {
				token = input;
				isOkay = 1;
			}
			else {
				token = input.substr(0, pos_plus);//항
			}//항
			int square_ex = 0;
			for (int i = 0; i < token.length(); i++) {
				size_t pos = token.find("x");//x가있는 index
				size_t pos_sq = token.find("^");//^가 있는 인덱스
				if (pos == string::npos) {
					//x가 없을 때 , 상수일때
					sum += 0;
				}
				else {
					string token_if = token.substr(0, pos);//x의 계수
					//-와 숫자가 있을대
					//x전까지 잘라
					if (token_if[0] == '-') {
						if (token_if[0] == '-'&&token_if[1] == 'x')//계수가 -1일때
						{
						}
						//계수가 -어찌구일때
						string num_gae = token_if.substr(1, pos);
						int num_gaesu = atoi(num_gae.c_str());//숫자계수

						if (pos_sq != string::npos) {
							string num2 = token.erase(0, pos_sq + 1);
							int num2_int = atoi(num2.c_str());//제곱수
							sum += (-1)*num_gaesu*function(num2_int, input_num);
							//제곱이 있을 때
						}
						else {
							sum += num_gaesu*(-1);
							//제곱이 없을 때
						}
					}
					//계수가 없을 때
					else if (token_if.length() == 0)
					{
						if (pos_sq != string::npos) {
							//제곱이 있을때
							string num2 = token.erase(0, pos_sq + 1);
							int num2_int = atoi(num2.c_str());
							sum += function(num2_int, input_num);
						}
						else {
							sum += 1;//x
						}
					}
					else {//계수가 그냥 숫자일때
						string num_gae = token_if.substr(0, pos);
						int num_gaesu = atoi(num_gae.c_str());
						if (pos_sq != string::npos) {
							//제곱수가 있을때
							string num2 = token.erase(0, pos_sq + 1);
							int num2_int = atoi(num2.c_str());//제곱수
							sum += num_gaesu*function(num2_int, input_num);
						}
						else {
							//제곱수가 없을 때 계수*x
							sum += num_gaesu;
						}
					}
				}
			}
			input.erase(0, pos_plus + 1);
			if (isOkay == 1) break;
		}
		cout << sum << endl;
	}
	return 0;
}