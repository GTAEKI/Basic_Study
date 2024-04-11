#pragma once

class Board;

class Player
{
public:
	Player();
	~Player();
public:
	void Init(Board* board);
	void Update(uint64 deltaTick); // 실질적인 길찾기, 이동 , 매프레임 업데이트를 계속 돌려서, 이전 프레임 대비 경과시간을 계속 넘겨서 업데이트

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

private:
	Pos _pos = {};
	int32 _dir = DIR_UP;
	Board* _board = nullptr;

};

