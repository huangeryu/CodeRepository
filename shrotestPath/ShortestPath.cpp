// ShortestPath.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
int main()
{
	int mat[6][6] = {
		{ 0,MAX,10,MAX,30,100 },
		{ MAX,0,5,MAX,MAX,MAX },
		{ MAX,MAX,0,50,MAX,MAX },
		{ MAX,MAX,MAX,0,MAX,10 },
		{ MAX,MAX,MAX,20,0,60 },
		{ MAX,MAX,MAX,MAX,MAX,0 }
	};
	dijkstra((int *)mat,6);
	floyd((int*)mat, 6);
    return 0;
}

