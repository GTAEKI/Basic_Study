#include<iostream>
#include<list>
#include "LinkedList.h"
using namespace std;
//
//template<typename T>
//class Node
//{
//public:
//	Node() : _prev(nullptr), _next(nullptr), _data(T())
//	{
//
//	}
//
//	Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
//	{
//
//	}
//
//public:
//	Node* _prev;
//	Node* _next;
//	T	  _data;
//};
//
//template<typename T>
//class Iterator 
//{
//public:
//	Iterator() :_node(nullptr) 
//	{
//	
//	}
//
//	Iterator(Node<T>* node) : _node(node) 
//	{
//	
//	}
//
//	// ++it
//	Iterator& operator++() 
//	{
//		_node = _node->_next;
//		return *this;
//	}
//
//	// it++
//	Iterator operator++(int) 
//	{
//		Iterator<T> temp = *this;
//		_node = _node->_next;
//		return temp;
//	}
//
//	// --it
//	Iterator& operator--()
//	{
//		_node = _node->_prev;
//		return *this;
//	}
//
//	// it--
//	Iterator operator--(int)
//	{
//		Iterator<T> temp = *this;
//		_node = _node->_prev;
//		return temp;
//	}
//
//	// *it
//	T& operator*() 
//	{
//		return _node->_data;
//	}
//
//	bool operator==(const Iterator& other) 
//	{
//		return _node == other._node;
//	}
//
//	bool operator != (const Iterator& other) 
//	{
//		return _node != other._node;
//	}
//
//public:
//	Node<T>* _node;
//};
//
//template<typename T>
//class List
//{
//public:
//	List() : _size(0) 
//	{
//		// [head] <-> ... <-> [tail]
//		_head = new Node<T>();
//		_tail = new Node<T>();
//		_head->_next = _tail;
//		_tail->_prev = _head;
//	}
//
//	~List() 
//	{
//		while (_size > 0)
//			pop_back();
//
//		delete _head;
//		delete _tail;
//	}
//
//	void push_back(const T& value) 
//	{
//		AddNode(_tail, value);
//	}
//
//	void pop_back() 
//	{
//		RemoveNode(_tail->_prev);
//	}
//
//	int size() 
//	{
//		return _size;
//	}
//
//private:
//	Node<T>* AddNode(Node<T>* before, const T& value) 
//	{
//		Node<T>* newNode = new Node<T>(value);
//		Node<T>* prevNode = before->_prev;
//
//		prevNode->_next = newNode;
//		newNode->_prev = prevNode;
//
//		newNode->_next = before;
//		before->_prev = newNode;
//
//		_size++;
//
//		return newNode;
//	}
//
//	Node<T>* RemoveNode(Node<T>* node) 
//	{
//		Node<T>* prevNode = node->_prev;
//		Node<T>* nextNode = node->_next;
//
//		prevNode->_next = nextNode;
//		nextNode->_prev = prevNode;
//
//		delete node;
//
//		_size--;
//
//		return nextNode;
//	}
//
//public:
//	using iterator = Iterator<T>;
//
//	iterator begin() { return iterator(_head->_next); }
//	iterator end() { return iterator(_tail); }
//
//	// it '앞에(이전)' 추가
//	iterator insert(iterator it, const T& value) 
//	{
//		Node<T>* node = AddNode(it._node, value);
//		return iterator(node);
//	}
//
//	iterator erase(iterator it) 
//	{
//		Node<T>* node = RemoveNode(it._node);
//		return iterator(node);
//	}
//
//private:
//
//	// 만약 널포인터가 될 수 있다고 하면, 계속 널 체크를 해줘야 하는문제가 있음
//	// 그래서 실제 사용하느 데이터만가리키ㅔㄱ 하는게아니라 더미노드를 만들어 아무리 데이터가 없어도 시작상태로 노드를 두개를 만든다
//	Node<T>* _head;
//	Node<T>* _tail;
//	int	     _size;
//
//};

int main()
{
    LinkedList<int> li;

    LinkedList<int>::iterator eraseIt = li.end(); // 초기화

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            eraseIt = li.insert(li.end(), i);
        }
        else
        {
            //li.push_back(i);
            li.push_front(i);
        }
    }

    li.pop_back();
    
    //li.erase(eraseIt);

    for (LinkedList<int>::iterator it = li.begin(); it != li.end(); it++)
    {
        cout << (*it) << endl;
    }

    return 0;
}