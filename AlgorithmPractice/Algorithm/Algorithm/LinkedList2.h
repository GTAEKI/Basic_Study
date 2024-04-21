#pragma once

template<typename T>
class Node 
{
public:
	Node() : _next(nullptr),_prev(nullptr), _data(T())
	{
		
	}

	Node(const T& value) : _next(nullptr), _prev(nullptr), _data(value)
	{
		
	}

public:
	Node<T>* _next;
	Node<T>* _prev;
	T _data;
};

template<typename T>
class Iterator 
{
public:
	Iterator() : _node(nullptr)
	{
		
	}

	Iterator(Node<T>* node) : _node(node)
	{
	
	}

	Iterator operator++(int)
	{
		Iteator<T> temp = *this;
		_node = _node->next;
		return temp;
	}

	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_prev;
		return temp;
	}

	bool operator==(const Iterator& other)
	{
		return _node == other._node;
	}

	bool operator!=(const Iterator& other)
	{
		return _node != other._node;
	}

	T& operator*() 
	{
		return _node->_data;
	}

public:
	Node<T>* _node;
};

template<typename T>
class LinkedList 
{
public:
	using iterator = Iterator<T>;

	LinkedList() : _size(0)
	{
		_head = new Node<T>();
		_tail = new Node<T>();

		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~LinkedList() 
	{
		while (_size > 0)
			pup_back();

		delete _head;
		delete _tail;
	}

	void push_back(const T& value) 
	{
		AddNode(_tail, value);
	}

	void size() 
	{
		return _size;
	}

	void pop_back() 
	{
		DeleteNode(_tail->_prev);
	}

	iterator Insert(iterator iter, const T& value) 
	{
		Node<T>* node = AddNode(iter._node, value);
		return iterator(node);
	}

	iterator erase(iterator iter)
	{
		Node<T>* node = RemoveNode(iter._node);
		return iterator(node);
	}

	iterator begin()
	{
		return iterator(_head->_next);
	}

	iterator end()
	{
		return iterator(_tail);
	}

private:
	Node<T>* AddNode(Node<T>& nextNode,const T& value) 
	{
		Node<T> newNode = new Node<T>(value);
		Node<T> prevNode = nextNode->_prev;

		newNode->_prev = prevNode;
		prevNode->_next = newNode;

		newNode->_next = nextNode;
		nextNode->_prev = newNode;

		_size++;
		return newNode;
	}

	Node<T>* DeleteNode(Node<T>& deleteNode) 
	{
		Node<T> nextNode = deleteNode->_next;
		Node<T> prevNode = deleteNode->_prev;

		nextNode->_prev = prevNode;
		prevNode->_next = nextNode;

		delete deleteNode;

		_size--;
		return nextNode;
	}

private:
	Node<T>* _head;
	Node<T>* _tail;
	int _size;
};