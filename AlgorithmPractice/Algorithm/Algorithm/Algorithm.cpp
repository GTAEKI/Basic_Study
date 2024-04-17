#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
using namespace std;

class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	}

	// 니 대장이 누구니?
	int Find(int u)
	{
		if (u == _parent[u])
			return u;

		return _parent[u] = Find(_parent[u]); // 대장을 찾았다면, 바로 부모를 대장으로 변경, 타고타고를 없애주는 최적화
	}

	// u와 v를 합친다.
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v) return; // 같은 대장

		if (_rank[u] > _rank[v])
			swap(u, v);

		// 여기까지 오면 rank[u] <= rank[v] 가 보장됨

		_parent[u] = v; // 이진트리는 아닐수있음

		if (_rank[u] == _rank[v])
			_rank[v]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;

};

struct Vertex 
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent; // 인접 행렬

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

// 크루스칼이 뱉어주는 값은 최종적으로 계산한 코스트의 합을 뱉어줄 것인데
// 어떠한 간선들로 이루어져야 하는지 골라줘야 하니 만든 스트럭트
struct CostEdge 
{
	int cost;
	int u;
	int v;

	bool operator<(CostEdge& other)  // 비교를 위함
	{
		return cost < other.cost;
	}
};

int Kruskal(vector<CostEdge>& selected)  // 연결된 애들은 selected에 반환, 최종 코스트는 int에 return
{
	int ret = 0;

	selected.clear();

	vector<CostEdge> edges;

	for (int u = 0; u < adjacent.size(); u++)
	{
		for (int v = 0; v < adjacent[u].size(); v++)
		{
			if (u > v) // 양방향 간선 추가 방지
				continue;

			int cost = adjacent[u][v];
			if (cost == -1)
				continue;

			edges.push_back(CostEdge{ cost, u, v });
		}
	}

	std::sort(edges.begin(), edges.end());

	DisjointSet sets(vertices.size()); // 처음에는 다 각기 독립적인 그룹이 될것인데

	for (CostEdge& edge : edges) 
	{
		//같은 그룹이면 스킵 (안그러면 사이클 발생)
		if (sets.Find(edge.u) == sets.Find(edge.v))
			continue;

		// 두 그룹을 합친다
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

