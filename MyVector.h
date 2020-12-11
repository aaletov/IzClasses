#pragma once
#include <iostream>

template <typename T>
void copyDynamic(T* in, T* out, int length)
{
	for (int i = 0; i < length; i++)
	{
		out[i] = in[i];
	}
}

template <typename T>
void copyDynamic(const T* in, T* out, int length)
{
	for (int i = 0; i < length; i++)
	{
		out[i] = in[i];
	}
}

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
	MyVector(int len)
	{
		array = new T[len];
		arraySize = len;
		arrayLen = len;
	}
	~MyVector()
	{
		try
		{
			for (int i = 0; i < arrayLen; i++)
			{
				array[i].~T();
			}
		}
		catch (const std::exception&)
		{
			delete[] array;
		}
	}
	bool operator==(MyVector<T>& rvalue)
	{
		if (arrayLen != rvalue.getArrayLen() || arraySize != rvalue.getArraySize())
		{
			return false;
		}
		else
		{
			for (int i = 0; i < arrayLen; i++)
			{
				if (!(array[i] == rvalue[i]))
				{
					return false;
				}
			}
		}
		return true;
	}
	T* getDynamic()
	{
		return array;
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
	int getArraySize()
	{
		return arraySize;
	}
	MyVector<T>& operator=(MyVector<T> &in)
	{
		delete[] array;
		array = new T[in.getArrayLen()];
		copyDynamic(in.getDynamic(), array, in.getArrayLen());
		arrayLen = in.getArrayLen();
		arraySize = in.getArraySize();

		return *this;
	}
	T& operator[](int i)
	{
		if (i > arrayLen)
		{
			throw - 1;
		}
		return *(array + i);
	}
	void push_back(T& elem)
	{
		if (arraySize > arrayLen)
		{
			array[arrayLen] = elem;
			arrayLen++;
		}
		else
		{
			T* tempArray = new T[arraySize * 2];
			copyDynamic(array, tempArray, arrayLen);
			delete[] array;

			array = new T[arraySize * 2];
			copyDynamic(tempArray, array, arrayLen);
			array[arraySize] = elem;

			arrayLen++;
			arraySize *= 2;
			delete[] tempArray;
		}
	}
};

//template<class T>
//class MyVectorPoly
//{
//private:
//	MyVector<T> vectors;
//public:
//	MyVectorPoly()
//	{
//	}
//	MyVectorPoly(int* lengths, int dimensions)
//	{
//		if (dimensions == 1)
//		{
//			for (int i = 0; i < lengths[0]; i++)
//			{
//				this->push_back(NULL);
//			}
//		}
//
//		int* copyLengths;
//		copyDynamic(lengths, copyLengths, dimensions);
//
//		for (int i = 0; i < lengths[0]; i++)
//		{
//			this->push_back(MyVector<T>(++copyLengths, dimensions - 1));
//		}
//
//		delete[] copyLengths;
//	}
//	bool contains(MyVector<T> elem)
//	{
//		for (int i = 0; i < arrayLen; i++)
//		{
//			if (array[i] == elem)
//			{
//				return true;
//			}
//		}
//		return false;
//	}
//}
