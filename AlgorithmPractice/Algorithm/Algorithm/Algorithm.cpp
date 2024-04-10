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

		cout << v[i] << " " << v.capacity() << "\n";
	}

	v.pop_back();

	for (int i = 0; i < v.size(); i++) 
	{
		cout << "[1] " << v[i] << "\n";
	}

	/*for (int i = 0; i < v.size(); i++)
	{
		v.pop_back();
	}*/

	while (!v.empty()) 
	{
		v.pop_back();
	}

	for (int i = 0; i < v.size(); i++)
	{
		cout << "[3] " << v[i] << "\n";
	}

	v.clear();
	cout << v.size() << " " << v.capacity() << "\n";
	return 0;
}