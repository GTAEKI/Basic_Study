#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
using namespace std;

class DisjoinSet 
{
public:
	DisjoinSet(int n) :_parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++) 
		{
			_parent[i] = i;
		}
	}

	int Find(int u) 
	{
		if (u == _parent[u])
			return u;

		return _parent[u] = Find(_parent[u]);
	}

	void Merge(int u, int v) 
	{
		u = Find(u);
		v = Find(v);

		if (u == v) // 부모가 같다면 병합 x
			return;

		if (_rank[u] > _rank[v])
			swap(u, v);

		_parent[u] = v;

		if (_rank[u] == _rank[v])
			_rank[v]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

struct Vertex 
{
	//int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateGraph() 
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = adjacent[1][0] = 15;
	adjacent[0][3] = adjacent[3][0] = 35;
	adjacent[1][2] = adjacent[2][1] = 5;
	adjacent[1][3] = adjacent[3][1] = 10;
	adjacent[3][4] = adjacent[4][3] = 5;
	adjacent[3][5] = adjacent[5][3] = 10;
	adjacent[5][4] = adjacent[4][5] = 5;
}

struct CostEdge 
{
	int cost;
	int u;
	int v;

	bool operator <(const CostEdge& other)
	{
		return cost < other.cost;
	}
};

int Kruskal(vector<CostEdge>& selected)
{
	int ret = 0;

	selected.clear();

	vector<CostEdge> edges;

	for (int u = 0; u < adjacent.size(); u++) 
	{
		for (int v = 0; v < adjacent[u].size(); v++) 
		{
			if (u > v) continue;

			int cost = adjacent[u][v];
			if (cost == -1) continue;

			edges.push_back(CostEdge{ cost, u, v });
		}
	}

	std::sort(edges.begin(), edges.end());

	DisjoinSet sets(vertices.size());

	for (CostEdge& edge : edges) 
	{
		if (sets.Find(edge.u) == sets.Find(edge.v))
			continue;

		sets.Merge(edge.u, edge.v);
		selected.push_back(edge);
		ret += edge.cost;
	}

	return ret;
}

int main()
{
#pragma region 실행부
	/*Vector<int> v;

	v.push_back(1);
	v.push_back(3);
	v.push_back(5);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << "\n";
	}

	v.pop_back();
	v.pop_back();

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << "\n";
	}

	cout << v.empty();*/


	/*RedBlackTree bst;

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
	this_thread::sleep_for(1s);*/

	// sort 실행부
	/*vector<int> v;

	srand(time(0));

	for (int i = 0; i < 50; i++)
	{
		int randValue = rand() % 100;
		v.push_back(randValue);
	}*/

	//BubbleSort(v);
	//SelectionSort(v);
	//InsertionSort(v);
	//HeapSort(v);
	//MergeSort2(v, 0, v.size() - 1);
	//HeapSort2(v);
	//QuickSort3(v, 0, v.size() - 1);

	// Disjoint Set
	/*DisjointSet teams(1000);

	teams.Merge(10, 1);

	int teamId = teams.Find(1);
	int teamId2 = teams.Find(10);

	teams.Merge(3, 2);
	int teamId3 = teams.Find(3);
	int teamId4 = teams.Find(2);

	teams.Merge(1, 3);
	int teamId5 = teams.Find(1);
	int teamId6 = teams.Find(3);*/
#pragma endregion
	CreateGraph();

	vector<CostEdge> selected;

	int cost = Kruskal(selected);
	


	return 0;
}

