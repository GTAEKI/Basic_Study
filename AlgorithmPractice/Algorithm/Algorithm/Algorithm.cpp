#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include "RedBlackTree.h"
using namespace std;

#include<thread>

// 오늘의 주제 : 이진 탐색 트리



int main()
{
	RedBlackTree bst;

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(10);
	bst.Print();
	this_thread::sleep_for(1s);

	return 0;
}