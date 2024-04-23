#pragma once

#include<vector>
#include<queue>
using namespace std;

// 버블 정렬
void BubbleSort(vector<int>& v) 
{
	int n = v.size();

	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n-i-1; j++) 
		{
			if (v[j] > v[j + 1]) 
			{
				::swap(v[j], v[j + 1]);
			}
		}
	}
}

void SelectionSort(vector<int>& v) 
{
	int n = v.size();

	for (int i = 0; i < n; i++) 
	{
		int bestIdx = i;
		for (int j = i+1; j < n; j++) 
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}

		::swap(v[i], v[bestIdx]);
	}
}

void InsertionSort(vector<int>& v) 
{
	int n = v.size();

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
}

void HeapSort(vector<int>& v) 
{
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int num : v)
		pq.push(num);

	v.clear();

	while (pq.empty() == false) 
	{
		v.push_back(pq.top());
		pq.pop();
	}
}


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

	MergeResult(v, left, mid, right);
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
}