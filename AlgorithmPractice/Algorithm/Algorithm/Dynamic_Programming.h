#pragma once

#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
#include<Windows.h>
using namespace std;

int combination(int n, int r) //n개중에 r개 뽑는 경우의 수
{
	// 기저 사례
	if (r == 0 || n == r)
		return 1;

	return combination(n - 1, r - 1) + combination(n - 1, r);
}

// 이미 알고있는 c n,r이라는 특정값에 대해 처음 한번은 어쩔수 없기 구해야하지만
// 이미 구했다면 어딘가에저장해서 반복을 방지할 수 있지 않을까? 라는 아이디어
// 메모이제이션, 캐쉬를 이용해서 값을저장한다가 핵심이다. ???

// 메모이 제이션 (memoization)
// 50,50 은 n,r을 의미, 문제마다 요구하는 함수의 모양에 따라 달라진다.
// 물론, n,r의 숫자가 너무 커진다면 캐시메모리 할당하는것 자체가 부담이 상당할것이다.
// 메모리를 손실을 감수하고서라도 속도를 갖고갈 수 있다.
int cache[50][50];
//bool visitied[][] 두개 만들면 낭비가 심하다는 느낌
// 그래서 경우의수 에서는 음수가 나올수가 없으니 -1로 처음에초기화

int combination2(int n, int r) //n개중에 r개 뽑는 경우의 수
{
	// 기저 사례
	if (r == 0 || n == r)
		return 1;

	// 메모이제이션 (이미 답을 구한 적 있으면 바로 반환)
	int& ret = cache[n][r];
	if (ret != -1)
		return ret;

	// 새로 답을 구해서 캐시에 저장
	return ret = combination2(n - 1, r - 1) + combination2(n - 1, r);
}

//
//int main()
//{
//	::memset(cache, -1, sizeof(cache));
//
//	__int64 start = GetTickCount64();
//
//	// 0ms
//	int lotto = combination2(45, 6);
//
//	// 172ms
//	//int lotto = combination(45, 6);
//
//	__int64 end = GetTickCount64();
//
//	cout << end - start << " ms" << endl;
//	cout << lotto << " value" << endl;
//
//
//	return 0;
//}

