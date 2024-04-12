#include "pch.h"
#include "Player.h"
#include "Board.h"

Player::Player()
{
}

Player::~Player()
{
}

Pos visited[BOARD_MAX_SIZE][BOARD_MAX_SIZE];

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	// 임시 내 포지션
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// 목적지를 가져온다.
	Pos dest = board->GetExitPos();

	Pos front[4] =
	{
		Pos {-1,0},	//UP
		Pos {0,-1},	//LEFT
		Pos {1,0},	//DOWN
		Pos {0,1},	//RIGHT
	};

	Pos comp = Pos{ 0,0 };
	Pos start = Pos{ -1,-1 };
	bool arrived = false;

	queue<Pos> que;
	que.push(pos);
	visited[pos.y][pos.x] = Pos{-1,-1};

	while (que.empty() == false)
	{
		Pos here = que.front();
		que.pop();

		for (int index = 0; index < 4; index++)
		{
			Pos there = here + front[index];
			if (there.x < 0 || there.y < 0 ||
				there.x >= _board->GetSize() ||
				there.y >= _board->GetSize() ||
				_board->GetTileType(there) == TileType::WALL)
				continue;
			if (visited[there.y][there.x] == comp) continue;
			if (visited[there.y][there.x] == dest) 
			{
				arrived = true;
				visited[there.y][there.x] = visited[here.y][here.x];
				break;
			} 

			que.push(there);
			visited[there.y][there.x] = visited[here.y][here.x];
		}

		if (arrived == true) break;
	}

	Pos tempPos = visited[dest.y][dest.x];

	while (true) 
	{
		if (tempPos == start) break;

		_path.push_back(tempPos);
		tempPos = visited[tempPos.y][tempPos.x];
	}

	std::reverse(_path.begin(), _path.end());

	//// 목적지 도착하기 전에는 계속 실행
	//while (pos != dest)
	//{
	//	// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인.
	//	int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
	//	if (CanGo(pos + front[newDir]))
	//	{
	//		// 오른쪽 방향으로 90도 회전
	//		_dir = newDir;
	//		// 앞으로 한 보 전진
	//		pos += front[_dir];

	//		_path.push_back(pos);
	//	}
	//	// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
	//	else if (CanGo(pos + front[_dir]))
	//	{
	//		// 앞으로 한 보 전진
	//		pos += front[_dir];

	//		_path.push_back(pos);
	//	}
	//	else
	//	{
	//		_dir = (_dir + 1) % DIR_COUNT;
	//	}
	//}

	//stack<Pos> s;

	//for (int i = 0; i < _path.size() - 1; i++)
	//{
	//	if (s.empty() == false && s.top() == _path[i + 1])
	//		s.pop();
	//	else
	//		s.push(_path[i]);
	//}

	//// 목적지 도착
	//if (_path.empty() == false)
	//	s.push(_path.back());

	//vector<Pos> path;
	//while (s.empty() == false)
	//{
	//	path.push_back(s.top());
	//	s.pop();
	//}

	//std::reverse(path.begin(), path.end());

	//_path = path;

}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}
