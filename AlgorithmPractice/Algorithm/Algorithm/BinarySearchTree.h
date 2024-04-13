#pragma once

struct Node 
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {}; // key value 따로 저장도 가능하지만, 일단 구조 보자
};

class BinarySearchTree
{
public:
	void Insert(int key);


private:
	Node* _root = nullptr;
};

