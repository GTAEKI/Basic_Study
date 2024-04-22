#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
#include<Windows.h>
using namespace std;

#include"LinkedList3.h"

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

	LinkedList<int> l3;

	l3.push_back(3);
	l3.push_back(4);
	l3.push_back(5);
	l3.push_back(6);

	for (auto iter = l3.begin(); iter != l3.end(); iter++) 
	{
		cout << *iter << endl;
	}

	l3.pop_back();

	cout << l3.size();

	return 0;
}

