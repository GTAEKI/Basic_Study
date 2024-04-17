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

	GenerateMap();
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

void Board::GenerateMap()
{
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
