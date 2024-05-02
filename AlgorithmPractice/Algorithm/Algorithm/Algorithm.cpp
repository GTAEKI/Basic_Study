#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
#include<Windows.h>
using namespace std;

// 동적 계획법 (DP)
// TIC-TAE-TOE

// [.][.][.]
// [.][.][.]
// [.][.][.]

int HashKey(const vector<vector<char>>& board) 
{
	int ret = 0;

	for (int y = 0; y < 3; y++) 
	{
		for (int x = 0; x < 3; x++) 
		{
			ret = ret * 3;

			if (board[y][x] == 'o')
				ret += 1;
			else if (board[y][x] == 'x')
				ret += 2;
		}
	}

	return ret;
}

vector<vector<char>> board;
int cache[19683];

enum
{
	DEFAULT = 2,
	WIN = 1,
	DRAW = 0,
	LOSE = -1
};

bool IsFinished(const vector<vector<char>>& board, char turn) 
{
	//좌우
	for (int i = 0; i < 3; i++)
		if (board[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
			return true;
	
	//상하
	for (int i = 0; i < 3; i++)
		if (board[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
			return true;

	//대각선
	if (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
		return true;

	if (board[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
		return true;

	return false;
}

int CanWin(vector<vector<char>>& board, char turn)
{
	// 기저 사례
	if (IsFinished(board, 'o' + 'x' - turn))
		return LOSE;

	// 캐시 확인
	int key = HashKey(board);
	int& ret = cache[key];
	if (ret != DEFAULT)
		return ret;

	// 풀기

	int minValue = DEFAULT;

	for (int y = 0; y < 3; y++) 
	{
		for (int x = 0; x < 3; x++) 
		{
			if (board[y][x] != '.')
				continue;

			// 착수
			board[y][x] = turn;

			// 확인
			minValue = min(minValue, CanWin(board, 'o' + 'x' - turn)); // 상대방이 패배하는것이 제일 좋은 케이스

			// 취소
			board[y][x] = '.';
		}
	}

	if (minValue == DRAW || minValue == DEFAULT)
		return ret = DRAW;

	return ret = -minValue;
}

int main()
{
#pragma region MyRegion

	//Vector<int> v3;

	//v3.reserve(8);

	//cout << v3.size() << v3.capacity() << endl;

	//v3.push_back(1);
	//v3.push_back(2);
	//v3.push_back(3);
	//v3.push_back(4);
	//v3.push_back(5);
	//v3.push_back(6);
	//v3.push_back(7);
	//v3.push_back(8);

	//for (int i = 0; i < v3.size(); i++) 
	//{
	//	cout << v3[i] << endl;
	//}

	//cout << v3.size() << v3.capacity() << endl;

	//v3.push_back(9);

	//cout << v3.size() << v3.capacity() << endl;

	//v3.pop_back();
	//v3.pop_back();
	//v3.pop_back();

	//cout << v3.size() << v3.capacity() << endl;

	//v3.clear();

	//cout << v3.size() << v3.capacity() << endl;


	//LinkedList<int> l3;

	//l3.push_back(3);
	//l3.push_back(4);
	//l3.push_back(5);
	//l3.push_back(6);

	//for (auto iter = l3.begin(); iter != l3.end(); iter++) 
	//{
	//	cout << *iter << endl;
	//}

	//l3.pop_back();

	//LinkedList<int> ::iterator iter2 = l3.begin();
	//iter2++;
	//l3.insert(iter2, 999);

	//for (auto iter = l3.begin(); iter != l3.end(); iter++)
	//{
	//	cout << "추가: " << *iter << endl;
	//}


	//cout << l3.size() << endl;

	//l3.erase(iter2);


	//for (auto iter = l3.begin(); iter != l3.end(); iter++)
	//{
	//	cout << "추가2: " << *iter << endl;
	//}

	//cout << l3.size() << endl;


	//PriorityQueue<int> pq;

	//pq.push(100);
	//pq.push(300);
	//pq.push(200);
	//pq.push(500);
	//pq.push(400);


	//while (pq.empty() == false)
	//{
	//	int value = pq.top();
	//	pq.pop();

	//	cout << value << endl;
	//}

	//vector<int> v{1,3,2,4,9,6,7,5,8};

	////BubbleSort<int>(v,greater<int>());
	////SelectionSort(v);
	////InsertionSort(v);
	////HeapSort(v);
	//MergeSort(v, 0, v.size()-1);
	////QuickSort(v, 0, v.size() - 1);

	//for (auto num : v) 
	//{
	//	cout << num << endl;
	//}
#pragma endregion

	board = vector<vector<char>>
	{
		{'o','x','x'},
		{'.','o','.'},
		{'o','.','.'},
	};

	for (int i = 0; i < 19683; i++)
		cache[i] = DEFAULT;

	int win = CanWin(board, 'x');

	switch (win) 
	{
		case WIN:
			cout << "WIN" << endl;
			break;
		case DRAW:
			cout << "DRAW" << endl;
			break;
		case LOSE:
			cout << "LOSE" << endl;
			break;
	}
}

