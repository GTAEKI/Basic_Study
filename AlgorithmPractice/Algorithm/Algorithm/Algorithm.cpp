#include<iostream>
#include "Vector.h"
#include <vector>

using namespace std;

int main() 
{
	Vector<int> v;

	for (int i = 0; i < 10; i++) 
	{
		v.push_back(i);

		if (i == 9) 
		{
			v.pop_back();
		}
		cout << v[i] << " " << v.capacity() << "\n";
	}

	//cout << v.capacity() << "\n";

	for (int i = 0; i < v.size(); i++) 
	{
		cout << "[1] " << v[i] << "\n";
	}

	for (int i = 0; i < v.size(); i++)
	{
		v.pop_back();
	}

	for (int i = 0; i < v.size(); i++)
	{
		cout << "[3] " << v[i] << "\n";
	}

	v.clear();
	cout << v.size() << "\n" << v.capacity() << "\n";
	return 0;
}