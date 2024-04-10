#include<iostream>
#include "Vector.h"
#include <vector>
#include "LinkedList.h"
#include <list>

using namespace std;

int main()
{
#pragma region Vector
	/*vector<int> v;

	v.reserve(10);
	v.resize(5);

	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);

		cout << v[i] << " " << v.capacity() << "\n";
	}

	v.pop_back();

	for (int i = 0; i < v.size(); i++)
	{
		cout << "[1] " << v[i] << "\n";
	}

	while (!v.empty())
	{
		v.pop_back();
	}

	v.resize(15);

	for (int i = 0; i < v.size(); i++)
	{
		cout << "[3] " << v[i] << " " << v.capacity() << "\n";
	}

	v.clear();
	cout << v.size() << " " << v.capacity() << "\n";*/
#pragma endregion

	LinkedList<int> li;

	LinkedList<int>::iterator eraseIt = li.end(); // 초기화

	for (int i = 0; i < 10; i++)
	{
		if (i == 5)
		{
			eraseIt = li.insert(li.end(), i);
		}
		else
		{
			li.push_back(i);
			//li.push_front(i);
		}
	}

	li.pop_back();

	//li.erase(eraseIt);

	for (LinkedList<int>::iterator it = li.begin(); it != li.end(); it++)
	{
		cout << (*it) << endl;
	}

	return 0;

}