#pragma once
template <typename T>

void sort(T& array, const int len)
{
	int i;
	int j;
	auto temp = array[0];
	for (i = 1; i < len; i++)
	{
		temp = array[i];
		j = i - 1;
		while (j > -1 && array[j] > temp)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = temp;
	}
}