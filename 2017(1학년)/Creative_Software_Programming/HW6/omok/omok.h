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
	// ������ (x,y)�� ���� ���� (x,y = 0~18). ù ���� �׻� �浹�� ����.
	// �� �ٱ��ʿ� ���ų� �̹� ���� �ڸ��� ���� ��� NOBODY�� ����.
	// �������� ��� ���� ���� turn_�� �Ͽ� �°� �����ϰ� ����.
	// ���� ���� �ƴ�, ���� ���� ���� (ó�� ȣ��� Put�� BLACK�� �����ϰ� ��)
	int Put(int x, int y);
	// winner�� �浹�� �̱� ��� BLACK����, �鵹�� �̱� ��� WHITE��, �ºΰ� ���� ���� ��� NOBODY�� ����
	void IsOmok(int winner) const;
	int Turn() const { return turn_; }
	int check_omok();
	int x_, y_;
	vector < vector<int> >omok_pan;
	// �ʿ� �� �Լ��� �߰� �����ϳ�, width_, height_�� get���� �ʰ� class������ ó�� �� ��±��� �ϴ� ���踦 ����
private:
	int width_, height_;
	int turn_; // �������� �÷��� �� ���� ����
			   /* ��� ������ �߰�. */
};
ostream& operator<<(std::ostream& os, const Omok& omok);
#endif // !omok