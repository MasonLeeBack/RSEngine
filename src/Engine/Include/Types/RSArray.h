/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSArray.h

*/

#ifndef _RSARRAY_H_
#define _RSARRAY_H_

#include <memory>
#include <initializer_list>

template<class T>
class RSArray {
	T* arr;
	int capacity;
	int current;
public:
	RSArray();
	~RSArray();

	void clear();

	void push(T data);
	void push(T data, int index);

	T get(int index);
	T* ptr();

	void pop();

	int size();
	int getCapacity();

	RSArray<T>& operator=(const RSArray<T>& rhs);
	RSArray<T>& operator=(std::initializer_list<T> _init);
};

template<class T>
inline RSArray<T>::RSArray()
{
	arr = new T[1];
	capacity = 1;
	current = 0;
}

template<class T>
inline RSArray<T>::~RSArray()
{
}

template<class T>
inline void RSArray<T>::clear()
{
	if (arr) {
		delete[] arr;

		arr = new T[1];
		capacity = 1;
		current = 0;
	}
}

template<class T>
inline void RSArray<T>::push(T data)
{
	if (current == capacity) {
		T* temp = new T[2 * capacity];

		for (int i = 0; i < capacity; i++) {
			temp[i] = arr[i];
		}

		delete[] arr;
		capacity *= 2;
		arr = temp;
	}

	arr[current] = data;
	current++;
}

template<class T>
inline void RSArray<T>::push(T data, int index)
{
	if (index == capacity)
		push(data);
	else
		arr[index] = data;
}

template<class T>
inline T RSArray<T>::get(int index)
{
	if (index < current)
		return arr[index];

	return NULL;
}

template<class T>
inline T* RSArray<T>::ptr()
{
	return arr;
}

template<class T>
inline void RSArray<T>::pop()
{
	current--;
}

template<class T>
inline int RSArray<T>::size()
{
	return current;
}

template<class T>
inline int RSArray<T>::getCapacity()
{
	return capacity;
}

template<class T>
inline RSArray<T>& RSArray<T>::operator=(const RSArray<T>& rhs)
{
	return *this;
}

template<class T>
inline RSArray<T>& RSArray<T>::operator=(std::initializer_list<T> _init)
{
	clear();

	for (auto member : _init) {
		push(member);
	}

	return *this;
}

#endif // _RSARRAY_H_
