#pragma once

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Vertex 
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacentList;
vector<vector<int>> adjacentMatrix;
vector<bool> visited;
vector<bool> discovered;

void CreateGraph() 
{
	vertices.resize(6);
	adjacentList[0].push_back(1);
	adjacentList[0].push_back(3);
	adjacentList[1].push_back(0);
	adjacentList[1].push_back(2);
	adjacentList[1].push_back(3);
	adjacentList[3].push_back(4);
	adjacentList[5].push_back(4);

	adjacentMatrix = vector < vector<int>>
	{
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
	};
}

void Dfs(int here) 
{
	visited[here] = true;

	/*for (int i = 0; i < adjacentList[here].size(); i++) 
	{
		int there = adjacentList[here][i];
		if (visited[there] == false) 
		{
			Dfs(there);
		}
	}*/

	for (int there = 0; there < vertices.size(); there++) 
	{
		if (adjacentMatrix[here][there] == 0)
			continue;

		if (visited[there] == false)
			Dfs(there);
	}
}

void Bfs(int here) 
{
	vector<int> parent(6, -1);
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

		/*for (int there : adjacentList[here]) 
		{
			if (visited[there] == false) 
			{
				q.push(there);
				visited[there] = true;

				parent[there] = here;
				distance[there] = distance[here] + 1;
			}
		}*/

		for (int there = 0; there < vertices.size(); there++)
		{
			if (adjacentMatrix[here][there] == 0) continue;

			if (visited[there] == false)
			{
				q.push(there);
				visited[there] = true;

				parent[there] = here;
				distance[there] = distance[here] + 1;
			}
		}
	}
}

void SearchAll() 
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < vertices.size(); i++) 
	{
		if (visited[i] == false) 
		{
			//Dfs(i);
			Bfs(i);
		}
	}
}