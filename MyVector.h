#pragma once
template <class T>
class MyVector
{
private:
	T* array;
	int arraySize;
	int arrayLen;
public:
	MyVector()
	{
		array = new T[1];
		arraySize = 1;
		arrayLen = 0;
	}
	~MyVector()
	{
		delete[] array;
	}
	bool contains(T& elem)
	{
		for (int i = 0; i < arrayLen; i++)
		{
			if (array[i] == elem)
			{
				return true;
			}
		}
		return false;
	}
	int getArrayLen()
	{
		return arrayLen;
	}
	T& operator[](int i)
	{
		return *(array + i);
	}
	void push_back(T elem)
	{
		if (arraySize > arrayLen)
		{
			array[arrayLen] = elem;
			arrayLen++;
		}
		else
		{
			T* newArray = new T[arraySize * 2];
			int i;
			for (i = 0; i < arraySize; i++)
			{
				newArray[i] = array[i];
			}
			newArray[i] = elem;
			arrayLen++;
			arraySize *= 2;
			delete[] array;
			array = newArray;
		}
	}
};

#include "MyVector.cpp"

