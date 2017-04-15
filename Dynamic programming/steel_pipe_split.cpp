//钢管切割问题
//问题描述:长度不同的钢管，对应的价格也不同，长的钢管可以通过切割变成小的钢管
//如何切割使得到的钢管价格最大
//模型：c[j]=max{p[k]+c[j-k]};
#include"stdafx.h"
//计算c[j]
void steelPipe::calculateTable()
{
	for (int i = 1; i <= this->size; i++)
	{
		int sum = 0;
		int id = 0;
		for (int k = 1; k <= i; k++)
		{
			if (sum < price[k] + c[i - k])
			{
				sum = price[k] + c[i - k];
				id = k;
			}
		}
		c[i] = sum;
		this->index[i] = id;
	}
	for (int i = 0; i <= size; i++)
	{
		using namespace std;
		cout << this->index[i] << "  ";
	}
}
//打印出切割方案
void steelPipe::getSolution(int size)
{
	using namespace std;
	if (index[size] != size)
	{
		getSolution(index[size]);
		getSolution(size - index[size]);
	}
	else
	{
		cout << "e" << size<<"  ";
	}
}