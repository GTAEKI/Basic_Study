#pragma once

#include<iostream>
#include<vector>
using namespace std;

// DFS (Depth First Search) 깊이 우선 탐색
// BFS (Breadth First Search) 너비 우선 탐색

struct Vertex
{
	//int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent; // 인접 리스트
vector<vector<int>> adjacent2; // 인접 행렬
vector<bool> visited;
vector<bool> discovered;


void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	//인접 리스트
	// adjacent[0] = {1,3};
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);

	// 인접 행렬
	adjacent2 = vector<vector<int>>
	{
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
	};
}

// DFS
void Dfs(int here)
{
	// 방문!
	visited[here] = true;

	////인접 리스트 ver
	// 모든 인접 정점을 순회
	//for (int i = 0; i < adjacent[here].size(); i++) 
	//{
	//	int there = adjacent[here][i];
	//	if (visited[there] == false) 
	//	{
	//		Dfs(there);
	//	}
	//}

	// 인접 행렬 ver
	// 모든 인접 정점을 순회
	for (int there = 0; there < 6; there++)
	{
		if (adjacent2[here][there] == 0)
			continue;

		if (visited[there] == false)
		{
			Dfs(there);
		}
	}
}

void Bfs(int here)
{
	// 누구에 의해 발견 되었는지?
	vector<int> parent(6, -1);
	// 시작점에서 얼만큼 떨어져 있는지?
	vector<int> distance(6, -1);

	queue<int> q;
	q.push(here);
	visited[here] = true;

	parent[here] = here;
	distance[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << "Visited : " << here << endl;

		// 인접 리스트
		//for (int there: adjacent[here])
		// 인접 행렬
		for (int there = 0; there < 6; there++)
		{
			//인접 행렬
			if (adjacent2[here][there] == 0) continue;

			if (visited[there] == false)
			{
				q.push(there);
				visited[there] = true;

				parent[there] = here;
				distance[there] = distance[here] + 1;
			}
		}
	}
	int a = 0; // 중단점
}

void SearchAll()
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < 6; i++)
	{
		if (visited[i] == false)
		{
			//Dfs(i);
			Bfs(i);
		}
	}
}