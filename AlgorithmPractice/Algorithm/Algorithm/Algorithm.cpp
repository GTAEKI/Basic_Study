#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
using namespace std;

#include"BasicSort.h"
#include"HeapSortMergeSort.h"

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
		while (low <= right && pivot >= v[low] )
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

		while (high >= left+1 && pivot <= v[high])
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


int main()
{
#pragma region 실행부
	/*Vector<int> v;

	v.push_back(1);
	v.push_back(3);
	v.push_back(5);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << "\n";
	}

	v.pop_back();
	v.pop_back();

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << "\n";
	}

	cout << v.empty();*/


	/*RedBlackTree bst;

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(10);
	bst.Print();
	this_thread::sleep_for(1s);*/
#pragma endregion

	vector<int> v;

	srand(time(0));

	for (int i = 0; i < 50; i++)
	{
		int randValue = rand() % 100;
		v.push_back(randValue);
	}

	//BubbleSort(v);
	//SelectionSort(v);
	//InsertionSort(v);
	//HeapSort(v);
	//MergeSort2(v, 0, v.size() - 1);
	//HeapSort2(v);

	QuickSort3(v, 0, v.size() - 1);

	return 0;
}

