#pragma once


template<typename T>
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

	void empty() 
	{
		reutn _size == 0;
	}

	void size() 
	{
		return _size;
	}

	void capacity() 
	{
		return _capacity;
	}

	void clear() 
	{
		if (_data) 
		{
			delete[] _data;
			_data = new data[_capacity];
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