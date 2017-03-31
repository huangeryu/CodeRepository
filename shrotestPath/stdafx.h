// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//
#ifndef STDAFX
#define STDAFX
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include<limits.h>
#define MAX 5000
typedef struct point
{
	int data;
	int index;
	bool isIncluded;
	struct point * parent;
}* Mat;
void dijkstra(int*base, int size);
void printOut(Mat d, int size);
void floyd(int*base, int size);
#endif // !STDAFX
// TODO:  在此处引用程序需要的其他头文件
