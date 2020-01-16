#ifndef omok
#define omok
#include<iostream>
#include<vector>
using namespace std;
#define BLACK -1
#define NOBODY 0
#define WHITE 1
#define GROUND_SIZE 19
class Omok {
public:
	Omok() : width_(GROUND_SIZE), height_(GROUND_SIZE), turn_(NOBODY) {
		vector < vector<int> >omok_pan;
	}
	// 번갈아 (x,y)에 돌을 놓음 (x,y = 0~18). 첫 수는 항상 흑돌로 가정.
	// 판 바깥쪽에 놓거나 이미 놓인 자리에 놓을 경우 NOBODY를 리턴.
	// 정상적인 경우 돌을 놓고 turn_을 턴에 맞게 세팅하고 리턴.
	// 다음 턴이 아닌, 현재 턴을 리턴 (처음 호출된 Put은 BLACK을 리턴하게 됨)
	int Put(int x, int y);
	// winner는 흑돌이 이긴 경우 BLACK으로, 백돌이 이긴 경우 WHITE로, 승부가 나지 않은 경우 NOBODY로 세팅
	void IsOmok(int winner) const;
	int Turn() const { return turn_; }
	int check_omok();
	int x_, y_;
	vector < vector<int> >omok_pan;
	// 필요 시 함수를 추가 가능하나, width_, height_를 get하지 않고 class내에서 처리 후 출력까지 하는 설계를 권장
private:
	int width_, height_;
	int turn_; // 마지막에 플레이 한 턴을 저장
			   /* 멤버 변수를 추가. */
};
ostream& operator<<(std::ostream& os, const Omok& omok);
#endif // !omok