//实现红黑树的插入与删除
#include"stdafx.h"
#include<assert.h>
#include<stdio.h>
//节点左旋，该节点是父节点的右孩子，以该节点为中心，
//父节点做逆时针翻转
//A-B ---> B-A
//返回值该结点
NodePoint RBTree::leftRotate(NodePoint head)
{
	if (head == NULL||head->parent==NULL)return head;
	assert(head == head->parent->right);
	NodePoint parent = head->parent;
	Color temp = head->color;
	head->color = parent->color;
	parent->color = temp;
	parent->right = head->left;
	if (head->left != NULL)head->left->parent = parent;
	head->left = parent;
	head->parent=parent->parent;
	if (head->parent != NULL)
	{
		head->parent->left == parent ?head->parent->left=head :head->parent->right=head ;
	}
	parent->parent = head;
	return head; 
}
//右旋，该节点是父节点的左孩子
NodePoint RBTree::rightRotate(NodePoint head)
{
	if (head == NULL || head->parent == NULL)return head;
	assert(head == head->parent->left);
	NodePoint parent = head->parent;
	Color temp = head->color;
	head->color=parent->color;
	parent->color = temp;
	parent->left = head->right;
	if (head->right != NULL)head->right->parent = parent;
	head->right = parent;
	head->parent = parent->parent;
	if (head->parent != NULL)
	{
		head->parent->left == parent ?head->parent->left=head :head->parent->right=head ;
	}
	parent->parent = head;
	return head;
}
//红黑树的插入操作
void RBTree::insertNode(NodePoint &head, int data)
{
	NodePoint p = searchByVal(head, data);
	if (p == NULL)
	{
		head = new Node{ data,NULL,NULL,NULL,0,BLACK };
		return;
	}
	if (p->parent == NULL)
	{
		p->color = BLACK;
		return;
	}
	while (p->parent->color!=BLACK)
	{
		NodePoint parent = p->parent;
		NodePoint grandFather = parent->parent;
		if (grandFather == NULL)
		{
			parent->color = BLACK;
		}
		if (grandFather->left == parent)
		{
			NodePoint parent_brother = grandFather->right;
			if (parent_brother != NULL)
			{
				if (parent_brother->color == RED)
				{
					grandFather->color = RED;
					parent->color = BLACK;
					parent_brother->color = BLACK;
					p = grandFather;
					if (p->parent == NULL)
					{
						p->color = BLACK;
						return;
					}
				}
				else
				{
					if (parent->left == p)
					{
						rightRotate(parent);
					}
					else
					{
						leftRotate(p);
						rightRotate(p);
						p = p->left;
					}
				}
			}
			else
			{
				if (parent->left == p)
				{
					rightRotate(parent);
				}
				else
				{
					leftRotate(p);
					rightRotate(p);
					p = p->left;
				}
			}
		}
		else if(grandFather->right==parent)
		{
			NodePoint parent_brother = grandFather->left;
			if (parent_brother != NULL)
			{
				if (parent_brother->color == RED)
				{
					parent->color = BLACK;
					parent_brother->color = BLACK;
					grandFather->color = RED;
					p = grandFather;
					if (p->parent == NULL)
					{
						p->color = BLACK;
						return;
					}
				}
				else
				{
					if (parent->left == p)
					{
						rightRotate(p);
						leftRotate(p);
						p = p->right;
					}
					else
					{
						leftRotate(parent);
					}
				}
			}
			else
			{
				if (parent->left == p)
				{
					rightRotate(p);
					leftRotate(p);
					p = p->right;
				}
				else
				{
					leftRotate(parent);
				}
			}
		}
	}
	while (head->parent != NULL)
	{
		head = head->parent;
	}
}
//红黑树的删除操作
void RBTree::deleteNode(NodePoint head, int data)
{

}
void RBTree::travers_RBTree(NodePoint head)
{
	using namespace std;
	if (head == NULL)return;
	travers_RBTree(head->right);
	printf("%5d", head->data);
	travers_RBTree(head->left);
}
//根据值对红黑树进行搜索
//如果树是空的，返回NULL
//如果找到返回该节点，如果找不到则插入该节点，并返回该节点
NodePoint RBTree::searchByVal(NodePoint head, int data)
{
	if (head == NULL)return NULL;
	if (head->data == data)return head;
	else if (head->data > data)
	{
		if (head->left == NULL)
		{
			head->left = new Node{data,NULL,NULL,head,0,RED};
			return head->left;
		}
		searchByVal(head->left, data);
	}
	else
	{
		if (head->right == NULL)
		{
			head->right = new Node{ data,NULL,NULL,head,0,RED };
			return head->right;
		}
		searchByVal(head->right, data);
	}
}