//单源点的最短路径--Dijkstra
#include"stdafx.h"
#include<iostream>
//point mat[row][col]
void dijkstra(int* base, int size)
{
	point* d = new point[size];
	for (int i = 0; i < size; i++)
	{
		(d + i)->data = base[i];
		(d + i)->isIncluded = false;
		(d + i)->parent = NULL;
		(d + i)->index = i;
	}
	int min = 0;
	int index = 0;
	for (int i = 1; i < size; i++)
	{
		int dmin=INT_MAX;
		int dindex = 0;
		for (int j = 1; j < size; j++)
		{
			if (!d[j].isIncluded)
			{
				int temp = min + base[index*size + j];
				if (temp < base[j])
				{
					d[j].data = temp;
					d[j].parent = d+index;
				}
				else if (temp >= base[j])
				{
					d[j].data = base[j];
					if(d[j].data!=MAX)d[j].parent = d;
				}
				if (d[j].data < dmin)
				{
					dmin = d[j].data;
					dindex = j;
				}
			}
		}
		index=dindex;
		d[index].isIncluded = true;
		min = dmin;
	}
	printOut(d, size);
}
void printOut(Mat d, int size)
{
	using namespace std;
	for (int i = 0; i < size; i++)
	{
		point *p = d + i;
		while (p->parent != NULL)
		{
			cout << p->index<<"<----";
			p = p->parent;
		}
		cout << p->index << endl;
	}
}