//没对顶点的最短路径--floyd算法
#include"stdafx.h"
#include<iostream>
void floyd(int* base,int size)
{
	using namespace std;
	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				int temp = base[i*size + k] + base[k*size + j];
				if (temp < base[i*size + j])base[i*size + j] = temp;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int temp = base[i*size + j];
			if (temp == MAX)
			{
				cout << "#" << "  ";
			}
			else
			{
				cout <<temp<< "  ";
			}
			
		}
		cout << endl;
	}
}