#pragma once
using namespace std;

#include<algorithm>
#include<cassert>

template<typename T>
class Vector 
{
public:
	Vector() : _size(0), _capacity(0), _data(nullptr) 
	{
	
	}

	~Vector() 
	{
		if (_data) 
		{
			delete[] _data;
		}
	}

	int size() 
	{
		return _size;
	}

	int capacity() 
	{
		return _capacity;
	}

	void push_back(const T& value) 
	{
		if (_size == _capacity) 
		{
			int newCapacity = (int)(_capacity * 1.5f);
			if (newCapacity <= 1) newCapacity++;

			reserve(newCapacity);
		}

		_data[_size] = value;
		_size++;
	}

	void pop_back() 
	{
		if (_size > 0)
		{
			_size--;
		}
	}

	void reserve(const int& capacity) 
	{
		if (_capacity >= capacity) return;
		_capacity = capacity;

		T* newData = new T[_capacity];

		for (int i = 0; i < _size; i++) 
		{
			newData[i] = _data[i];
		}

		if (_data) 
		{
			delete[] _data;
		}
		_data = new Data;
	}

	void resize(const int& size) 
	{
		if (size <= _size) 
		{
			_size = size;
		}
		else if (size > _size) 
		{
			if (size > _capacity) 
			{
				int newCapacity = max((int)(_capacity * 1.5), size);
				reserve(newCapacity);
			}

			for (int i = _size; i < size; i++) 
			{
				_data[i] = 0;
			}
			_size = size;
		}
	}

	bool empty() 
	{
		return _size == 0;
	}

	void clear() 
	{
		if (_data) 
		{
			delete[] _data;
			_data = new T[_capacity];
		}
	}

private:
	int _size;
	int _capacity;
	T* _data;
};