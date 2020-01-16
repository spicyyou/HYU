#include <iostream>
#include <string>
#include <stdio.h>
#include<algorithm>
using namespace std;

const int NUM_OF_CHAT = 200;
int getChatCount(string *_chatList) {
	int i;
	for (i = 0; i < NUM_OF_CHAT; i++) {
		string s = _chatList[i];
		if (s.empty() == true) break;
	}
	return i;
}

void printChat(string *_chatList) {
	int count = getChatCount(_chatList);
	for (int i = 0; i < count; ++i) {
		cout << i << " " << _chatList[i] << endl;
	}
}
bool addChat(string *_chatList, string _chat) {

	if (getChatCount(_chatList) != 200) {
		_chatList[getChatCount(_chatList)] = _chat;
		return true;
	}
}
;//returns true when adding chat is succeeded
bool removeChat(string *_chatList, int _index) {
	for (int i = _index; i < getChatCount(_chatList); i++)
	{
		_chatList[i] = _chatList[i + 1];
	}
	_chatList[getChatCount(_chatList)] = "";
	return true;
}
;//returns true when removing chat is succeeded
int cnt[300];
int b;
int main(void) {
	string* chats = new string[NUM_OF_CHAT];
	addChat(chats, "Hello, Reply Administrator!");
	addChat(chats, "I will be a good programmer.");
	addChat(chats, "This class is awesome.");
	addChat(chats, "Professor Lim is wise.");
	addChat(chats, "Two TAs are kind and helpful.");
	addChat(chats, "I think TAs look cool.");
	int m, a;
	int k = 0;
	int correct = 0;
	int stick = 0;
	while (true) {
		string command;
		getline(cin, command);
		//quit

		if (command.compare("#quit") == 0)/* #quit */break;

		//remove

		else if (command[0] == '#'&&command[1] == 'r') {

			// nothing
			for (int i = 7; i < command.length(); i++) {
				if (command[i] == ',' || command[i] == '-') {
					correct = 1;
					break;
				}
			}

			if (correct != 1) {
				int removeline = 0;
				for (int i = command.length() - 1; i > 0; i--)
				{
					if (command[i] == ' ')
						break;
					removeline += (command[i] - 48)*pow(10, command.length() - 1 - i);
				}
				if (removeline < getChatCount(chats)) {
					removeChat(chats, removeline);
					printChat(chats);
				}
			}
			else {
				for (int i = 7; i < command.length(); i++) {
					// '-'
					if (command[i] == '-') {

						int removeSt = 0;
						int removeEnd = 0;
						for (int i = command.length() - 1; i > 0; i--)
						{
							if (command[i] == '-') {
								stick = i;
								break;
							}
							removeEnd += (command[i] - 48)*pow(10, command.length() - 1 - i);

						}

						for (int i = stick - 1; i > 0; i--)
						{
							if (command[i] == ' ') {
								break;
							}
							removeSt += (command[i] - 48)*pow(10, stick - 1 - i);

						}
						for (int j = removeEnd; j >= removeSt; j--) {
							if (j < getChatCount(chats) && removeEnd>removeSt &&removeSt<getChatCount(chats)) {
								removeChat(chats, j);
								b = 1;
							}
						}
					}
					// ','
					else if (command[i] == ',') {
						int st = command.length() - 1;
						for (int i = st; i > 0; i--)
						{
							if (!(command[i] == ',' || command[i] == ' ')) {
								cnt[k] += (command[i] - 48)*pow(10, st - i);
							}
							if (command[i] == ',')
							{
								st = i - 1;
								k++;
							}
							if (command[i] == ' ')
								break;
						}
						m = k;
						sort(cnt, cnt + m + 1);
						for (int j = m; j >= 0; j--) {
							if (cnt[j] < getChatCount(chats)) {
								removeChat(chats, cnt[j]);
								b = 1;
							}
						}
						for (int l = 0; l <= k; l++) {
							cnt[l] = 0;
						}
						k = 0;
						break;
					}
				}
				if (b == 1) {
					printChat(chats);
				}
			}
			correct = 0;
		}
		//add
		else if (addChat(chats, command)) {
			printChat(chats);
		}
	}
	// delete chatting list
	delete[] chats;

	return 0;
}