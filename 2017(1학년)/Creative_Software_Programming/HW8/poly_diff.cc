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
		//getline(cin, input); //getline�� �ι� �ȹ޾����� ������..
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
				token = input.substr(0, pos_plus);//��
			}//��
			int square_ex = 0;
			for (int i = 0; i < token.length(); i++) {
				size_t pos = token.find("x");//x���ִ� index
				size_t pos_sq = token.find("^");//^�� �ִ� �ε���
				if (pos == string::npos) {
					//x�� ���� �� , ����϶�
					sum += 0;
				}
				else {
					string token_if = token.substr(0, pos);//x�� ���
					//-�� ���ڰ� ������
					//x������ �߶�
					if (token_if[0] == '-') {
						if (token_if[0] == '-'&&token_if[1] == 'x')//����� -1�϶�
						{
						}
						//����� -����϶�
						string num_gae = token_if.substr(1, pos);
						int num_gaesu = atoi(num_gae.c_str());//���ڰ��

						if (pos_sq != string::npos) {
							string num2 = token.erase(0, pos_sq + 1);
							int num2_int = atoi(num2.c_str());//������
							sum += (-1)*num_gaesu*function(num2_int, input_num);
							//������ ���� ��
						}
						else {
							sum += num_gaesu*(-1);
							//������ ���� ��
						}
					}
					//����� ���� ��
					else if (token_if.length() == 0)
					{
						if (pos_sq != string::npos) {
							//������ ������
							string num2 = token.erase(0, pos_sq + 1);
							int num2_int = atoi(num2.c_str());
							sum += function(num2_int, input_num);
						}
						else {
							sum += 1;//x
						}
					}
					else {//����� �׳� �����϶�
						string num_gae = token_if.substr(0, pos);
						int num_gaesu = atoi(num_gae.c_str());
						if (pos_sq != string::npos) {
							//�������� ������
							string num2 = token.erase(0, pos_sq + 1);
							int num2_int = atoi(num2.c_str());//������
							sum += num_gaesu*function(num2_int, input_num);
						}
						else {
							//�������� ���� �� ���*x
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