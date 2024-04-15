#include "RedBlackTree.h"
#include <iostream>
#include <windows.h>
using namespace std;

enum class ConsoleColor
{
	// 실질적으로 나중에 사용할 API와 연관이 있다.
	// 콘솔에 사용할 색
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

RedBlackTree::RedBlackTree()
{
	_nil = new Node(); //Black
	_root = _nil;
}

RedBlackTree::~RedBlackTree()
{
	delete _nil;
}

// 구현하는 방법이 굉장히 만다.
void RedBlackTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	Node* node = _root;
	Node* parent = _nil; // 어디에 추가해줄것인지

	// node가 없으면 탈출
	while (node != _nil)
	{
		parent = node;
		if (key < node->key) // 왼쪽 오른쪽
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;

	if (parent == _nil)
		_root = newNode;
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	// 검사
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;

	InsertFixup(newNode);

}

void RedBlackTree::InsertFixup(Node* node)
{
	// 규칙 // 삼촌의 색상을 확인해야한다. (조부모의 반대쪽 자식)
	// 1) parent = red, uncle = red
	//	-> 부모와 삼촌 색상을 black으로
	//  -> 조부모의 색상을 red로 변경하면 끝
	// 2) parent = red, uncle = black (triangle)
	//	-> 적당한 회전을 통해 case3 으로 변경
	// 3) parent = red, uncle = black (list)
	//	-> 색상 변경
	// 부모가 black이라면 문제될것이 없다는 가정

	while (node->parent->color == Color::Red) // 부모가 red인가?
	{
		if (node->parent == node->parent->parent->left) // 부모는 조부모의 왼쪽인가?
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red) // 1번 케이스
			{
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				node->parent->parent->color = Color::Red;

				node = node->parent->parent; // 다시 체크하기 위한 코드
			}
			else // 2번 or 3번 케이스
			{
				// 2번 -> pp , p , node 가 ㄱ자 (트라이앵글)
				// 3번 -> pp , p , node 가 / 자 (리스트)
				if (node == node->parent->right) // Triangle 타입(2번 케이스)
				{
					// Triangle이라면 list처럼 펴주어야 한다.
					// left rotate를 해준다.
					node = node->parent;
					LeftRotate(node);
				}

				// List 타입 (3번 케이스)
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}
		}
		else // 부모는 조부모의 오른쪽인가?
		{
			Node* uncle = node->parent->parent->left;
			
			if (uncle->color == Color::Red) 
			{
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				node->parent->parent->color = Color::Red;

				node = node->parent->parent;
			}
			else 
			{
				if (node == node->parent->left) 
				{
					node = node->parent;
					RightRotate(node);
				}

				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}

	_root->color = Color::Black;
}

void RedBlackTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void RedBlackTree::Delete(Node* node)
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
void RedBlackTree::Replace(Node* u, Node* v)
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

void RedBlackTree::Print(Node* node, int x, int y)
{
	if (node == _nil)
		return;

	SetCursorPosition(x, y);

	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);

	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

Node* RedBlackTree::Search(Node* node, int key)
{
	if (node == _nil || key == node->key) return node;

	if (key < node->key) return Search(node->left, key);
	else if (key > node->key) return Search(node->right, key);
}

Node* RedBlackTree::Min(Node* node)
{
	while (node->left != _nil)
		node = node->left;
	return node;
}

Node* RedBlackTree::Max(Node* node)
{
	while (node->right != _nil)
		node = node->right;
	return node;
}

Node* RedBlackTree::Next(Node* node)
{
	if (node->right != _nil)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

void RedBlackTree::LeftRotate(Node* x)
{
	Node* y = x->right;

	x->right = y->left;

	if(y->left != _nil)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == _nil)
		_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

void RedBlackTree::RightRotate(Node* y)
{
	Node* x = y->left;

	y->left = x->right;

	if (x->right != _nil)
		x->right->parent = y;
	
	x->parent = y->parent;

	if (y->parent == _nil)
		_root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}
