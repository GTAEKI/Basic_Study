#pragma once

#include<vector>
#include<queue>
using namespace std;

// 힙 정렬
// 힙을 이용한 정렬이다.
// 결과적으로 NlogN
void HeapSort(vector<int>& v)
{
	// Priority Queue는
	// 내부 구조가 꼭 힙으로 만들어져야 한다는 뜻은 아니고
	// 큐는 큐인데 우선순위에 따라 내가 지정한 값을 추출해주는 큐를 의미하는것
	priority_queue<int, vector<int>, greater<int>> pq;

	// O(NlogN)
	for (int num : v)
		pq.push(num);

	v.clear();

	//O(NlogN)
	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}


// 병합 정렬
// 분할 정복 (Divied and Conquer)
// - 분할 (Divide)		문제를 더 단순하게 분할한다.
// - 정복 (Conquer)		분할된 문제를 해결
// - 결합 (Combine)		결과를 취합하여 마무리

// 내가 문제를 해결(정복)하기 쉬울때까지 분해하는것
void MergeResult(vector<int>& v, int left, int mid, int right)
{

	int leftIdx = left;
	int rightIdx = mid + 1;

	vector<int> temp;

	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	// 왼쪽이 먼저 끝났으면, 오른쪽 나머지 데이터 복사
	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	else
	{
		while (leftIdx <= mid)
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right); // 결합
}


void MergeResult2(vector<int>& v, int left, int mid, int right)
{
	int leftIdx = left;
	int rightIdx = mid + 1;

	vector<int> newVector;

	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] < v[rightIdx])
		{
			newVector.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			newVector.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			newVector.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	else
	{
		while (leftIdx <= mid)
		{
			newVector.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	for (int i = 0; i < newVector.size(); i++)
	{
		v[left + i] = newVector[i];
	}
}

void MergeSort2(vector<int>& v, int left, int right)
{
	if (left >= right) return;

	int mid = (left + right) / 2;

	MergeSort2(v, left, mid);
	MergeSort2(v, mid + 1, right);

	MergeResult2(v, left, mid, right);
}

void HeapSort2(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int n : v)
	{
		pq.push(n);
	}

	v.clear();

	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}


// Quick Sort
// Merge Sort와 마찬가지로 둘씩 쪼개서 진행하는것까지는 비슷하다.
// 단, 어느정도 특정 알고리즘을 적용시켜 무엇인가를 한 뒤 나눈다는 점이 다르다.
// 최악의 경우 O(N^2) 이 될 수 있음
// O(NlogN) -> 평균적으로
// 최악의 경우 느린 시간복잡도를 갖고있지만 데이터를 복사하는 내용이 거의 없기에 평균적으로 병합정렬보다 빠르게 동작한다.

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	// O(N)
	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;

		while (high >= left + 1 && pivot <= v[high])
			high--;

		if (low < high)
			swap(v[low], v[high]);
	}

	swap(v[left], v[high]);
	return high;
}

void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right) return;

	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;

		while (high >= left + 1 && pivot <= v[high])
			high--;

		if (low < high)
			swap(v[low], v[high]);
	}

	swap(v[left], v[high]);

	QuickSort(v, left, high - 1);
	QuickSort(v, high + 1, right);

	/*int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);*/
}


void QuickSort2(vector<int>& v, int left, int right)
{
	if (left >= right) return;

	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;

		while (high >= left + 1 && pivot <= v[high])
			high--;

		if (low < high) // 선을 넘어갔을 수 있음
		{
			int temp = v[low];
			v[low] = v[high];
			v[high] = temp;
		}
	}

	int temp = v[left];
	v[left] = v[high];
	v[high] = temp;


	QuickSort2(v, left, high - 1);
	QuickSort2(v, high + 1, right);
}

void QuickSort3(vector<int>& v, int left, int right)
{
	if (left >= right) return;

	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;

		while (high >= left + 1 && pivot <= v[high])
			high--;

		if (low < high)
		{
			swap(v[low], v[high]);
		}
	}

	swap(v[left], v[high]);

	QuickSort3(v, left, high - 1);
	QuickSort3(v, high + 1, right);
}
