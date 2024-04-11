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

	// 임시 내 포지션
	Pos pos = _pos;

	// 목적지를 가져온다.
	Pos dest = board->GetExitPos();

	// 목적지 도착하기 전에는 계속 실행
	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인.
		if (CheckRightDir(pos))
		{
			// 오른쪽 방향으로 90도 회전
			TurnRight();
			// 앞으로 한 보 전진
			MovePos(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CheckFrontDir(pos))
		{
			// 앞으로 한 보 전진
			MovePos(pos);
		}
		else 
		{
			// 왼쪽 방향으로 90도 회전.
			TurnLeft();
		}
		cout << "움직이는중" << "\n";
	}
	cout << "도착";
}

// 직접구현
bool Player::CheckRightDir(const Pos& pos) 
{
	switch (_dir) 
	{
	case DIR_UP:
		if (_board->GetTileType(Pos{ pos.y, pos.x + 1 }) == TileType::EMPTY) return true;
		else return false;
	case DIR_RIGHT:
		if (_board->GetTileType(Pos{ pos.y+1, pos.x}) == TileType::EMPTY) return true;
		else return false;
	case DIR_LEFT:
		if (_board->GetTileType(Pos{ pos.y-1, pos.x}) == TileType::EMPTY) return true;
		else return false;
	case DIR_DOWN:
		if (_board->GetTileType(Pos{ pos.y, pos.x-1}) == TileType::EMPTY) return true;
		else return false;
	}
}


bool Player::CheckFrontDir(const Pos& pos)
{
	switch (_dir)
	{
	case DIR_UP:
		if (_board->GetTileType(Pos{ pos.y-1, pos.x}) == TileType::EMPTY) return true;
		else return false;
	case DIR_RIGHT:
		if (_board->GetTileType(Pos{ pos.y, pos.x+1 }) == TileType::EMPTY) return true;
		else return false;
	case DIR_LEFT:
		if (_board->GetTileType(Pos{ pos.y, pos.x-1}) == TileType::EMPTY) return true;
		else return false;
	case DIR_DOWN:
		if (_board->GetTileType(Pos{ pos.y+1, pos.x}) == TileType::EMPTY) return true;
		else return false;
	}
}


void Player::TurnRight() 
{
	switch (_dir)
	{
	case DIR_UP:
		_dir = DIR_RIGHT;
		return;
	case DIR_RIGHT:
		_dir = DIR_DOWN;
		return;
	case DIR_LEFT:
		_dir = DIR_UP;
		return;
	case DIR_DOWN:
		_dir = DIR_LEFT;
		return;
	}
}

void Player::TurnLeft() 
{
	switch (_dir)
	{
	case DIR_UP:
		_dir = DIR_LEFT;
		return;
	case DIR_RIGHT:
		_dir = DIR_UP;
		return;
	case DIR_LEFT:
		_dir = DIR_DOWN;
		return;
	case DIR_DOWN:
		_dir = DIR_RIGHT;
		return;
	}
}

void Player::MovePos(Pos& pos)
{
	switch (_dir)
	{
	case DIR_UP:
		pos.y -= 1;
		return;
	case DIR_RIGHT:
		pos.x += 1;
		return;
	case DIR_LEFT:
		pos.x -= 1;
		return;
	case DIR_DOWN:
		pos.y += 1;
		return;
	}
}

void Player::Update(uint64 deltaTick)
{

}
