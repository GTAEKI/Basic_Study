#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"
#include "DisjointSet.h"

const char* TILE = "■";

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size, Player* player)
{
	assert(size < BOARD_MAX_SIZE && size % 2 != 0);

	_size = size;
	_player = player;

	//GenerateMap_Kruskal();
	GenerateMap_Prim();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);
	//ConsoleHelper::SetCursorColor(ConsoleColor::RED);

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			ConsoleColor color = GetTileColor(Pos{ y,x });
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}

		cout << endl;
	}
}

// Binary Tree 미로 생성 알고리즘
// - Mazes For Programmers 책

void Board::GenerateMap_Kruskal()
{
	struct CostEdge
	{
		int cost;
		Pos u;
		Pos v;

		bool operator<(CostEdge& other)
		{
			return cost < other.cost;
		}
	};

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_tile[y][x] = TileType::WALL;
			}
			else
			{
				_tile[y][x] = TileType::EMPTY;
			}
		}
	}

	vector<CostEdge> edges;

	// edges 후보를 랜덤 cost로 등록
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 우측 연결하는 간선 후보
			if (x < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue, Pos{y,x}, Pos{y,x + 2} });
			}

			// 아래로 연결하는 간선 후보
			if (y < _size - 2) 
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue, Pos{y,x}, Pos{y + 2,x} });
			}
		}
	}

	std::sort(edges.begin(), edges.end());

	DisjointSet sets(_size * _size);

	for (CostEdge& edge : edges) 
	{
		int u = edge.u.y * _size + edge.u.x; // 2차원을 1차원으로 관리하고싶을때 이용하는 대표적인 공식
		int v = edge.v.y * _size + edge.v.x; // 1차원 배열로 바꿔준다.
		// 같은 그룹이면 스킵
		if (sets.Find(u) == sets.Find(v))
			continue;

		sets.Merge(u, v);

		// 맵에 적용
		int y = (edge.u.y + edge.v.y) / 2;
		int x = (edge.u.x + edge.v.x) / 2;
		_tile[y][x] = TileType::EMPTY;
	}

	//// 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
	//for (int32 y = 0; y < _size; y++)
	//{
	//	for (int32 x = 0; x < _size; x++)
	//	{
	//		if (x % 2 == 0 || y % 2 == 0)
	//			continue;
	//		if (y == _size - 2 && x == _size - 2)
	//			continue;

	//		if (y == _size - 2) 
	//		{
	//			_tile[y][x + 1] = TileType::EMPTY;
	//			continue;
	//		}
	//		
	//		if (x == _size - 2) 
	//		{
	//			_tile[y + 1][x] = TileType::EMPTY;
	//			continue;
	//		}

	//		const int32 randValue = ::rand() % 2;
	//		if (randValue == 0)
	//		{
	//			_tile[y][x + 1] = TileType::EMPTY;
	//		}
	//		else
	//		{
	//			_tile[y + 1][x] = TileType::EMPTY;
	//		}
	//	}
	//}
}

void Board::GenerateMap_Prim()
{
	struct CostEdge
	{
		int cost;
		Pos vtx;

		// 우선순위 큐 사용시 내부적으로 const를 붙이지 않으면 빌드가 되지 않음
		bool operator<(const CostEdge& other) const 
		{
			return cost < other.cost;
		}
	};

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_tile[y][x] = TileType::WALL;
			}
			else
			{
				_tile[y][x] = TileType::EMPTY;
			}
		}
	}

	// edges[u] : u 정점과 연결된 간선 목록
	map<Pos, vector<CostEdge>> edges;

	// edges 후보를 랜덤으로 등록한다.
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 우측 연결하는 간선 후보
			if (x < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				// u 정점과 v정점을 연결하겠다는 컨셉
				Pos u = Pos{ y,x };
				Pos v = Pos{ y,x + 2 };

				// 코드에서 찾기 쉽도록 서로 연결
				edges[u].push_back(CostEdge{ randValue, v }); // u와 v연결
				edges[v].push_back(CostEdge{ randValue, u }); // v와 u도 연결
			}

			// 아래로 연결하는 간선 후보
			if (y < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				// u 정점과 v정점을 연결하겠다는 컨셉
				Pos u = Pos{ y,x };
				Pos v = Pos{ y+2,x};

				// 코드에서 찾기 쉽도록 서로 연결
				edges[u].push_back(CostEdge{ randValue, v }); // u와 v연결
				edges[v].push_back(CostEdge{ randValue, u }); // v와 u도 연결
			}
		}
	}

	// 해당 정점이 트리에 포함되어 있나?
	map<Pos, bool> added; // 이중 벡터로 만들어도 됨
	
	// 어떤 정점이 누구에 의해 연결되었는지
	map<Pos, Pos> parent;

	// 만들고있는 트리에 인접한 간선 중, 해당 정점에 닿는 최소 간선의 정보
	// 다익스트라 : 시작 기준 / 프림 : 현재 트리 기준
	map<Pos, int32> best;

	for (int32 y = 0; y < _size; y++) 
	{
		for (int32 x = 0; x < _size; x++) 
		{
			best[Pos{ y,x }] = INT32_MAX;
			added[Pos{ y,x }] = false; // 옵션
		}
	}

	priority_queue<CostEdge> pq;
	const Pos startPos = Pos{ 1,1 }; // 랜덤으로 정해도 됨
	pq.push(CostEdge{ 0, startPos });
	best[startPos] = 0;
	parent[startPos] = startPos;

	while (pq.empty() == false) 
	{
		CostEdge bestEdge = pq.top();
		pq.pop();

		// 새로 연결된 정점
		Pos v = bestEdge.vtx;
		// 이미 추가되었다면 스킵
		if (added[v])
			continue;

		added[v] = true;

		// 맵에 적용
		{
			int y = (parent[v].y + v.y) / 2;
			int x = (parent[v].x + v.x) / 2;

			_tile[y][x] = TileType::EMPTY;
		}

		// 방금 추가한 정점에 인접한 간선들을 검사한다.
		for (CostEdge& edge : edges[v]) 
		{
			// 이미 추가 되었으면 스킵 - 사이클 방지
			// 크루스칼에서는 DisjoinSet을 이용했었음
			// 프림알고리즘은 그룹이 1개이므로 bool로도 충분하다.
			if (added[edge.vtx])
				continue;

			// 다른 경로로 더 좋은 후보가 발견되었으면 스킵
			if (edge.cost > best[edge.vtx])
				continue;

			best[edge.vtx] = edge.cost;
			parent[edge.vtx] = v;

			pq.push(edge);
		}
	}
}

TileType Board::GetTileType(Pos pos)
{
	if (pos.x < 0 || pos.x >= _size)
		return TileType::NONE;

	if (pos.y < 0 || pos.y >= _size)
		return TileType::NONE;

	return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	if (_player && _player->GetPos() == pos) // _player 가 null이 아니고, 현재 위치라면
		return ConsoleColor::YELLOW;

	if (GetExitPos() == pos)
		return ConsoleColor::BLUE;

	TileType tileType = GetTileType(pos);

	switch (tileType)
	{
	case TileType::EMPTY:
		return ConsoleColor::GREEN;
	case TileType::WALL:
		return ConsoleColor::RED;
	}

	return ConsoleColor::WHITE;
}
