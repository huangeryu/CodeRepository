// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include<iostream>
#include <stdio.h>
#include <tchar.h>
#include<vector>
using namespace std;
class matrixChain
{
protected:
	int size;
	int *c=new int[size*size];
	int *index = new int[size*size]{0};
	int *chain;
	const int Max = 1000000;
public:
	matrixChain(int size) :size(size+1)
	{
		chain = new int[size]{30,35,15,5,10,20,25};
	}
	void calculateTable();
	void getSolution(int from,int end);
	~matrixChain()
	{
		delete c, index, chain;
	}
};
class steelPipe
{
private:
	int size;
	int* c = new int[size+1];
	int* index = new int[size+1];
	int* price = new int[size + 1]{0,1,5,8,9,10,17,17,20,24,26};
public:
	steelPipe(int size):size(size)
	{
		this->c[0] = 0;
		this->price[0] = 0;
		this->index[0] = 0;
	}
	void calculateTable();
	void getSolution(int size);
	~steelPipe()
	{
		delete c;
		delete price;
	}
};
class lcs
{
private:
	char* A=new char[8]{' ','A','B','C','B','D','A','B'};
	char* B=new char[7]{' ','B','D','C','A','B','A'};
	int* c;
	int asize;
	int bsize;
public:
	lcs()
	{
		this->asize =8;
		this->bsize =7;
		c = new int[56]{0};
	}
	void calculateTable();
	void getSolution();
	~lcs()
	{
		delete c;
	}
};
class OBST
{
private:
	vector<double> p;
	vector<double>q;
	int size;
	const double MAX = 1000000;
	double *w=new double[size*size];
	double *c=new double[size*size];
	int *index=new int[size*size];
public:
	OBST(int size):size(size+1)
	{
		double a[] = {0,0.15,0.1,0.05,0.1,0.2};
		double b[] = { 0.05,0.1,0.05,0.05,0.05,0.1 };
		p.insert(p.begin(), a, a + 10);
		q.insert(q.begin(), b, b + 10);
	}
	void calculateTable();
	void getSolution(int from,int end);
	~OBST()
	{
		delete w,c,index; 
	}
};
class knapsack
{
private:
	int size;
	int capacity;
	int * w=new int[size];
	int * p=new int[size];
	int *c=new int [size*capacity];
public:
	knapsack(int size,int capacity):size(size+1),capacity(capacity+1)
	{
		
	}
	void calculateTable();
	void getSolution();
};
// TODO:  在此处引用程序需要的其他头文件
