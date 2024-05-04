#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
#include<Windows.h>
using namespace std;

// 카트라이더
// -카트는 게임이 시작하면 달리기 시작하며, 주어진 시간(T)동안 달린다.
// 카트는 처음에는 기본 속도 (초속 1)로 달린다.
// 게임이 시작하고 특정 시간(a)가 되면 바닥에 신발 아이템이 생성된다.
// 카트는 신발을 신거나 지나칠 수 있다. 지나간 신발은 영영 다시 주울 수 없다.
// 신발을 착용하려면 (b)의 시간이 필요하다. 즉(b)초 동안 제자리에서 멈추고 나서야 움직일 수 있다.
// 신발을 착용하면 일정시간(c) 동안 신발 속도(d)로 달릴 수 있다.
// 신발은 하나만 착용할 수 있고, 가장 최근에 착용한 신발의 속도만 적용된다.
// 신발을 벗거나 다른 신발로 바꿔 장착할 때 추가시간이 들지 않는다. (새로운 신발을 신는 시간만 소요된다.)
// 신발 효과가 끝나면 다시 기본 속도 (초속 1)로 달린다.
// 
// Q) 생성되는 모든 신발 정보가 주어졌을 때, (T)초 동안 갈 수 있는 최대 거리를 구하라.
//

struct Shoe
{
	Shoe(int a, int b, int c, int d) : time(a), start(a + b), end(a + b + c), speed(d)
	{

	}

	int time;
	int start;
	int end;
	int speed;
};

int T;
vector<int> cache;
vector<Shoe> shoes;

// input.txt
// 20
// 4
// 3 4 10 3
// 4 1 4 2
// 10 2 5 5 
// 15 1 3 7

int Solve(int now) 
{
	if (now >= shoes.size())
		return 0;

	// cache
	int& ret = cache[now];
	if (ret != -1)
		return ret;

	Shoe& shoe = shoes[now];
	
	int dist = (shoe.end - shoe.start) * shoe.speed + (T - shoe.end) * 1;
	ret = max(ret, dist);

	for (int next = now + 1; next < shoes.size(); next++) 
	{
		Shoe& nextShoe = shoes[next];

		if (nextShoe.time < shoe.start)
			continue;

		int moveDist = 0;
		if (nextShoe.time <= shoe.end) 
		{
			moveDist = (nextShoe.time - shoe.start) * shoe.speed;
		}
		else 
		{
			moveDist = (shoe.end - shoe.start) * shoe.speed + (nextShoe.time - shoe.end) * 1;
		}

		ret = max(ret, moveDist + Solve(next));
	}

	return ret;
}

int main()
{
	T = 20;

	shoes.push_back(Shoe(0,0,T,1));
	shoes.push_back(Shoe(3, 4, 10, 3));
	shoes.push_back(Shoe(4, 1, 4, 2));
	shoes.push_back(Shoe(10, 2, 5, 5));
	shoes.push_back(Shoe(15, 1, 3, 7));

	std::sort(shoes.begin(), shoes.end(), [=](Shoe& left, Shoe& right) {return left.time < right.time; });

	cache = vector<int>(shoes.size(), -1);

	int ret = Solve(0);
	cout << ret << endl;
}

#pragma region MyRegion
//
//	//Vector<int> v3;
//
//	//v3.reserve(8);
//
//	//cout << v3.size() << v3.capacity() << endl;
//
//	//v3.push_back(1);
//	//v3.push_back(2);
//	//v3.push_back(3);
//	//v3.push_back(4);
//	//v3.push_back(5);
//	//v3.push_back(6);
//	//v3.push_back(7);
//	//v3.push_back(8);
//
//	//for (int i = 0; i < v3.size(); i++) 
//	//{
//	//	cout << v3[i] << endl;
//	//}
//
//	//cout << v3.size() << v3.capacity() << endl;
//
//	//v3.push_back(9);
//
//	//cout << v3.size() << v3.capacity() << endl;
//
//	//v3.pop_back();
//	//v3.pop_back();
//	//v3.pop_back();
//
//	//cout << v3.size() << v3.capacity() << endl;
//
//	//v3.clear();
//
//	//cout << v3.size() << v3.capacity() << endl;
//
//
//	//LinkedList<int> l3;
//
//	//l3.push_back(3);
//	//l3.push_back(4);
//	//l3.push_back(5);
//	//l3.push_back(6);
//
//	//for (auto iter = l3.begin(); iter != l3.end(); iter++) 
//	//{
//	//	cout << *iter << endl;
//	//}
//
//	//l3.pop_back();
//
//	//LinkedList<int> ::iterator iter2 = l3.begin();
//	//iter2++;
//	//l3.insert(iter2, 999);
//
//	//for (auto iter = l3.begin(); iter != l3.end(); iter++)
//	//{
//	//	cout << "추가: " << *iter << endl;
//	//}
//
//
//	//cout << l3.size() << endl;
//
//	//l3.erase(iter2);
//
//
//	//for (auto iter = l3.begin(); iter != l3.end(); iter++)
//	//{
//	//	cout << "추가2: " << *iter << endl;
//	//}
//
//	//cout << l3.size() << endl;
//
//
//	//PriorityQueue<int> pq;
//
//	//pq.push(100);
//	//pq.push(300);
//	//pq.push(200);
//	//pq.push(500);
//	//pq.push(400);
//
//
//	//while (pq.empty() == false)
//	//{
//	//	int value = pq.top();
//	//	pq.pop();
//
//	//	cout << value << endl;
//	//}
//
//	//vector<int> v{1,3,2,4,9,6,7,5,8};
//
//	////BubbleSort<int>(v,greater<int>());
//	////SelectionSort(v);
//	////InsertionSort(v);
//	////HeapSort(v);
//	//MergeSort(v, 0, v.size()-1);
//	////QuickSort(v, 0, v.size() - 1);
//
//	//for (auto num : v) 
//	//{
//	//	cout << num << endl;
//	//}
#pragma endregion

