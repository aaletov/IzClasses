//#include "MyVector.h"
//
//template<typename T>
//MyVector<T>::MyVector()
//{
//	array = new T[1];
//	arraySize = 1;
//	arrayLen = 0;
//}
//
//template<class T>
//int MyVector<T>::getArrayLen()
//{
//	return arrayLen;
//}
//
//template<class T>
//T& MyVector<T>::operator[](int i)
//{
//	return &(array + i);
//}
//
//template<class T>
//void MyVector<T>::push_back(T elem)
//{
//	if (arraySize > arrayLen)
//	{
//		array[arrayLen] = elem;
//		arrayLen++;
//	}
//	else
//	{
//		T* newArray = new T[arraySize * 2];
//		int i;
//		for (i = 0; i < arraySize; i++)
//		{
//			newArray[i] = array[i];
//		}
//		newArray[i] = elem;
//		arrayLen++;
//		arraySize *= 2;
//		delete[] array;
//		array = newArray;
//	}
//}
