//最优二叉搜索树(optimal binary search tree)
//问题描述：给定序列K及每个点的概率，构造一颗访问节点最少的树，该树的中序遍历和序列k的顺序一样
//分析思路：如果树T是满足上述条件的最优树，这它的左右子树也是一颗最优树（具有最优子结构）
//模型：c[i,j]={min{c[i,k-1]+c[k+1,j]+w[i,j]} k∈[i,j] i<=j,q[i-1] i=j+1};
#include"stdafx.h"
void OBST::calculateTable()
{
	for (int i = 1; i < this->size; i++)
	{
		c[i*size + i - 1] = this->q[i-1];
		w[i*size + i - 1] = this->q[i - 1];
	}
	for (int length = 1; length <size; length++)
	{
		for (int i = 1; i <size-length+1; i++)
		{
			int j = i + length - 1;
			if (j < size)
			{
				double min = MAX;
				w[i*size + j] = w[i*size + j - 1] + p[j] + q[j];
				for (int k = i; k <= j; k++)
				{
					double temp = c[i*size + k - 1] + c[(k + 1)*size + j] + w[i*size+j];
					if (temp < min)
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
void OBST::getSolution(int from,int end)
{//获得前序遍历
	if (from <= end)
	{
		int temp = index[from*size + end];
		cout << temp<<" ";
		getSolution(from, temp - 1);
		getSolution(temp + 1, end);
	}
}