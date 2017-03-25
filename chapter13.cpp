// chapter13.cpp : 定义控制台应用程序的入口点。
//二叉搜索树、平衡二叉树、红黑树

#include "stdafx.h"
#include<stdlib.h>
#include<time.h>
int main()
{
	BSTree T;
	AVL TB;
	RBTree rb;
	NodePoint rbHead=NULL;
	NodePoint head = TB.getHead();
	//srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int temp = 100+rand() % 1000;
		NodePoint p = new  Node{temp,NULL,NULL,NULL,0,BLACK};
		T.addNode(p);
		TB.addNode(head, NULL, temp);
		rb.insertNode(rbHead, temp);
		printf("%-8d", temp);
	}
	T.travers_BSTree(T.getHead());
	T.deleteNode(T.getHead(), 141);
	T.travers_BSTree(T.getHead());
	printf("\n");
	TB.travers_AVL(head);
	TB.deleteNode(head,124);
	TB.deleteNode(head, 100);
	printf("\n");
	TB.travers_AVL(head);
	printf("\n%d\n",head->height);
	//红黑树的插入
	printf("red-black-tree:\n");
	rb.travers_RBTree(rbHead);
    return 0;
}

