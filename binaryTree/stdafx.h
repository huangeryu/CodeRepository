// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#ifndef STDAFX
#define STDAFX
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
enum Color
{
	BLACK = 0,
	RED=1
};
typedef struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int height;
	Color color ;

}* NodePoint;
enum DataType
{
	NUREPEAT = 1,
	REPEAT = 0
};

//二叉搜索树类
class BSTree
{
private:
	struct Node *head;

public:
	BSTree()
	{
		this->head = NULL;
	}
	NodePoint searchNode(NodePoint, int, DataType type=REPEAT);
	void addNode(NodePoint);
	void deleteNode(NodePoint, int );
	NodePoint getHead();
	void travers_BSTree(NodePoint);
};
//binary balance tree
class AVL
{
private:
	struct Node *head;
	int* getMaxHeight(NodePoint, NodePoint);
public:
	AVL()
	{
		this->head = NULL;
	}
	//左旋转，支点的左边顺时针旋转
	NodePoint leftRotate(NodePoint& p);
	//右旋转，支点的右边逆时针旋转
	NodePoint rightRotate(NodePoint& p);
	//添加节点
	NodePoint addNode(NodePoint &head,NodePoint p,int data);
	//删除节点
	NodePoint deleteNode(NodePoint &head,int data);
	NodePoint deleteNode(NodePoint p);
	//遍历
	void travers_AVL(NodePoint head);
	NodePoint getHead();
	void adjust(NodePoint & parent);
};
class RBTree
{
private:
	NodePoint head;
public:
	void insertNode(NodePoint &head, int data);
	void deleteNode(NodePoint &head, int data);
	NodePoint leftRotate(NodePoint head);
	NodePoint rightRotate(NodePoint head);
	void travers_RBTree(NodePoint head);
	NodePoint searchByVal(NodePoint head, int data);
	void doubleBlackAdjust(NodePoint head);
};
#endif
// TODO:  在此处引用程序需要的其他头文件
