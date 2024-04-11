#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main()
{
	::srand(static_cast<unsigned>(time(nullptr))); // 랜덤 시드설정
	board.Init(25, &player);
	player.Init(&board);

	std::locale::global(std::locale("ko_KR.UTF-8"));

	// 거의 대부분의 게임들은 무한루프안에서 돌아간다.
	// 물론 온라인게임일 경우 일부 로직은 서버쪽에 분산이 되어 처리될것
	// 입력
	// 로직
	// 랜더링
	uint64 lastTick = 0;

	while (true)
	{
#pragma region 프레임 관리
		// 기본적인 프레임 관리
		// 고정프레임, 가변프레임이 있다
		// 고정은 1초동안 고정적인 프레임만 허락하겠다 (30, 60 등)
		// 요즘 게임들은 컴퓨터 좋은거에 맞춰 그냥 200 300 까지도 가는것을 볼 수 있는데
		// 우리는 그냥 가변으로
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick;
		lastTick = currentTick;
#pragma endregion
		// 입력

		// 로직
		player.Update(deltaTick);

		// 랜더링
		board.Render();
	}
}