#include "reply_admin.h"
#include<algorithm>

ReplyAdmin::ReplyAdmin()
{
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
	if (chats.size() != NUM_OF_CHAT) {
		chats.push_back(_chat);
		return true;
	}
}
bool ReplyAdmin::removeChat(int _index)
{
	list<string>::iterator it;
	for (int i = 0; i <= _index; it++);
	chats.erase(it);
	return true;
}

bool ReplyAdmin::removeChat(int * _indices, int _count)//,,,indices ==숫자 count 숫자갯수 3,4,5 면 3개 들어가있음,, numbers는 indices 배열
{
	int isOkay;
	sort(_indices, _indices + _count);
	for (int i = _count-1; i >= 0; i--) {
		if (_indices[i] <chats.size()) {
			removeChat(_indices[i]);
			isOkay = 0;
		}
	}
	if (isOkay == 0)
		return true;
}

bool ReplyAdmin::removeChat(int _start, int _end)
{
	int isOkay;
	for (int i = _end; i >= _start; i--) {
		if (i < chats.size() && _start < _end&&_start < chats.size()) {
			removeChat(i);
			isOkay = 0;
		}
	}
	if (isOkay == 0)
		return true;
}
void ReplyAdmin::printChat()
{
	list<int>::iterator it2;
	for (it2=chats.begin; it2 != chats.end; it2++) {
		cout << " " << *it2 << endl;
	}
}