#pragma once

struct Node 
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {}; // key value 따로 저장도 가능하지만, 일단 구조 보자

	// 위 방식을 nullptr로 관리하는 방식이고
	// 아래 bool을 추가하여 더미 노드로 관리하기도 한다.
	// bool external;
};

class BinarySearchTree
{
public:
	// key를 건네주고 key값에 해당하는 노드를 만들어서 추가해주는 함수
	void Insert(int key);

	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u, Node* v);

	void Print() { Print(_root, 10, 0); }
	void Print(Node* node, int x, int y);

	// 순서를 정해주어야 한다. 어떤식으로 데이터를 출력할 것인지
	void Print_Inorder() { Print_Inorder(_root);} //실질적 방식
	void Print_Inorder(Node* node);

	Node* Search(Node* node, int key);
	Node* Search2(Node* node, int key); // 성능적으로는 우세

	Node* Min(Node* node); // 가장 작은수
	Node* Max(Node* node); // 가장 큰 수
	Node* Next(Node* node); // 내 다음 크기 수

private:
	Node* _root = nullptr;
};

