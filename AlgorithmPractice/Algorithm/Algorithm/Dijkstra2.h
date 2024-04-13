#pragma once

#include<iostream>
#include<vector>
#include<list>
using namespace std;

struct Vertex
{
	//int _data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateMap() 
{
	vertices = vector<Vertex>(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijkstra2(int here) 
{
	struct VertexCost 
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered;
	vector<int> best = vector<int>(6,INT32_MAX);
	vector<int> parent = vector<int>(6);

	discovered.push_back(VertexCost{ here, 0 });
	best[here] = 0;
	parent[here] = 0;

	while (discovered.empty() == false)
	{
		list<VertexCost>::iterator bestIter;
		int bestCost = INT32_MAX;
		for (auto iter = discovered.begin(); iter != discovered.end(); iter++)
		{
			if (iter->cost < bestCost)
			{
				bestIter = iter;
				bestCost = iter->cost;
			}
		}

		here = bestIter->vertex;
		discovered.erase(bestIter);

		if (best[here] < bestCost) continue;

		for (int there = 0; there < vertices.size(); there++) 
		{
			if (adjacent[here][there] == -1) continue;

			int newCost = best[here] + adjacent[here][there];
			if (best[there] < newCost) continue;

			discovered.push_back(VertexCost{ there,newCost });
			best[there] = newCost;
			parent[there] = here;
		}
	}
}