#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
using namespace std;


template<typename T>
class PriorityQueue_Less
{
public:
	void push(const T& data) 
	{
		_heap.push_back(data);

		int now = _heap.size() - 1;

		while (now > 0) 
		{
			int next = (now - 1) / 2;

			if (_heap[now] < _heap[next]) break;

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
			int left = now * 2 + 1;
			int right = now * 2 + 2;

			if (_heap.size() <= left) break;

			int next = now;
			if (_heap[next] < _heap[left]) next = left;
			else if (_heap.size() > right && _heap[next] < _heap[right]) next = right;

			if (next == now) break;

			::swap(_heap[next], _heap[now]);
			now = next;
		}
	}


	T& top() 
	{
		return _heap[0];
	}

	bool empty() 
	{
		return _heap.empty();
	}


private:
	vector<T> _heap;
};



//template <typename T, typename Container = vector<T>, typename _Pr = less<T>>
//class PriorityQueue 
//{
//public:
//	void push(const T& data) 
//	{
//		_heap.push_back(data);
//
//		int now = _heap.size() - 1;
//
//		while (now > 0) 
//		{
//			int next = (now - 1) / 2;
//			if (predicate(_heap[now], _heap[next])) break;
//
//			::swap(_heap[now], _heap[next]);
//			now = next;
//		}
//	}
//
//	void pop() 
//	{
//		_heap[0] = _heap.back();
//		_heap.pop_back();
//
//		int now = 0;
//
//		while (true) 
//		{
//			int left = now * 2 + 1;
//			int right = now * 2 + 2;
//
//			if (_heap.size() <= left) break;
//
//			int next = now;
//
//			if (predicate(_heap[next], _heap[left]))
//				next = left;
//
//			if (_heap.size() <= right) break;
//			if (predicate(_heap[next], _heap[right]))
//				next = right;
//
//			if (next == now) break;
//
//			::swap(_heap[now], _heap[next]);
//			now = next;
//		}
//	}
//
//	T& top() 
//	{
//		return _heap[0];
//	}
//
//	bool empty() 
//	{
//		return _heap.empty();
//	}
//
//private:
//	Container _heap = {};
//	_Pr predicate = {};
//};


int main()
{
	//PriorityQueue<int, vector<int>, greater<int>> pq;
	PriorityQueue_Less<int> pq;

	pq.push(100);
	pq.push(300);
	pq.push(200);
	pq.push(500);
	pq.push(400);
	

	while (pq.empty() == false) 
	{
		int value = pq.top();
		pq.pop();

		cout << value << endl;
	}

	return 0;
}