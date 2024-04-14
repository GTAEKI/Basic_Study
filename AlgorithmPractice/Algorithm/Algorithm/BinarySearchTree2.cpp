#include "BinarySearchTree2.h"

void BinarySearchTree2::insert(int key)
{
	if (_root == nullptr) 
	{
		_root = new Node();
		_root->key = key;
		return;
	}

	Node* newNode = new Node();
	newNode->key = key;
	Node* parent = new Node();
	Node* node = _root;

	while (node) 
	{
		
	}

}
