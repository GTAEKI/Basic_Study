#include<iostream>
#include<vector>
#include<queue>
#include<list>
using namespace std;

// 트리
// 계층적 구조를 갖는 데이터를 표현하기 위한 자료구조

using NodeRef = shared_ptr<struct Node>;

struct Node
{
	Node() { }
	Node(const string& data) : data(data) { }

	string data;
	vector<NodeRef> children;
};

NodeRef CreateTree()
{
	NodeRef root = make_shared<Node>("R1 개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("전투");
			node->children.push_back(leaf);
			{
				NodeRef leaf2 = make_shared<Node>("임시노드");
				leaf->children.push_back(leaf2);
			}
		}

		{
			NodeRef leaf = make_shared<Node>("경제");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서버");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("클라");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->children.push_back(leaf);
		}
	} 
	{
		NodeRef node = make_shared<Node>("아트팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("캐릭터");
			node->children.push_back(leaf);
		}
	}

	return root;
}

// 트리의 재귀적 특성
void PrintTree(NodeRef root, int depth)
{
	for (int i = 0; i < depth; i++)
		cout << "-";
	cout << root->data << endl;

	for (NodeRef& child : root->children)
		PrintTree(child,depth + 1);
}

// 깊이 (depth) : 루트에서 어떤 노드에 도달하기 위해 거쳐야 하는 간선의 수 (그 노드는 몇 층?)
// 높이 (height) : 트리의 가장 깊숙히 있는 노드의 깊이 (트리의 총 높이 max(depth))


int GetHeight(NodeRef root) 
{
	int height = 1;

	for (NodeRef& child : root->children) 
	{
		height = max(height , GetHeight(child) + 1);
	}

	return height;
}

//// 정답 보기전 직접 구현 코드
//int GetHeight(NodeRef root, int depth) 
//{
//	int maxDepth = depth;
//
//	for (NodeRef& child : root->children) 
//	{
//		int temp = GetHeight(child, depth+1);
//		maxDepth = max(temp, maxDepth);
//	}
//	return maxDepth;
//}

int main()
{
	NodeRef root = CreateTree();

	PrintTree(root, 0);
	int a = GetHeight(root);

	cout << "트리의 높이는: " << a << "\n";

	return 0;
}