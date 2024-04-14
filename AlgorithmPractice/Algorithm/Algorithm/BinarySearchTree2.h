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

	void Replace(Node* u, Node* v);

	Node* Search(int key);
	Node* Search(Node* node, int key);

	void Delete(int key);
	void Delete(Node* node);

	Node* Min(Node* node);
	Node* Max(Node* node);
	Node* Next(Node* node);

private:
	Node* _root;
};

