// Dynamic programming.cpp : 定义控制台应用程序的入口点。
//动态规划举例:钢管切割，矩阵的链乘，最长公共子序列（不要求连续），最优二叉搜索树(中序遍历保持初始序列不变)，0-1背包问题
//
#include "stdafx.h"
#include<iostream>
using namespace std;
int main()
{
	steelPipe sp(10);
	sp.calculateTable();
	sp.getSolution(10);
	matrixChain mc(6);
	mc.calculateTable();
	mc.getSolution(1, 6);
	lcs lcsClass;
	lcsClass.calculateTable();
	lcsClass.getSolution();
	cout << endl;
	OBST obst(5);
	obst.calculateTable();
	obst.getSolution(1,5);
	return 0;
}

