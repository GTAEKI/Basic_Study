#pragma once

#include<iostream>
#include<vector>
#include<queue>
#include<list>
using namespace std;

struct Vertex 
{
	//int data;
};

vector<Vertex> vertices;
vector<vector<int>>adjacentMatrix;

void CreateGraph() 
{
	vertices.resize(6);
	adjacentMatrix = vector<vector<int>>(6, vector<int>(6, -1));

	adjacentMatrix[0][1] = 15;
	adjacentMatrix[0][3] = 35;
	adjacentMatrix[1][0] = 15;
	adjacentMatrix[1][2] = 5;
	adjacentMatrix[1][3] = 10;
	adjacentMatrix[3][4] = 5;
	adjacentMatrix[5][4] = 5;
}

void Dijkstra(int here) 
{
	struct VertexCost 
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered;

	vector<int> best(6, INT32_MAX);
	vector<int> parent(6, -1);

	discovered.push_back(VertexCost{ here,0 });
	best[here] = 0;
	parent[here] = here;

	int count = 0;
	while (discovered.empty() == false) 
	{
		count++;

		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++) 
		{
			if (it->cost < bestCost) 
			{
				bestCost = it->cost; 
				bestIt = it;
			}
		}

		int cost = bestIt->cost;	
		here = bestIt->vertex;
		discovered.erase(bestIt);

		if (best[here] < cost) continue;

		for (int there = 0; there < 6; there++) 
		{
			if (adjacentMatrix[here][there] == -1) continue;

			int nextCost = best[here] + adjacentMatrix[here][there];
			if (nextCost >= best[there]) continue;

			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}

}