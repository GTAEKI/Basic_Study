#pragma once

template <typename T>
class Node 
{
public:
	Node() :_next(nullptr), _prev(nullptr), _data(T())
	{
	
	}

	Node(const T& value) : _next(nullptr), _prev(nullptr), _data(value)
	{
	
	}

public:
	Node* _next;
	Node* _prev;
	T _data;
};

template <typename T>
class Iterator 
{
public:
	Iterator() :_node(nullptr)
	{
	
	}

	Iterator(Node<T>* node) : _node(node)
	{
	
	}

public:
	// i++
	Iterator operator++(int) 
	{
		//Node<T> newNode = *_node;
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