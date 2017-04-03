//程序的入口
#include"stdafx.h"
#include<stdlib.h>
#include<iostream>
using namespace std;
int main()
{
	OSTree tree;
	for (int i = 0; i < 10; i++)
	{
		int data = rand() % 900 + 100;
		cout << data << " ";
		tree.insertNode(data);
	}
	cout << endl;
	tree.travel_OSTree(tree.getRoot());
	cout <<endl<<"Rank(778)="<< tree.getRank(778)<<endl;
	tree.deleteNode(500);
	tree.travel_OSTree(tree.getRoot());
	return 0;
}