#pragma once

#include "Types.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <cassert>
using namespace std;

struct Pos 
{
	bool operator ==(const Pos& other) 
	{
		return x == other.x && y == other.y;
	}

	int32 x = 0;
	int32 y = 0;
};