#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<thread>
using namespace std;
// 오늘의 주제 : 해시테이블 (hash_map)

// Q) map vs hash_map (C++11 표준 unordered_map)

// map : Red-Black Tree
// - 추가/탐색/삭제 O(logN)

// C# dictionary = C++ unordered_map

// hash_map(unordered_map)
// - 추가/탐색/삭제 O(1)
// 메모리를 내주고 속도를 취한다

// '해시' '테이블'
void TestTable() 
{
	struct User 
	{
		int userId = 0; // 1~999
		string username;
	};

	vector<User> users;
	users.resize(1000);

	/// 777번 유저 정보 세팅
	users[777] = User{ 777, "Rookiss"};

	// 777번 유저 이름은?
	string name = users[777].username;
	cout << name << endl;

}


// 보안
// id: rookiss + pw : qwer1234;
// id: rookiss + pw : hash(qwer1234); -> dafdfs;fasdkfjs@#!244353@@@#DFDF

// DB[rookiss][qwer1234]
// DB[rookiss][dafdfs;fasdkfjs@#!244353@@@#DFDF]
// 역으로 돌아갈 수 없다. 역으로 해석할 수 없다.
// 비밀번호 찾기 -> 아이디 입력 / 폰 인증 -> 비밀번호는 ~~입니다.
// 어느순간부터는 새 비밀번호를 입력하세요로 뜬다. // 제공하는 측에서도 비밀번호가 뭔지 모름

void TestHash() 
{
	struct User
	{
		int userId = 0; // 1~int32_max
		string username;
	};

	vector<User> users;
	users.resize(1000); // 통은 1000개로 유지하는것으로 가정

	const int userId = 123456789;
	int key = (userId % 1000); // hash < 고유번호

	/// 123456789번 유저 정보 세팅
	users[key] = User{ userId, "Rookiss" };

	// 123456789번 유저 이름은?
	User& user = users[key];
	if (user.userId == userId) 
	{
		string name = user.username;
		cout << name << endl;
	}

	// 충돌 문제
	// 충돌이 발생한 자리를 대신해서 다른 빈자리를 찾아나서면 된다.
	// - 선형 조사법 (linear probing)
	// hash(key) + 1 -> hash(key) + 2
	// -- 너무 데이터가 몰리는 문제가 발생
	// - 이차 조사법 (quadratic probing)
	// hash(key) + 1 ^ 2 좀 더 몰리지 않게 하는것
	// - etc
	// 대표적 방법 : 체이닝
}

void TestHashTableChaining() 
{
	struct User 
	{
		int userId = 0;
		string username;
	};

	vector<vector<User>> users;
	users.resize(1000);

	const int userId = 123456789;
	int key = (userId % 1000);

	users[789].push_back(User{ 789, "Faker" });
	users[key].push_back(User{ userId, "Rookiss" });

	// 123456789번 유저 이름은?
	vector<User>& bucket = users[key];
	for (User& user : bucket) 
	{
		if (user.userId == userId) 
		{
			cout << user.username << endl;
		}
	}
}

int main()
{
#pragma region 실행부
	/*Vector<int> v;

	v.push_back(1);
	v.push_back(3);
	v.push_back(5);

	for (int i = 0; i < v.size(); i++) 
	{
		cout << v[i] << "\n";
	}

	v.pop_back();
	v.pop_back();

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << "\n";
	}

	cout << v.empty();*/


	/*RedBlackTree bst;

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(10);
	bst.Print();
	this_thread::sleep_for(1s);*/
#pragma endregion

	//TestTable();
	//TestHash();
	TestHashTableChaining();

	return 0;
}