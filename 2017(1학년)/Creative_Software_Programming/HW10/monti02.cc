#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<cmath>
double Rounding(double x, int digit)
{
	return (floor((x)* pow(float(10), digit) + 0.5f) / pow(float(10), digit));
}

using namespace std;
//처음 고르는 문 랜덤
//선물 바꾸기
//rand()%M 하면 0~(M-1)까지의 수 생성
int main() {
	int select;
	double num;
	int num2;
	cin >> select >> num>>num2;
	double success = 0;
	for (int i = 0; i < num; i++) {
		int gift = (rand() % num2) + 1;
		int I_door = (rand() % num2) + 1;
		int m_door_temp;
		int m_door;
		while (1) {
			int m_door_temp = (rand() % 3) + 1;
			if (I_door != m_door_temp&&m_door_temp != gift) {
				m_door = m_door_temp;
				break;
			}
		}
		//기존선택 유지
		if (select == 1) {
			if (gift == I_door) {
				success++;
			}
		}
		//기존 선택 변경
		//while문써서 기존선택과 다른 랜덤값 선택
		else if (select == 2) {
			int new_door_select;
			while (1) {
				int new_I_door = (rand() % num2) + 1;
				if (I_door != new_I_door&&m_door != new_I_door) {
					new_door_select = new_I_door;
					break;
				}
			}
			if (gift == new_door_select) { success++; }
		}
		//랜덤
		else if (select == 3) {
			int select_temp = (rand() % 2) + 1;
			if (select_temp == 1) {
				if (gift == I_door) {
					success++;
				}
			}
			else if (select_temp == 2) {
				int new_door_select;
				while (1) {
					int new_I_door = (rand() % num2) + 1;
					if (I_door != new_I_door&&m_door != new_I_door) {
						new_door_select = new_I_door;
						break;
					}
				}
				if (gift == new_door_select) { success++; }
			}
		}
	}
	// 바꾸는거하깅
	double result;
	string result_str;
	int result_int;
	result = (success / num) * 100;
	result_int = (success / num) * 100;
	result_str = to_string(result_int);
	cout << Rounding(result, result_str.length() - 1) << "%" << "("
		<< success << "/" << num << ")" << endl;
	return 0;
}