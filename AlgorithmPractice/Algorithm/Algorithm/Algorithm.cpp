#include<iostream>
#include "Vector.h"
#include <vector>

using namespace std;

int main() 
{
	vector<int> v;

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
	cout << v.size() << " " << v.capacity() << "\n";
	return 0;
}