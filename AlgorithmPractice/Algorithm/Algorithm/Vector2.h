#pragma once

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

public:
	void push_back(const T& data)
	{
		if (_size == _capacity) 
		{
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity <= 1) newCapacity++;
			reserve(newCapacity);
		}

		_data[_size] = data;
		_size++;
	}

	void pop_back() 
	{
		if (_size > 0)
			--_size;
	}

	bool empty() 
	{
		return _size == 0;
	}

	void reserve(int capacity)
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

	void resize(int size)
	{
		if (_size <= size) 
		{
			_size = size;
		}
		else
		{
			if (_capacity < size) 
			{
				reserve(size);
				_capacity = size;
			}

			for (int i = _size; i < size; i++) 
			{
				_data[i] = 0;
			}

			_size = size;
		}
	}

	void clear() 
	{
		if (_data) 
		{
			delete[] _data;
			_data = new T[_capacity];
			_size = 0;
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

	T operator[](const int& index) 
	{
		return _data[index];
	}
	
private:
	int _size;
	int _capacity;
	T* _data;
};