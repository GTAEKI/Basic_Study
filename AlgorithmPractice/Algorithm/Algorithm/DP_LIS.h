#pragma once

#include<vector>
#include <iostream>
using namespace std;

vector<int> seq;
int cache[100];

int LIS(int pos)
{
	// 기저 사항 - 없을 수도 있음
	/*if (pos == seq.size() - 1)
		return 1;*/

		// 캐시 확인
	int& ret = cache[pos];
	if (ret != -1)
		return ret;

	// LIS(0) = LIS(1) +1
	// LIS(1) = 1

	// 구하기
	ret = 1; // 최소 seq[pos]는 있으니 1부터 시작

	for (int next = pos + 1; next < seq.size(); next++)
	{
		if (seq[pos] < seq[next])
			ret = max(ret, 1 + LIS(next));
	}

	return ret;
}

//int main()
//{
//	::memset(cache, -1, sizeof(cache));
//
//	seq = vector<int>{ 1,9,2,5,7 };
//
//	int ret = 0;
//	for (int i = 0; i < seq.size(); i++)
//	{
//		ret = max(ret, LIS(i));
//	}
//
//	cout << ret;
//
//	return 0;
//}
