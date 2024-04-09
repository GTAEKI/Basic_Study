#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<queue>
#include<deque>
#include "LinkedList.h"
using namespace std;


template<typename T>
class ArrayQueue
{
public:
    ArrayQueue() :_front(0), _back(0), _size(0)
    {
        _container.resize(100);
    }

    void push(const T& value)
    {
        // TODO:다 찼는지 체크
        if (_size == _container.size()) 
        {
            int newSize = max(1, _size * 2);
            vector<T> newData;
            newData.resize(newSize);

            // 데이터 복사
            for (int i = 0; i < _size; i++) 
            {
                int index = (_front + i) % _container.size();
                newData[i] = _container[index];
            }

            _container.swap(newData);
            _front = 0;
            _back = _size;
        }
        
        _container[_back] = value;
        _back = (_back + 1) % _container.size();
        _size++;
    }

    void pop()
    {
        // TODO: 비어있는지 체크
        _front = (_front + 1) % _container.size();
        _size--;
    }

    T& front()
    {
        // TODO : 데이터가 있는지 체크
        return _container[_front];
    }

    bool empty()
    {
        return _size == 0;
    }

    int size()
    {
        return _size;
    }

private:
    vector<T> _container;

    int _front = 0;
    int _back = 0;
    int _size = 0;
};


template<typename T>
class ListQueue
{
public:
    void push(const T& value) 
    {
        _container.push_back(value);
    }

    void pop() 
    {
        // erase를 함수로 지원한다고 해도 빠르게 동작한다는 보장이 없다.
        //_container.erase(_container.begin()); 
        
        // 동적배열 보다는 연결리스트로 만드는게 일단은 더 간단해 보임
        _container.pop_front();

        /*vector<T> temp;
        temp.reserve(_container.size() - 1);
        for (int i = 1; i < _container.size(); i++) 
        {
            temp.push_back(_container[i]);
        }
        _container.clear();
        _container = temp;*/
    }

    T& front() 
    {
        return _container.front();
    }

    bool empty() 
    {
        return _container.empty();
    }

    int size() 
    {
        return _container.size();
    }

private:
    deque<T> _container;
    //list<T> _container;
    //vector<T> _container;
};


int main()
{
    vector<int> v(3, 1);
    deque<int> dq(3, 1);

    v.push_back(2);
    v.push_back(2);

    dq.push_back(2);
    dq.push_back(2);

    dq.push_front(3);
    dq.push_front(3);

    // deque 의 동작원리
    // 중간 삽입 삭제 (BAD / BAD)
    // 처음 끝 삽입 삭제
    // 임의 접근


    return 0;

    ////ListQueue<int> q;

    //ArrayQueue<int> q; // stack 및 queue는 deque를 기본 컨테이너로 활용을 한다.

    //for (int i = 0; i < 100; i++) q.push(i);

    //while (q.empty() == false) 
    //{
    //    int value = q.front();
    //    q.pop();
    //    cout << value << endl;
    //}

    //int size = q.size();
    //cout << size << endl;

    //return 0;
}