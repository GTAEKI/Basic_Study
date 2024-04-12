#include<iostream>
#include<vector>
#include<queue>
#include<list>
using namespace std;

// BFS의 한계
// edge에 가중치가 없는 경우에서는 문제가 없었다.
// 그런데 가중치가 있을 경우에는 문제가 생긴다. (지하철 노선도 : 걸리는 시간과 거리가 다름)
// 실질적인 모델링에서 오류가 생길 수 있음
// 
// 내가 먼저 방문하는곳이 BFS라면
// 가중치까지 포함해서 기록을 남기는것이 다익스트라

// 아래 코드는 좀 느리게 동작하는 다익스트라이다.
// 모든 케이스를 리스트로 관리하고 순차적으로 제일 좋은 케이스를 찾는 것 자체가 굉장히 비효율적일것
// 사실 우리에게 필요한것은 리스트같은 자료구조가 아닌 제일 좋은 후보를 뽑아줄 수 잇는 자료구조를 운영한다면
// 모든 애들을 스캔하여 뽑아올 필요가 없고 더 효율적으로 코드를 할 수 있을것이다.
// 가장 효율적으로 처리할 수 있는 자료구조가 있는데, 그것이 우선순위 큐(Priority Queue)이다.
// Priority Queue는 그냥 큐와는 다르게 넣은 순서대로가 아닌 우선순위가 있어서 넣어준 애들중 베스트케이스 하나를 빠르게 뽑아준다.
// 다익스트라에서는 Priority Qeuue가 궁합이 굉장히 잘 맞을것이다.
// 기본적으로 STL에도 구현은 되어있으나 어떤 원리로 동작하는지 숙지하기 위해 공부를 해야한다.

struct Vertex 
{
	// int data;
};

//vector < vector <pair<int,int>>> v(6);
vector<Vertex> vertices;
vector<vector<int>>adjacent; //인접 행렬

void CreateGraph() 
{
	//v[0].push_back({ 1,15 });
	//v[0].push_back({ 3,35 });
	//v[1].push_back({ 0,15 });
	//v[1].push_back({ 2,5 });
	//v[1].push_back({ 3,10 });
	//v[3].push_back({ 3,10 });
	//v[5].push_back({ 4,5 });

	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
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
	vector<int> best(vertices.size(), INT32_MAX);
	vector<int> parent(vertices.size());

	discovered.push_back(VertexCost{here, 0});
	best[here] = 0;
	parent[here] = 0;

	while (discovered.empty() == false) 
	{
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;
		for (auto iter = discovered.begin(); iter != discovered.end(); iter++) 
		{
			if (iter->cost < bestCost) 
			{
				bestCost = iter->cost;
				bestIt = iter;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		//if (best[here] < cost) continue;

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
	int a = 3;
}



void Dijkstra1(int here) 
{
	struct VertexCost 
	{
		int vertex;
		int cost;
	};

	list<VertexCost> visited;
	vector<int> best(vertices.size(), INT32_MAX); // 최고 값
	vector<int> parent(vertices.size()); // 부모값

	visited.push_back(VertexCost{here,0});
	best[here] = 0;
	parent[here] = here;

	while (visited.empty() == false) 
	{
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;
		
		for (auto iter = visited.begin(); iter != visited.end(); iter++) 
		{
			if (iter->cost < bestCost) 
			{
				bestCost = iter->cost;
				bestIt = iter;
			}
		}

		here = bestIt->vertex;
		visited.erase(bestIt);


		if (best[here] < bestCost) // 더 빠른경로가 있었다면
			continue;

		for (int there = 0; there < vertices.size(); there++) 
		{
			if (adjacent[here][there] == -1) continue;

			int newCost = best[here] + adjacent[here][there];
			if (best[there] < newCost) continue;

			visited.push_back(VertexCost{ there, newCost });
			best[there] = newCost;
			parent[there] = here;
		}
	}
}


void Dijikstra(int here) 
{
	// std::pair<int,int>
	struct VertexCost 
	{
		int vertex;
		int cost;
	};

	// 발견 목록 -> bfs에서는 큐(먼저 찾은애가 반드시 먼저 방문이 되어 사용하였고
	// 이제는 먼저 발견한 애가 꼭 먼저 방문해야한다는 보장이 없기에 큐 말고 리스트나 다른 자료구조로 구현
	// 추후에는 좀 더 효율적으로 관리 예정
	list<VertexCost> discovered;
	
	// 각 정점별로 지금까지 발견한 최소 거리 -> 우리가 처음 3번 정점 기준으로 뒤늦게 다른 기준으로 갱신될 필요가 있을것이다. 
	// 실질적으로 내가 찾으려는 거리를 추적하기위한 변수
	vector<int> best(6, INT32_MAX); 
	vector<int> parent(6, -1);


	discovered.push_back(VertexCost{ here, 0 });
	best[here] = 0;
	parent[here] = here;


	int count = 0;
	while (discovered.empty() == false) 
	{
		count++;

		// 제일 좋은 후보를 찾는다
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++) 
		{
			cout << count<<": vertext -> " << it->vertex << ", cost -> " << it->cost <<"\n";

			if (it->cost < bestCost) 
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		// 방문? 뒤늦게 찾은 느린경로들은 전부 스킵
		if (best[here] < cost)
			continue;

		// 방문!
		for (int there = 0; there < 6; there++) 
		{
			// 연결되지 않았으면 스킵
			if (adjacent[here][there] == -1)
				continue;

			// 더 좋은 경로를 과거에 찾았다면 스킵
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there]) // 기껏 비교해봤는데 기존에 찾은 코스트 보다 낮다면
				continue;

			// (3,35) (3,25) 두개가 들어갈것
			discovered.push_back(VertexCost{ there,nextCost });
			best[there] = nextCost; 
			parent[there] = here;
		}
	}
}

int main()
{
	CreateGraph();

	//Dijikstra(0);
	//Dijkstra1(0);
	Dijkstra2(0);


	return 0;
}