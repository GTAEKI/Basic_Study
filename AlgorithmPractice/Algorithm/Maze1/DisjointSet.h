#pragma once

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
