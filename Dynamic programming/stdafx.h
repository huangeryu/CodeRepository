// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include<iostream>
#include <stdio.h>
#include <tchar.h>
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


// TODO:  在此处引用程序需要的其他头文件
