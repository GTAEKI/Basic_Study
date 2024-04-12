#include "pch.h"
#include "Player.h"
#include "Board.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Bfs();

}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
#pragma region 우수법
	//// 임시 내 포지션
	//Pos pos = _pos;

	//_path.clear();
	//_path.push_back(pos);

	//// 목적지를 가져온다.
	//Pos dest = _board->GetExitPos();

	//Pos front[4] =
	//{
	//	Pos {-1,0},	//UP
	//	Pos {0,-1},	//LEFT
	//	Pos {1,0},	//DOWN
	//	Pos {0,1},	//RIGHT
	//};

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
#pragma endregion
}

void Player::SelfBfs()
{
#pragma region 직접 짜본 코드(정답 보기 전)
	/*Pos comp = Pos{ 0,0 };
	Pos start = Pos{ -1,-1 };
	bool arrived = false;

	const int size = _board->GetSize();
	vector<vector<Pos>> visited(size,vector<Pos>(size,Pos{0,0}));

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

	std::reverse(_path.begin(), _path.end());*/
#pragma endregion
}

void Player::Bfs() 
{
	// 임시 내 포지션
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// 목적지를 가져온다.
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos {-1,0},	//UP
		Pos {0,-1},	//LEFT
		Pos {1,0},	//DOWN
		Pos {0,1},	//RIGHT
	};

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	//vector<vector<Pos>> parent;
	// parent[A] = B; -> A는 B로 인해 발견함
	map<Pos, Pos> parent;

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false) 
	{
		pos = q.front();
		q.pop();

		if (pos == dest)
			break;

		for (int32 dir = 0; dir < 4; dir++) 
		{
			Pos nextPos = pos + front[dir];
			if (CanGo(nextPos) == false) continue;
			if (discovered[nextPos.y][nextPos.x] == true) continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	//TODO
	_path.clear();

	pos = dest;

	while (true) 
	{
		_path.push_back(pos);

		// 시작점
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
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
