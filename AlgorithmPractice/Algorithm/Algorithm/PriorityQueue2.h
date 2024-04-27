#pragma once

#include<vector>
using namespace std;

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue 
{
public:
	void push(const T& value) 
	{
		_heap.push_back(value);

		int now = _heap.size() - 1;

		while (now > 0) 
		{
			int next = (now-1) / 2;
			
			if (_pred(_heap[now], _heap[next]))
				return;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	void pop() 
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;

		while (true) 
		{
			int left = (now * 2) + 1;
			int right = (now * 2) + 2;
			int next = now;

			if (left >= _heap.size())
				return;

			if (_pred(_heap[next], _heap[left]))
				next = left;

			if (right < _heap.size() && _pred(_heap[next], _heap[right]))
				next = right;

			if (next == now)
				return;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	T& top() 
	{
		return _heap[0];
	}

	int size() 
	{
		return _heap.size();
	}

	bool empty() 
	{
		return _heap.empty();
	}

private:
	Container _heap = {};
	Predicate _pred = {};
};