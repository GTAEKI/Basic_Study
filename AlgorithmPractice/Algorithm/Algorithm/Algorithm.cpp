#include<iostream>
#include<vector>
using namespace std;

void CreateGraph_1()
{
	// 포인터로 서로 물고있는 구조가 살짝 맘에 안든다.
	// 나중에가면 실제 데이터와 간선의 연결여부를 분리해서 관리를 하는게 좀 더 유용한 상황이 종종 생긴다.
	// 그런데 지금은 정점 자체에 간선에 대한 정보가 같이 포함되어있는것도 맘에 들지 않는다.
	struct Vertex
	{
		vector<Vertex*> edges;
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// Q) 0번과 3번 정점이 연결되어 있나요?
	bool connected = false;
	for (Vertex* edge : v[0].edges)
	{
		if (edge == &v[3])
		{
			connected = true;
			break;
		}
	}
}



// 나쁜 방법이 아니다. 하지만
// 정점이 100개 ~~ 엄청 큰 수 일 경우
// 서로 드문 드문 연결되어있는 경우

// 그러나
// 페이스북 친구 100명끼리 모두 서로를 친추해놓은 상태라면
// 서로 빽빽하게 연결되어있을것이다.
// 그렇다면 리스트에 모두 연결을 시켜주어야 할 것이다. 
// 검색을 할 경우에도 하나씩 하나씩 순회를 해서 찾아보는 수밖에 없다.
// 빽빽하다면 2차 배열을 통해 메모리를 팔아 성능을 얻는 방법이 좋은 방법이 될것이다.
void CreateGraph_2()
{
	//struct Vertex
	//{
	//	// int data;
	//};

	//vector<Vertex> v;
	//v.resize(6);

	// 연결된 목록을 따로 관리
	// adjacent[n] -> n번째 정점과 연결된 정점 목록
	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };


	// Q) 0번과 3번 정점이 연결되어 있나요?
	bool connected = false;
	for (int vertex : adjacent[0])
	{
		if (vertex == 3)
		{
			connected = true;
			break;
		}
	}

	// STL
	vector<int>& adj = adjacent[0];
	bool connected2 = (std::find(adj.begin(), adj.end(), 3) != adj.end());
}

void CreateGraph_3()
{
	// 연결된 목록을 따로 관리
	// [X][O][X][O][X][X]
	// [O][X][O][O][X][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]

	// 읽는 방법 adjacent[from][to]
	// 행렬을 이용한 그래프 표현(2차원 배열)
	// 메모리 소모가 심하지만, 빠른 접근이 가능하다.
	// 간선이 많은 경우 이점이 있음
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][5] = true;


	// Q) 0번과 3번 정점이 연결되어 있나요?
	bool connected = adjacent[0][3];

	// 간선에도 값을 넣어준것 : 초기값 -1, 가중치 양수
	vector<vector<int>> adjacent2 =
	{
		vector<int> {-1,15,-1,35,-1,-1},
		vector<int>{15,-1,+5,10,-1,-1},
		vector<int>{-1,-1,-1,-1,-1,-1},
		vector<int>{-1,-1,-1,-1,+5,-1},
		vector<int>{-1,-1,-1,-1,-1,-1},
		vector<int>{-1,-1,-1,-1,+5,-1},
	};

	// Q) 0번과 3번 정점이 연결되어 있나요?
	bool connected = (adjacent[0][3] != -1);
}

int main()
{
	CreateGraph_3();


	return 0;
}