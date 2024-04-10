#pragma once

#include "Base.h"

template <typename T>
class LinkedList 
{
public:
	LinkedList():_size(0)
	{
		_head = new Node<T>();
		_tail = new Node<T>();
		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~LinkedList() 
	{
		while (_size>0) 
		{
			pop_back();
		}
		delete _head;
		delete _tail;
	}

public:
	using iterator = Iterator<T>;

	void push_back(const T& value) 
	{
		AddNode(_tail, value);
	}

	void pop_back() 
	{
		RemoveNode(_tail->_prev);
	}

	void push_front(const T& value) 
	{
		AddNode(_head->_next, value);
	}

	iterator insert(iterator iter, const T& value)
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
	Node<T>* AddNode(Node<T>* nextNode, const T& data) 
	{
		Node<T>* newNode = new Node<T>(data);
		Node<T>* prevNode = nextNode->_prev;

		newNode->_next = nextNode;
		nextNode->_prev = newNode;

		newNode->_prev = prevNode;
		prevNode->_next = newNode;

		_size++;
		return newNode;
	}

	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* nextNode = node->_next;
		Node<T>* prevNode = node->_prev;

		nextNode->_prev = prevNode;
		prevNode->_next = nextNode;

		delete node;

		_size--;

		return nextNode;
	}

private:
	Node<T>* _head;
	Node<T>* _tail;
	int _size;
};