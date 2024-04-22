#pragma once

template <typename T>
class Vector 
{
public:
	Vector() : _size(0),_capacity(0),_data(nullptr)
	{
	
	}

	~Vector() 
	{
		if (_data)
		{
			delete[] _data;
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
			delete[] _data;

		_data = newData;
	}

	void push_back(const T& value) 
	{
		if (_size >= _capacity) 
		{
			int tempCapacity = _capacity * 1.5f;
			if (tempCapacity <= 1) tempCapacity++;

			reserve(tempCapacity);
		}

		_data[_size] = value;
		_size++;
	}

	void pop_back() 
	{
		if (_size > 0)
			_size--;
	}

	int size() 
	{
		return _size;
	}

	int capacity()
	{
		return _capacity;
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
		return _data[index];
	}



private:
	int _size;
	int _capacity; 
	T* _data;
};