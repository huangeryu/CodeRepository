//矩阵链乘
//问题描述：多个矩阵相乘，可以利用括号化减少计算量
//模型：c[i,j]=min{c[i,k]+c[k+1,j]+cost(i,k,j)},k∈[i,j);
#include"stdafx.h"
void matrixChain::calculateTable()
{
	using namespace std;
	//初始化this->c
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i > j)c[i*size+j] = this->Max;
			else if(i==j)
			{
				c[i*size+j] = 0;
			}
		}
	}
	//计算
	for (int length = 2; length < this->size; length++)
	{
		for (int i = 1; i < this->size; i++)
		{
			int j = i + length - 1;
			if (j < size)
			{
				int min = Max;
				for (int k = i; k < j; k++)
				{
					int temp = c[i*size + k] + c[(k + 1)*size + j] + chain[i-1] * chain[k] * chain[j];
					if (min > temp)
					{
						min = temp;
						index[i*size + j] = k;
					}
				}
				c[i*size + j] = min;
			}
		}
	}
}
void matrixChain::getSolution(int from,int end)
{
	using namespace std;
	if (end == from)
	{
		cout << from << " ";
	}
	else
	{
		cout << "(";
		getSolution(from, index[from*size + end]);
		getSolution(index[from*size + end] + 1, end);
		cout << ")";
	}
}