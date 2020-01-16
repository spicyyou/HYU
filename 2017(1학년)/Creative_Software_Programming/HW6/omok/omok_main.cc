#include <iostream>
#include "omok.h"
using namespace std;

int main() {
	Omok omok_main;
	while (1) {
		int num = 0;
		int a, b;
		cin >> a >> b;
		omok_main.Put(a, b);
		num = omok_main.Turn();
		if(omok_main.check_omok()==1&&omok_main.Turn()%2==1){
			cout << omok_main;
			omok_main.IsOmok(num);
			break;
		}//black win
		else if(omok_main.check_omok() == 2&& omok_main.Turn() %2==0){
			cout << omok_main;
			break;
		}
	}
}