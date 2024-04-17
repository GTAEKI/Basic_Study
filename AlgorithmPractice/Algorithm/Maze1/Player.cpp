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

	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size()) 
	{
		//_board->GenerateMap_Kruskal();
		_board->GenerateMap_Prim();
		Init(_board);
		return;
	}

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
#pragma region 우수법
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

	// 목적지 도착하기 전에는 계속 실행
	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인.
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{
			// 오른쪽 방향으로 90도 회전
			_dir = newDir;
			// 앞으로 한 보 전진
			pos += front[_dir];

			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진
			pos += front[_dir];

			_path.push_back(pos);
		}
		else
		{
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	// 목적지 도착
	if (_path.empty() == false)
		s.push(_path.back());

	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	std::reverse(path.begin(), path.end());

	_path = path;
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

struct PQNode 
{
	bool operator<(const PQNode& other) const 
	{
		return f < other.f;
	}

	bool operator>(const PQNode& other) const
	{
		return f > other.f;
	}

	int32 f; // f = g + h;
	int32 g;
	Pos pos;
};

void Player::AStar()
{
	// 점수 매기기 (다익스트라에서는 가중치의 합이었다)
	// F = G + H (대부분의 A*)
	// F = 최종점수(작을수록 좋음, 경로에 따라 달라짐)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용
	// H = 목적지에서 얼마나 가까운지(작을 수록 좋음, 고정) -> 휴리스틱의 약자

	Pos start = _pos;
	Pos dest = _board->GetExitPos();
	
	enum
	{
		DIR_COUNT = 4, // 여기까지 일단 사용하겠다는 뜻
	};

	Pos front[] =
	{
		Pos {-1,0},	//UP
		Pos {0,-1},	//LEFT
		Pos {1,0},	//DOWN
		Pos {0,1},	//RIGHT
		Pos {-1,-1},// UP_LEFT // 대각선
		Pos {1,-1},	// downleft
		Pos {1,1},	// DOWN_RIGHT
		Pos {-1,1}	// UP_RIGHT
	};

	// 이동 비용
	int32 cost[] =
	{
		10, // UP
		10, // LEFT
		10, // DOWN
		10, // RIGHT
		14, // 대각선
		14,
		14,
		14,
	};

	const int32 size = _board->GetSize();

	// CloseList
	// close[y][x] -> (y,x) 에 방문을 했는지 여부
	// closed는 굳이 사용안해도 best만으로 구현도 가능하다.
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	// best[y][x] -> 지금까지 (y,x)에 대한 가장 좋은 비용(작을수록 좋음)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));
	// -> 너무 데이터가 많아져서 사이즈가 크다면
	// 이차벡터로 만들기보다는 map이라거나 다른 형태로 바꿔주면 된다.
	// 알고리즘 이해가 핵심이다. 구현 방식은 맘대로 해도 됨

	// 부모 추적 용도
	map<Pos, Pos> parent;

	// OpenList - 지금까지 예약된 애들을 관리하는 자료구조, 어떤식으로 만들어도상관없지만 이번에는 우선순위큐로 구현
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>>pq;

	// 1) 예약(발견) 시스템 구현
	// - 이미 더 좋은 경로를 찾았다면 스킵
	// 2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수
	// - openList에서 찾아서 제거한다거나 -> list로 구현했다면?
	// - pq에서 pop한 다음에 무시한다거나 -> 현재 구현 방식
	
	// 초기값
	{
		int32 g = 0;
		// 임의로 정해준 h
		// 연산량이 적어서 이렇게 해주었다. 경우에 따라서는 피타고라스 정리를 사용해도 되고 여러 방식을 사용할 수 있다.
		int32 h = 10 * (abs(dest.y - start.y)) + abs(dest.x - start.x);
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false) 
	{
		// 제일 좋은 후보를 찾는다.
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로로 찾아서, 
		// 더 빠른 경로로 인해서 이미 방문(closed)된 경우 스킵
		// 이 부분을 누락하게 된다면
		// 스타크래프트에서 드라군이 왼쪽갔다 오른쪽갔다 와리가리 하는 것을 보게 된다.
		// closed로 해도 되고 best로 판별해도됨 closed는 이해가 편하도록 넣은것임

		// [선택]
		if (closed[node.pos.y][node.pos.x])
			continue;
		// if(best[node.pos.y],best[node.pos.x] < node.f) continue;

		// 방문
		// 내가 방문을 한 다음 그 다음 더 우수한 후보를 찾을 수는 없나요?
		// 그것은 존재할 수가 없다고 한다. 이미 방문했다는 사실은 더 빠른 경로를 발견할 수 없다는 이야기.
		// 수학적으로도 증명할 수 있음
		closed[node.pos.y][node.pos.x] = true;

		// 목적지에 도착했으면 바로 종료
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++) 
		{
			Pos nextPos = node.pos + front[dir];
			// 갈 수 있는 지역은 맞는지 확인
			if (CanGo(nextPos) == false)
				continue;

			// [선택] 이미 방문한 곳이라면 스킵
			// 여기서 넣지 않는다면, 우선순위큐에 들어가게 될것이고, 위쪽에서 걸러질 것이다.
			if (closed[nextPos.y][nextPos.x])
				continue;

			// 비용 계산
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y)) + abs(dest.x - nextPos.x);
			
			// 다른 경로에서 더 빠른 길을 찾았으면 스킵
			// 동점까지도 스킵
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// 여기까지 왔다면, 내가 지금까지 찾은 경로보다 우수한 후보라는것을 알 수 있으니
			// 예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}

	// 거꾸로 거슬러올라간다.
	Pos pos = dest;

	_path.clear();
	_pathIndex = 0;

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
