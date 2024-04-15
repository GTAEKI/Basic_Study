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

void ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
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

// 먼저 BST 삭제 실행

void RedBlackTree::Delete(Node* node)
{
	if (node == _nil) return;

	if (node->left == _nil)
	{
		Color color = node->color;
		Node* right = node->right;
		Replace(node, node->right);

		if (color == Color::Black) // 블랙일때만 실행해주면 됨
			DeleteFixup(right);
	}
	else if (node->right == _nil)
	{
		Color color = node->color;
		Node* right = node->left;
		Replace(node, node->left);

		if (color == Color::Black)
			DeleteFixup(right);
	}
	else
	{
		// 다음 데이터 찾기
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}


}

// 먼저 BST 삭제 실행
// - Case1) 삭제할 노드가 Red-> 그냥 삭제! 끝!
// - Case2) root가 DB -> 그냥 추가 Black 삭제! 끝!
// - Case3) DB의 sibling 노드가 Red
// -- s = black, p = red (s <-> p 색상 교환)
// -- DB 방향으로 rotate(p)
// -- goto other case
// - Case4) DB의 sibling 노드가 Black && sibling의 양쪽 자식도 Black
// -- 추가 Black을 parent에게 이전
// --- p가 Red이면 Black 됨
// --- p가 Black이면 DB 됨
// s = red
// p를 대상으로 알고리즘 이어서 실행 (DB가 여전히 존재한다면)
// - Case5) DB의 sibling 노드가 Black && sibling의 near child = red, far child = black
// -- s <-> near 색상 교환
// -- far 방향으로 rotate(s)
// -- goto case 6
// - Case 6) DB의 sibling 노드가 Black && sibling의 far child = red
// -- p <-> s 색상 교환
// -- far = black
// -- rotate(p) (DB 방향으로)
// -- 추가 Black 제거
void RedBlackTree::DeleteFixup(Node* node)
{
	Node* x = node; // 삭제한 노드일 수도 삭제한 이후 이동한 뒤 붙은 노드 일수도

	// [Case1][Case2]
	while (x != _root && x->color == Color::Black)
	{
		if (x == x->parent->left)
		{
			// [Case3]
			Node* s = x->parent->right;
			if (s->color == Color::Red)
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;

				LeftRotate(x->parent);
				s = x->parent->right;
			}

			// [Case4]
			if (s->left->color == Color::Black && s->right->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}
			else
			{
				// [Case5]
				if (s->right->color == Color::Black)
				{
					s->left->color = Color::Black;
					s->color = Color::Red;
					RightRotate(s);
					s = x->parent->right;
				}

				//[Case 6]
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->right->color = Color::Black;
				LeftRotate(x->parent);
				x = _root;
			}
		}
		else
		{
			// [Case3]
			Node* s = x->parent->left;
			if (s->color == Color::Red)
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;

				RightRotate(x->parent);
				s = x->parent->left;
			}

			// [Case4]
			if (s->right->color == Color::Black && s->left->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}
			else
			{
				// [Case5]
				if (s->left->color == Color::Black)
				{
					s->right->color = Color::Black;
					s->color = Color::Red;
					LeftRotate(s);
					s = x->parent->left;
				}

				//[Case 6]
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->left->color = Color::Black;
				RightRotate(x->parent);
				x = _root;
			}

		}
	}

	x->color = Color::Black;
}

// u 서브트리를 v 서브트리로 교체
// 그리고 delete u
void RedBlackTree::Replace(Node* u, Node* v)
{
	if (u->parent == _nil) // 처음부터 root노드였다는 뜻
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	//if (v) -> 이제는 null체크가 필요없음
	v->parent = u->parent;

	delete u;
}

void RedBlackTree::Print()
{
	::system("cls"); // 콘솔을 클리어 해달라는 뜻
	ShowConsoleCursor(false); // 커서 깜빡임 제거
	Print(_root, 10, 0);
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

	if (y->left != _nil)
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
