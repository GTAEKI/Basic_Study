#include "BinarySearchTree.h"

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr) 
	{
		_root = newNode;
		return;
	}
}
