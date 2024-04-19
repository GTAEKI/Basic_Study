#pragma once

template<typename T>
class Vector 
{
public:
	Vector() : _capacity(0), _size(0), _data(nullptr)
	{
		
	}

	~Vector()
	{
		if(_data)
			delete[] _data;
	}

	void push_back(const T& value) 
	{
		if (_size >= _capacity) 
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
		if (size > 0)
			_size--;
	}

	void empty() 
	{
		return _size == 0;
	}

	int size() 
	{
		return _size;
	}

	int capacity() 
	{
		return _capacity;
	}

	void reserve(const int& capacity) 
	{
		if (capacity <= _capacity)
			return;
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
			_data = new T(_capacity);
		}

		_size = 0;
	}

	T& operator [](const int& index)
	{
		return _data[index];
	}




private:
	T* _data;
	int _size;
	int _capacity;
};