#pragma once
using namespace std;

#include<algorithm>
#include<cassert>

template<typename T>
class Vector
{
public:
	Vector() :_size(0), _capacity(0), _data(nullptr)
	{

	}

	~Vector()
	{
		if (_data) 
		{
			delete[] _data;
		}
	}

public:
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
			int newCapacity = static_cast<int>(_capacity * 1.5);
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
			--_size;
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
		_data = newData;
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
				int newCapacity = max(static_cast<int>(_capacity * 1.5), size);
				reserve(newCapacity);
			}

			// 데이터 복사 및 빈공간 채우기
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

		_size = 0;
	}

	T& operator[](const int& index)
	{
		assert(index >= 0 && index < _size); // 인덱스 범위 검사
		return _data[index];
	}


private:
	int _size;
	int _capacity;
	T* _data;
};