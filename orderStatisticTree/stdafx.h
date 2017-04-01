// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
enum Color
{
	Rad = 0,
	BLACK=1
};
typedef struct Node
{
	int data;
	int size;
	Node* rightchild;
	Node* leftchild;
	Node* parent;
	Color color;
	Node(int data,Color color=Rad,int size=1)
	{
		this->data = data;
		this->size = size;
		this->rightchild = NULL;
		this->leftchild = NULL;
		this->parent = NULL;
		this->color = color;
	}
}* NodePoint;
class OSTree
{
private:
	NodePoint T;
public:
	OSTree()
	{
		this->T = NULL;
	}
	void insertNode(int data);
	void deleteNode(int data);
	NodePoint searchNode(int date);
	void adjustBlack(NodePoint& p);
	void travel_OSTree(NodePoint head);
	int getRank(int data);
	void leftRatate(NodePoint p);
	void rightRatate(NodePoint p);
	int getSize(NodePoint p);
};

// TODO:  在此处引用程序需要的其他头文件
