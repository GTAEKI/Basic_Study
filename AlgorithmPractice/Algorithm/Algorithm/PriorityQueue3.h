#pragma once

#include<vector>
using namespace std;

template <typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue 
{
public:

	void push(const T& value) 
	{
		_head.push_back(value);

		int now = _head.size() - 1;

		while (now > 0) 
		{
			int next = (now - 1) / 2;

			if (_predicate(_head[now], _head[next]))
				return;

			::swap(_head[now], _head[next]);
			now = next;
		}
	}

	void pop() 
	{
		if (_head.empty())
			return;

		_head[0] = _head.back();
		_head.pop_back();

		int now = 0;

		while (true) 
		{
			int left = (now * 2) + 1;
			int right = (now * 2) + 2;
			
			int next = now;
			if (_head.size() <= left)
				return;

			if (_predicate(_head[next], _head[left]))
			{
				next = left;
			}

			if (_head.size() > right && _predicate(_head[next], _head[right])) 
			{
				next = right;
			}

			if (now == next) return;

			::swap(_head[now], _head[next]);
			now = next;
		}
	}

	T& top() 
	{
		return _head[0];
	}

	bool empty() 
	{
		return _head.empty();
	}

	int size() 
	{
		return _head.size();
	}

private:
	Container _head = {};
	Predicate _predicate = {};
	
};