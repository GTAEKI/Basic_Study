#pragma once

#include<vector>
using namespace std;

void InsertionSort(vector<int>& v) 
{
	const int n = v.size();

	for (int i = 0; i < n; i++) 
	{
		int temp = v[i];

		int j = i - 1;
		for (; j >= 0; j--) 
		{
			if (v[j] > temp) 
			{
				v[j + 1] = v[j];
			}
			else 
			{
				break;
			}
		}
		
		v[j + 1] = temp;
	}
}

void MergeResult(vector<int>& v, int left, int mid, int right) 
{
	int leftIdx = left;
	int rightIdx = mid+1;
	
	vector<int> temp;

	while (leftIdx <= mid && rightIdx <= right) 
	{
		if (v[leftIdx] < v[rightIdx]) 
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

	if (leftIdx <= mid) 
	{
		while (leftIdx <= mid) 
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}
	else 
	{
		while (rightIdx <= right) 
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	for (int i = 0; i < temp.size(); i++) 
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right) 
{
	if (left >= right) return;

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
		while (low <= right && v[low] <= pivot)
			low++;

		while (high >= left + 1 && v[high] >= pivot)
			high--;

		if (low < high)
		{
			::swap(v[low], v[high]);
		}
	}

	::swap(v[left], v[high]);

	QuickSort(v, left, high - 1);
	QuickSort(v, high + 1, right);
}