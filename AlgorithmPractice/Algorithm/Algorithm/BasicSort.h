#pragma once

#include<vector>
using namespace std;

// 오늘의 주제 : 정렬

// C# 자료구조 / 알고리즘
// -> A* OpenList(PQ) 를 왜 쓰는가
// -> C# List 에서 sort를 쓰면 되는게 아니냐?

// 정렬을 공부하지 않으면 sort가 굉장히 빠르게 동작하는것으로 생각 할 수 있다.
// 정렬과 PQ는 시간복잡도가 어마어마하게 차이가 많이난다.

// 이진트리구조는 대부분 logN의 시간복잡도이다.
// Sorting? 
// 코딩 면접에서도 자주 나온다.

// 1) 버블 정렬 (Bubble Sort)
// - 뒤쪽부터 자리가 정렬되는 방식
// - 시간복잡도
void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n - 1 - i); j++)
		{
			if (v[j] > v[j + 1])
			{
				int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
				// swap(v[i],v[j+1]);
			}
		}
	}
}

// 2) 선택 정렬 (Selection Sort)
void SelectionSort(vector<int>& v)
{
	const int n = v.size();
	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}

		int temp = v[i];
		v[i] = v[bestIdx];
		v[bestIdx] = temp;
	}
}


// 3) 삽입 정렬 (Insertion Sort)
// 코딩면접에서 컨셉이 자주나옴
// 특히 문자열과 같은 문제, 뒷부분부터 건드려서 작업하는 경우가 많이 생긴다.
/*void InsertionSort(vector<int>& v)
{
	const int n = v.size();

	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];

		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
			{
				v[j + 1] = v[j];
			}
			else
			{
				break;
			}
		}

		v[j + 1] = insertData;
	}
}*/

void InsertionSort(vector<int>& v)
{
	const int n = v.size();

	for (int i = 1; i < n; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (v[j+1] < v[j])
			{
				int temp = v[j+1];
				v[j+1] = v[j];
				v[j] = temp;
			}
			else
			{
				break;
			}
		}
	}
}