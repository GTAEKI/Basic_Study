#include "BinarySearchTree2.h"

void BinarySearchTree2::insert(int key)
{

	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr) 
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;

	while (node) 
	{
		parent = node;
		if (key < node->key)
		{
			node = node->left;
		}
		else
			node = node->right;
	}

	newNode->parent = parent;

	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree2::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr)
		_root = v;
	else if (u->parent->right == u)
		u->parent->right = v;
	else if (u->parent->left == u)
		u->parent->left = v;

	if (v)
		v->parent = u->parent;

	delete u;
}

Node* BinarySearchTree2::Search(int key)
{
	Node* newNode = Search(_root, key);
	return newNode;
}

Node* BinarySearchTree2::Search(Node* node, int key)
{
	if (node == nullptr && node->key == key) return node;

	if (node->key < key)
		Search(node->right, key);
	else
		Search(node->left, key);
}

void BinarySearchTree2::Delete(int key)
{
	Node* deleteNode = Search(key);
	Delete(deleteNode);
}

void BinarySearchTree2::Delete(Node* node)
{
	if (node == nullptr) return;

	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	else 
	{
		Node* nextNode = Next(node);
		node->key = nextNode->key;
		Delete(nextNode);
	}

}

Node* BinarySearchTree2::Min(Node* node)
{
	while (node->left)
		node = node->left;
	return node;
}

Node* BinarySearchTree2::Max(Node* node)
{
	while (node->right)
		node = node->right;
	return node;
}

Node* BinarySearchTree2::Next(Node* node)
{
	if (node->right)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent && node == parent->right) 
	{
		node = parent;
		parent = node->parent;
	}

	return parent;
}
