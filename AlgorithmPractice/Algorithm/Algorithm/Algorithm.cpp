#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
using namespace std;

// 오늘의 주제 : 이진 탐색 트리

// 이진 탐색(binary search)
// 상황) 배열에 데이터가 정렬되어 있다

// Q) 82라는 숫자가 배열에 있습니까?
// A) 쭈욱 스캔하는 방식
// [1][8][15][23][32][44][56][63][81][91]

vector<int> numbers;

// 이진 탐색 - 정렬이 되어있었기 때문에 가능하다.
// 정렬된 배열이었기 때문에 가능하였고, 정렬된 연결 리스트로는 불가할 것이다.
// 잠깐 그런데 배열의 단점은 중간 삽입 삭제가 느린 문제가 있었다.
// 찾은 값을 꺼내거나, 값을 넣어야 한다면? 이진탐색에는 한계가 있을것이다.
// 그래서 트리를 가서 노드기반으로 만들어서 데이터를 유동적으로 바꾸려는 것
// 삽입삭제가 없다면 배열을 통해 이진탐색을 하는 방식이 좋은 방식이 될 수 있다.
void BinarySearch(int N) 
{
	int left = 0;
	int right = numbers.size() - 1;
	bool check = false;

	while (left <= right) 
	{
		int mid = (left + right) / 2;

		cout << "검색 범위: " << left << " ~ " << right << endl;

		if (N < numbers[mid]) 
		{
			cout << N << " < " << numbers[mid] << endl;
			right = mid-1;
		}
		else if (N > numbers[mid]) 
		{
			cout << N << " > " << numbers[mid] << endl;
			left = mid + 1;
		}
		else 
		{
			cout << "찾읍!" << endl;
			check = true;
			break;
		}
	}
	if(!check)	cout << "못 찾읍!" << endl;
}

int main()
{
	numbers = vector<int>{ 1,8,15,23,32,44,56,63,81,91 };
	BinarySearch(82);

	return 0;
}