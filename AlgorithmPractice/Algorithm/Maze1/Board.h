#pragma once
#include "ConsoleHelper.h"


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

	void Init(int32 size);
	void Render();

	void GenerateMap();

	// 좀 더 편하게관리하기 위한 함수 
	TileType GetTileType(Pos pos); // 어떤 타일이 있는지 체크
	ConsoleColor GetTileColor(Pos pos); // 어떤 위치 어떤 색상인지

private:
	TileType _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	int32 _size = 0;
};

