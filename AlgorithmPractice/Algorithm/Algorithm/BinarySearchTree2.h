#pragma once

struct Node 
{
	Node* parent;
	Node* left;
	Node* right;

	int key = {};
};

class BinarySearchTree2
{
public:
	void insert(int key);

private:
	Node* _root;
};

