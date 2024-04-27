#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
#include<Windows.h>
using namespace std;

#include"LinkedList2.h"
#include"PriorityQueue2.h"
//#include"SortTotal3.h"

int main()
{
#pragma region MyRegion

	//Vector<int> v3;

	//v3.reserve(8);

	//cout << v3.size() << v3.capacity() << endl;

	//v3.push_back(1);
	//v3.push_back(2);
	//v3.push_back(3);
	//v3.push_back(4);
	//v3.push_back(5);
	//v3.push_back(6);
	//v3.push_back(7);
	//v3.push_back(8);

	//for (int i = 0; i < v3.size(); i++) 
	//{
	//	cout << v3[i] << endl;
	//}

	//cout << v3.size() << v3.capacity() << endl;

	//v3.push_back(9);

	//cout << v3.size() << v3.capacity() << endl;

	//v3.pop_back();
	//v3.pop_back();
	//v3.pop_back();

	//cout << v3.size() << v3.capacity() << endl;

	//v3.clear();

	//cout << v3.size() << v3.capacity() << endl;
#pragma endregion

	//LinkedList<int> l3;

	//l3.push_back(3);
	//l3.push_back(4);
	//l3.push_back(5);
	//l3.push_back(6);

	//for (auto iter = l3.begin(); iter != l3.end(); iter++) 
	//{
	//	cout << *iter << endl;
	//}

	//l3.pop_back();

	//LinkedList<int> ::iterator iter2 = l3.begin();
	//iter2++;
	//l3.insert(iter2, 999);

	//for (auto iter = l3.begin(); iter != l3.end(); iter++)
	//{
	//	cout << "추가: " << *iter << endl;
	//}


	//cout << l3.size() << endl;

	//l3.erase(iter2);


	//for (auto iter = l3.begin(); iter != l3.end(); iter++)
	//{
	//	cout << "추가2: " << *iter << endl;
	//}

	//cout << l3.size() << endl;


	PriorityQueue<int> pq;

	pq.push(100);
	pq.push(300);
	pq.push(200);
	pq.push(500);
	pq.push(400);


	while (pq.empty() == false)
	{
		int value = pq.top();
		pq.pop();

		cout << value << endl;
	}

	//vector<int> v{1,3,2,4,9,6,7,5,8};

	////BubbleSort<int>(v,greater<int>());
	////SelectionSort(v);
	////InsertionSort(v);
	////HeapSort(v);
	////MergeSort(v, 0, v.size()-1);
	////QuickSort(v, 0, v.size() - 1);

	//for (auto num : v) 
	//{
	//	cout << num << endl;
	//}

	return 0;
}

