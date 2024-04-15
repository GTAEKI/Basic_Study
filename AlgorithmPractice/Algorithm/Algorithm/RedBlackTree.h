#pragma once

enum class Color
{
	Red = 0,
	Black = 1,
};

struct Node
{
	Node() : 
		parent(nullptr),
		left(nullptr),
		right(nullptr),
		key(0),
		color(Color::Black)
	{
	
	}

	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
	Color color = Color::Black;
};

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();
	
	void Insert(int key);
	void InsertFixup(Node* node);

	void Delete(int key);
	void Delete(Node* node);
	void DeleteFixup(Node* node);

	void Replace(Node* u, Node* v);
	void Print();
	void Print(Node* node, int x, int y);

	Node* Search(Node* node, int key);

	Node* Min(Node* node); // 가장 작은수
	Node* Max(Node* node); // 가장 큰 수
	Node* Next(Node* node); // 내 다음 크기 수

	// Red-Black Tree
	void LeftRotate(Node* node);
	void RightRotate(Node* node);

private:
	Node* _root = nullptr;
	Node* _nil = nullptr; // 없음을 나타내는 일종의 nullptr역할이므로 하나만 만들어서 가리키게 한다.
};

