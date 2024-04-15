#pragma once

template<typename T>
class Node
{
public:
	Node() : _next(nullptr), _prev(nullptr), _data(T())
	{

	}

	Node(const T& data) : _next(nullptr), _prev(nullptr), _data(data)
	{
		
	}


public:
	Node* _next;
	Node* _prev;
	T _data;
};

template<typename T>
class Iterator
{
public:
	Iterator() : _node(nullptr) 
	{
	
	}

	Iterator(const Node<T>* node) : _node(node) 
	{
	
	}

	// i++
	Iterator operator++(int) 
	{
		Iterator<T> temp = *this;
		_node = _node->_next;
		return temp;
	}

	// ++i
	Iterator& operator++() 
	{
		_node = _node->_next;
		return *this;
	}

	// i--
	Iterator operator--(int) 
	{
		Iterator<T> temp = *this;
		_node = _node->_prev;
		return temp;
	}

	// --i
	Iterator operator--() 
	{
		_node = _node->_prev;
		return *this;
	}

	bool operator==(const Iterator& other) 
	{
		return _node == other._node;
	}

	bool operator!= (const Iterator& other) 
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
	LinkedList() :size(0)
	{
		_head = new Node<T>();
		_tail = new Node<T>();

		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~LinkedList() 
	{
		while (_size) 
		{
			pop_back();
		}

		delete _head;
		delete _tail;
	}

public:
	void push_back(const T& data)
	{
		AddNode(_tail, data);
	}

	void pop_back()
	{
		DeleteNode(_tail);
	}

	bool empty() 
	{
		return _size == 0;
	}

	int size() 
	{
		return _size;
	}

	using iterator = Iterator<T>;

	iterator begin() 
	{
		return iterator(_head->_next);
	}

	iterator end() 
	{
		return iterator(_tail->_prev);
	}

	iterator erase(iterator iter) 
	{
		Node<T>* nextNode = DeleteNode(iter._node);
		return iterator(nextNode);
	}

	iterator insert(iterator nextiter, const T& data) 
	{
		Node<T>* node = AddNode(iter._node, data);
		return iterator(node);
	}

private:
	Node<T>* AddNode(Node<T>* backNode, const T& data)
	{
		Node<T>* newNode = new Node<T>(data);
		Node<T>* frontNode = backNode->_prev;

		newNode->_next = backNode;
		backNode->_prev = newNode;

		newNode->_prev = frontNode;
		frontNode->_next = newNode;

		_size++;
		return newNode;
	}

	Node<T>* DeleteNode(Node<T>* deleteNode) 
	{
		Node<T>* backNode = deleteNode->_next;
		Node<T>* frontNode = deleteNode->_prev;

		frontNode->_next = backNode;
		backNode->_prev = frontNode;

		delete delteNode;

		_size--;
		return backNode;
	}

private:
	Node<T>* _head;
	Node<T>* _tail;
	int _size;
};