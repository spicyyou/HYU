//2017030519_È«À¯Áø_A
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<queue>
#include<algorithm>
#include<stack>
#include<map>
#include<functional>
#define pii pair<int,int>

using namespace std;
priority_queue < pair<int, pii> > pq;

int v[10005];

int find(int x) {
	if (x == v[x]) return x;
	return v[x] = find(v[x]);
}
priority_queue<pair<int, pii> > res;

vector<pair<int, pii> > input;
int main() {
	int V;
	int sum = 0;
	int cnt = 0;
	scanf("%d", &V);
	for (int i = 0; i <= V; i++) {
		v[i] = i;
	}

	int a, b, c;
	int t = 0;
	while(scanf("%d",&a)!=EOF) {
	//for (int i = 0; i < 14; i++) {
		//scanf("%d", &a);
		scanf("%d%d", &b, &c);
		if (a < b) {
			input.push_back({ a,{ b,c } });
		}
		else {
			input.push_back({ b,{ a,c } });
		}
		t++;
	}
	sort(input.begin(), input.end());
	for (int i = 0; i <t; i++) {
		int a = input[i].first;
		int b = input[i].second.first;
		int w = input[i].second.second;
		pq.push({ -w,{ -a,-b } });
	}

	while (!pq.empty()) {
		int a = pq.top().second.first*(-1); //a a->b
		int b = pq.top().second.second*(-1);//b
											//a->b
		int w = pq.top().first*(-1);
		int hi = find(a);
		int bye = find(b);
		pq.pop();
		//printf(": %d %d %d \n", a, b, w);
		if (hi == bye) continue;
		else {
			v[hi] = bye;
			cnt++;
			res.push({ -w,{ -a,-b } });
		}
	}
	printf("%d\n", cnt);
	//sort(res.begin(), res.end());
	while (!res.empty()) {
		int a = res.top().second.first*(-1); //a a->b
		int b = res.top().second.second*(-1);//b
		int w = res.top().first*(-1);
		printf("%d %d %d\n", a, b, w);
		res.pop();
	}
}