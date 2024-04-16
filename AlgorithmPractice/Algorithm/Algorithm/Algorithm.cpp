#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
using namespace std;

// 상호 배타적 집합(Disjoint Set)
// -> 유니온 - 파인드 Union-Find (합치기 - 찾기)

// 게임회사에서 프로그래머로 일하고 있는데
// 오늘부터 Lineage Battleground (혼종!)
// 혈맹전 + 서바이벌
// 1인 팀 1000명 (팀 id 0~999)
// 동맹(1번팀 + 2번팀 = 1번팀)

// 트리 구조를 이용한 상호 배타적 집합의 표현
// [0] [1] [2] [3] [4] [5]
struct Node 
{
	Node* leader;
};

// 조직 폭력배 구조도
// [1]  [3]               [3]
// [2]  [4][5]   ->    [4][5][1]
//      [0]			   [0]	 [2]

// 시간 복잡도 : 트리의 높이에 비례한 시간이 걸림
// 그런데 균형잡힌 트리가 아니기 때문에 트리 모양이 어떻게 될지 알 수가 없음
// Find가 재귀이기때문에 한쪽으로만 쭈욱 늘어지게 되면 빠르게 써칭하는 역할을 잃어버린다.
class NaiveDisjointSet // 순진하게구현
{
public:
	NaiveDisjointSet(int n) : _parent(n) 
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	}

	// 니 대장이 누구니?
	int Find(int u) 
	{
		if (u == _parent[u])
			return u;

		return Find(_parent[u]);
	}

	// u와 v를 합친다 (일단 u가 v 밑으로)
	void Merge(int u, int v) 
	{
		u = Find(u);
		v = Find(v);

		if (u == v) return; // 같은 대장

		_parent[u] = v; // 이진트리는 아닐수있음
	}

private:
	vector<int> _parent;

};

// 예방 방법 1 (Union - By - Rank : 랭크에 의한 합치기 최적화, 여기서 랭크는 높이를 말한다.)
// 트리가 한쪽으로 기우는 문제 해결
// 트리를 합칠 때, 항상 [높이가 낮은 트리]를 [높이가 높은 트리] 밑으로 넣는게 어떨까?

// 시간 복잡도 O(Ackermann(n)) = O(1)
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

#pragma endregion

	DisjointSet teams(1000);

	teams.Merge(10, 1);

	int teamId = teams.Find(1);
	int teamId2 = teams.Find(10);

	teams.Merge(3, 2);
	int teamId3 = teams.Find(3);
	int teamId4 = teams.Find(2);

	teams.Merge(1, 3);
	int teamId5 = teams.Find(1);
	int teamId6 = teams.Find(3);
	

	return 0;
}

