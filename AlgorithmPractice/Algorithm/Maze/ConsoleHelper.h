#pragma once

#include <windows.h>
#include "Types.h"

enum class ConsoleColor
{
	// 실질적으로 나중에 사용할 API와 연관이 있다.
	// 콘솔에 사용할 색
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

class ConsoleHelper
{
public:
	static void SetCursorPosition(int32 x, int32 y); // 커서 설정
	static void SetCursorColor(ConsoleColor color); // 커서 색상 결정
	static void ShowConsoleCursor(bool flag); // 커서 보여줄지 안보여줄지
};

