#pragma once

#include<iostream>
#include<vector>
using namespace std;

// DP (ENCHANT)

// +0 집행검
// 무기 강화 주문서 => +1 / +2 / +3 중 하나

// +N 집행검 뜨는 경우의 수는?
// ex) +1 +2 +3 +4 ...+9
// ex) +3 +6 +9
// ex) +1 +3 +4

int N;
int cache[10];

int Enchant(int num)
{
	if (num == N)
		return 1;
	else if (num > N)
		return 0;

	int& ret = cache[num];
	if (ret != -1)
		return ret;

	return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);
}
//
//int main()
//{
//	N = 4;
//	memset(cache, -1, sizeof(cache));
//
//	int ret = Enchant(0);
//
//	cout << ret << endl;
//
//}