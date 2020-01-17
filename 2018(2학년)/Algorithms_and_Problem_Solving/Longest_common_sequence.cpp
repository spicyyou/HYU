//2017030519_홍유진_A
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
#include<string.h>
using namespace std;
int DP[1010][1010];
//int DP[];
int prv[1010][1010];
//int arr2[100005];

char str1[1010];
char str2[1010];	
int main() {
	scanf("%s\n%s", str1 + 1, str2 + 1);//strlen할때또 +1 해줘야함
	int len1 = strlen(str1 + 1);
	int len2 = strlen(str2 + 1);
	for (int i = 1; i <= len2; i++) {
		for (int j = 1; j <= len1; j++) {
			if (str1[j] == str2[i]) {
				DP[i][j] = DP[i - 1][j - 1] + 1;
			}
			else {
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
			}
		}
	}
	printf("%d\n", DP[len2][len1]);
	int start1 = len1, start2 = len2;
	vector<char> vec;
	while (1) {
		//둘보다 큰거
		if (DP[start2][start1] == DP[start2 - 1][start1]
			) {
			start2--;
		}
		else if (DP[start2][start1] == DP[start2][start1 - 1]) {
			start1--;
		}
		else if (DP[start2][start1] - DP[start2 - 1][start1 - 1] == 1) {
			vec.push_back(str2[start2]);
			start1--;
			start2--;
		}
		if (start1 < 0 || start2 < 0) {
			break;
		}
	}
	for (int i = vec.size() - 1; i >= 0; i--) {
		printf("%c", vec[i]);
	}
	printf("\n");
}