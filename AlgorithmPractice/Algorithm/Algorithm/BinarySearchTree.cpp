#include "BinarySearchTree.h"
#include <iostream>
#include <windows.h>
using namespace std;
//
//void SetCursorPosition(int x, int y)
//{
//	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
//	::SetConsoleCursorPosition(output, pos);
//}

// 구현하는 방법이 굉장히 만다.
void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr) // 데이터가 아무것도 없는 상황
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr; // 어디에 추가해줄것인지

	// node가 없으면 탈출
	while (node) 
	{
		parent = node;
		if (key < node->key) // 왼쪽 오른쪽
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;

	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr) return;

	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	else 
	{
		// 다음 데이터 찾기
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

// u 서브트리를 v 서브트리로 교체
// 그리고 delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr) // 처음부터 root노드였다는 뜻
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v)
		v->parent = u->parent;

	delete u;
}

// 데이터 출력함수, 중위 순회
void BinarySearchTree::Print_Inorder(Node* node)
{
	if (node == nullptr) return;

	// 내 현재노드(중간노드_parent)가 언제 체크하는지에 따른 순회방식
	// 전위 순회 (preorder traverse)

	// 중위 순회 (inorder)
	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);

	// 후위 순회 (postorder)
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr)
		return;

	//SetCursorPosition(x, y);
	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr) return node;

	if (key == node->key) return node;
	else if (key < node->key) return Search(node->left, key);
	else if (key > node->key) return Search(node->right, key);
}

Node* BinarySearchTree::Search2(Node* node, int key)
{
	while (node && key != node->key) 
	{
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

Node* BinarySearchTree::Min(Node* node)
{
	/*if (node == nullptr) return node;
	if (node->left) return Min(node->left);*/

	while (node->left)
		node = node->left;
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	/*if (node == nullptr) return node;
	if (node->right) return Max(node->right);*/

	while (node->right)
		node = node->right;
	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node->right)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent && node == parent->right) 
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}
