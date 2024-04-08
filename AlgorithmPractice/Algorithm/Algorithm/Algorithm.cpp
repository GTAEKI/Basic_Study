#include<iostream>
using namespace std;

template <typename T>
class Vector
{
public:
	Vector()
	{
	}

	~Vector()
	{
		if (_data)
		{
			delete[] _data;
		}
	}

	void reserve(int capacity)
	{
		if (_capacity >= capacity)
		{
			return;
		}
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

	void push_back(const T& value)
	{
		if (_size == _capacity)
		{
			int newCapacity = static_cast<int>(_capacity * 1.5f);
			if (_capacity == newCapacity)
				++newCapacity;

			reserve(newCapacity);
		}

		_data[_size] = value;
		++_size;
	}

	T& operator [](const int pos) { return _data[pos]; };

	void clear()
	{
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
		}

		_size = 0;
	}

	int size()
	{
		return _size;
	}

	int capacity()
	{
		return _capacity;
	}



private:
	T* _data = nullptr;
	int _size = 0;
	int _capacity = 0;

};

int main()
{
	// vector 클래스
	Vector<int> v;

	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
	}

	v.clear();
	cout << v.size() << " " << v.capacity() << endl;

}