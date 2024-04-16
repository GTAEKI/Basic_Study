#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
using namespace std;

#include"BasicSort.h"

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
	MergeSort2(v, 0, v.size() - 1);

	return 0;
}

