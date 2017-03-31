//二叉查找树
#include "stdafx.h"
#include<assert.h>

	//在二叉搜索树中查找值为@data的节点
	//二叉树为空，返回NULL
	//没有该节点，返回要插入的父节点

	NodePoint BSTree::searchNode(NodePoint head, int data, DataType type )
	{
		if (head == NULL)return NULL; 
		NodePoint pre=NULL,temp=head;
		while (temp != NULL)
		{
			pre = temp;
			if (temp->data == data&&type==NUREPEAT)return pre;
			else if(data>=temp->data)
			{
				temp = temp->right;
			}else
			{
				temp = temp->left;
			}
		}
		return pre;
	}
	void BSTree::addNode(NodePoint p)
	{
		NodePoint pre = searchNode(this->head,p->data);
		if (pre == NULL)
		{
			this->head = p;
			return;
		}
		if (p->data >= pre->data)
		{
			pre->right = p;
			p->parent = pre;
		}
		else
		{
			pre->left = p;
			p->parent = pre;
		}
	}
	void BSTree::deleteNode(NodePoint head,int data)
	{
		if (head != NULL)
		{
			NodePoint pre = searchNode(head,data, NUREPEAT);
			assert(pre != NULL);
			printf("pre->data=%d\n", pre->data);
			if (pre->data == data)
			{
				deleteNode(pre->right, data);
				NodePoint temp = searchNode(pre->right, data);
				if(temp==NULL)
				{
					if (pre->parent == NULL)
					{
						head = pre->left;
						pre->left != NULL ? pre->left->parent=NULL: 0;
					}
					else
					{
						pre == pre->parent->left ? pre->parent->left = pre->left 
							:pre->parent->right=pre->left ;
						{if(pre->left!=NULL)pre->left->parent = pre->parent; };
					}	
			    }
			    else
			    {
					pre->data = temp->data;
					if (temp->right == NULL)
					{
						(temp == temp->parent->left) ? temp->parent->left = NULL : temp->parent->right = NULL;
					}
					else
					{
						temp == temp->parent->left ? temp->parent->left=temp->right
							: temp->parent->right = temp->right;
						temp->right->parent = temp->parent;
					}
				}
				delete temp;
			}
		}
	}
	NodePoint BSTree::getHead()
	{
		return this->head;
	}
	void BSTree::travers_BSTree(NodePoint p)
	{
		if (p != NULL)
		{
			travers_BSTree(p->left);
			printf("%-8d", p->data);
			travers_BSTree(p->right);
		}
	}
