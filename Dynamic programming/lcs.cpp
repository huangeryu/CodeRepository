//最长公共子序列（longest-common-subsequence problem）
//问题描述：A，B是两序列，求最长公共子序列Z
//解决思路：
//情况1：如果A、B的最后一元素相同，则A、B的最后的这个元素一定在最长公共子序列中，并且处在最后的位置
//情况2：如果A、B的最后的元素不相同，则从A去掉最后的元素与B的最长公共子序列、B去掉最后的元素与A的最长公共子序列中选最长的公共子序列
//模型表示：
//c[i,j]={c[i-1,j-1] A[i]=B[j];max{c[i,j-1],c[i-1,j]}A[i]!=B[j]};
#include"stdafx.h"
using namespace std;
void lcs::calculateTable()
{
	for (int j = 0; j < this->bsize; j++)
	{
		c[j] = 0;
	}
	for (int i = 0; i < this->asize; i++)
	{
		c[i*this->bsize] = 0;
	}
	for (int i = 1; i < this->asize; i++)
	{
		for (int j = 1; j < this->bsize; j++)
		{
			if (A[i] == B[j])
			{
				c[i*this->bsize + j] = c[(i - 1)*this->bsize + j - 1]+1;
			}
			else
			{
				if (c[i*this->bsize + j - 1] > c[(i - 1)*this->bsize + j])
				{
					c[i*this->bsize + j] = c[i*this->bsize + j - 1];
				}
				else
				{
					c[i*this->bsize + j] = c[(i - 1)*this->bsize + j];
				}
			}
		}
	}
}
void lcs::getSolution()
{
	for (int i = 0; i < 56; i++)
	{
		
		if (i % 7 == 0)
		{
			cout << endl;
		}
		cout << c[i] << " ";
	}
}