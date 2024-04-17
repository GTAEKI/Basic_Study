#pragma once
#include "ConsoleHelper.h"

class Player; // 전방선언

enum
{
	BOARD_MAX_SIZE = 100
};

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
};



class Board
{
public:
	Board();
	~Board();

	void Init(int32 size, Player* player);
	void Render();

	void GenerateMap_Kruskal();
	void GenerateMap_Prim();

	// 좀 더 편하게관리하기 위한 함수 
	TileType GetTileType(Pos pos); // 어떤 타일이 있는지 체크
	ConsoleColor GetTileColor(Pos pos); // 어떤 위치 어떤 색상인지

	Pos GetEnterPos() { return Pos{ 1,1 }; };
	Pos GetExitPos() { return Pos{ _size - 2, _size - 2 }; };

	int GetSize() { return _size; }

private:
	TileType _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	int32 _size = 0;
	Player* _player = nullptr;
};

