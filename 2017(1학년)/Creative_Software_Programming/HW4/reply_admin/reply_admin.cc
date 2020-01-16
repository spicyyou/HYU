#include "reply_admin.h"
#include<algorithm>

ReplyAdmin::ReplyAdmin()
{
	list<string> chats;
	addChat("Hello, Reply Administrator!");
	addChat("I will be a good programmer.");
	addChat("This class is awesome.");
	addChat("Professor Lim is wise.");
	addChat("Two TAs are kind and helpful.");
	addChat("I think male TA looks cool.");
}

ReplyAdmin::~ReplyAdmin()
{
}

bool ReplyAdmin::addChat(string _chat)
{
	chats.push_back(_chat);
	return true;
}
bool ReplyAdmin::removeChat(int _index)
{
	size_t num = chats.size();

	if (_index > num) return false;

	list<string>::iterator it = chats.begin();

	advance(it, _index);

	chats.erase(it);

	return true;
}

bool ReplyAdmin::removeChat(list<int> _indices)//,,,indices ==숫자 count 숫자갯수 3,4,5 면 3개 들어가있음,, numbers는 indices 배열
{
	_indices.sort();
	size_t num = _indices.size();
	while (num--) {
		removeChat(_indices.back());
		_indices.pop_back();
	}
	return true;
}

bool ReplyAdmin::removeChat(int _start, int _end)
{
	int isOkay = 1;
	for (int i = _end; i >= _start; i--) {
		if (i < chats.size() && _start < _end&&_start < chats.size()) {
			removeChat(i);
			isOkay = 0;
		}
	}
	if (isOkay == 0)
		return true;
	else return false;
}
void ReplyAdmin::printChat()
{
	size_t num = chats.size();
	for (int i = 0; i < num; i++) {
		cout << i << " " << chats.front() << endl;
		chats.push_back(chats.front());
		chats.pop_front();
	}
}