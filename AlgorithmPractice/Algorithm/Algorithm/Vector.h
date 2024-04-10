#pragma once

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
		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of range");
		}
		return _data[index];
	}


private:
	int _size;
	int _capacity;
	T* _data;
};