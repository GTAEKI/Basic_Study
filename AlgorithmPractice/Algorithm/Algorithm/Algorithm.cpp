#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
#include<Windows.h>
using namespace std;

#include"Vector3.h"

int main()
{
	Vector<int> v3;

	v3.reserve(8);

	cout << v3.size() << v3.capacity() << endl;

	v3.push_back(1);
	v3.push_back(2);
	v3.push_back(3);
	v3.push_back(4);
	v3.push_back(5);
	v3.push_back(6);
	v3.push_back(7);
	v3.push_back(8);

	for (int i = 0; i < v3.size(); i++) 
	{
		cout << v3[i] << endl;
	}

	cout << v3.size() << v3.capacity() << endl;

	v3.push_back(9);

	cout << v3.size() << v3.capacity() << endl;

	v3.pop_back();
	v3.pop_back();
	v3.pop_back();

	cout << v3.size() << v3.capacity() << endl;

	v3.clear();

	cout << v3.size() << v3.capacity() << endl;

	return 0;
}

