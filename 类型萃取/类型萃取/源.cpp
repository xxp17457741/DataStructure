#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "typetraits.h"
#include<string>
using namespace std;

template<typename T>

class SeqList
{
public:
	SeqList()
		:_size(0)
		, _capacity(0)
	{
		_CheckCapacity();
	}
	void PushBack(const T& d);
	void PopBack();
	void PushFront(const T& d);
	void PopFront();
	int Find(const T& d);
	void Insert(int pos, const T& d);
	void Sort();
	template<typename T>
	friend ostream& operator<<<T>(ostream& output, const SeqList<T>& s);
private:
	void _CheckCapacity()
	{
		if (_size == _capacity)
		{
			T* tmp = new T[2 * _capacity + 3];
			if (TypeTraits<T>::IsPodType().Get())
			{
				memcpy(tmp, _data, sizeof(T)*_size);
			}
			else
			{
				for (int i = 0; i < _size; i++)
				{
					tmp[i] = _data[i];
				}
			}
			delete[] _data;
			_data = tmp;
			_capacity = 2 * _capacity + 3;
		}
	}
private:
	T* _data;
	int _size;
	int _capacity;
};
template<typename T>
void SeqList<T>::PushBack(const T& d)
{
	_CheckCapacity();
	_data[_size] = d;
	_size++;
}
template<typename T>
void SeqList<T>::PopBack()
{
	_size--;
}
template<typename T>
void SeqList<T>::PushFront(const T& d)
{
	_CheckCapacity();
	for (int i = _size; i >0; i--)
	{
		_data[i] = _data[i - 1];
	}
	_data[0] = d;
	_size++;
}
template<typename T>
void SeqList<T>::PopFront()
{

	for (int i = 0; i < _size; i++)
	{
		_data[i] = _data[i + 1];
	}
	_size--;
}

template<typename T>
int SeqList<T>::Find(const T& d)
{
	for (int i = 0; i < _size; i++)
	{
		if (_data[i] == d)
			return i;
	}
	return -1;
}

template<typename T>
void SeqList<T>::Insert(int pos, const T& d)
{
	_CheckCapacity();
	for (int i = _size; i > pos; i--)
	{
		_data[i] = _data[i - 1];
	}
	_data[pos] = d;
	_size++;
}

template<typename T>
void SeqList<T>::Sort()
{
	int i = 0;
	int j = 0;
	int flag = 0;
	for (i = 0; i < _size; i++)
	{
		flag = 0;
		for (j = 0; j < _size - 1 - i; j++)
		{
			if (_data[j]>_data[j + 1])
			{
				T tmp = _data[j];
				_data[j] = _data[j + 1];
				_data[j + 1] = tmp;
				flag = 1;
			}

		}
		if (flag == 0)
			break;
	}
}
template<typename T>
ostream& operator<<(ostream& output, const SeqList<T>& s)
{
	for (int i = 0; i < s._size; i++)
	{
		output << s._data[i] << " ";
	}
	return output;
}
int main()
{
	/*SeqList<string> s;
	s.PushBack("11111");
	s.PushBack("3333333");
	s.PushBack("22222222");
	s.PushBack("2222222");
	s.PushBack("1111111");
	s.PushBack("55555555");*/
	SeqList<int> s;
	s.PushBack(1);
	s.PushBack(2);
	s.PushBack(3);
	s.PushBack(4);


	cout << s << endl;
	getchar();
	return 0;
}
