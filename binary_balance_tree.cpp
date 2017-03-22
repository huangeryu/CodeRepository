//二叉平衡树
#include"stdafx.h"
#include <assert.h>
//获得某个节点的高度

int* AVL::getMaxHeight(NodePoint tl, NodePoint tr)
{
	int*p = new int[2]{ 0,0 };
	int a = 0, b = 0;
	if (tl != NULL)a = tl->height;
	if (tr != NULL)b = tr->height;
	a > b ? p[0]=a:p[0]=b ;
	p[1] = a - b;
	return p;
}

//左旋
NodePoint AVL::leftRotate(NodePoint& p)
{
	if (p == NULL)return NULL;
	if (p->left == NULL)return p;
	NodePoint q = p->left;
	p->left = q->right;
	q->right = p;
	if (p->left != NULL)p->left->parent = p;
	q->parent = p->parent;
	p->parent = q;
	p->height = getMaxHeight(p->left, p->right)[0] + 1;
	q->height = getMaxHeight(q->left, q->right)[0] + 1;
	p = q;
	return q;
}
//右旋
NodePoint AVL::rightRotate(NodePoint& p)
{
	if (p == NULL)return NULL;
	if (p->right == NULL)return p;
	NodePoint q = p->right;
	p->right = q->left;
	if (p->right != NULL)p->right->parent = p;
	q->left = p;
	q->parent = p->parent;
	p->parent = q;
	p->height = getMaxHeight(p->left, p->right)[0] + 1;
	q->height = getMaxHeight(q->left, q->right)[0] + 1;
	p = q;
	return q;
}
//添加节点，递归返回时调整
NodePoint AVL::addNode(NodePoint &p,NodePoint parent,int data)
{
	if (p == NULL)
	{
		p = new Node {data,NULL,NULL,parent,1};
	}
	else
	{
		if (p->data >= data)
		{
			addNode(p->left,p, data);
		}
		else
		{
			addNode(p->right,p, data);
		}
		int *combox=getMaxHeight(p->left, p->right);
		p->height = combox[0] + 1;
		if (combox[1] == 2)
		{
			if (data < p->left->data)p=leftRotate(p);
			else
			{
				rightRotate(p->left);
				leftRotate(p);
			}
		}
		else if(combox[1]==-2)
		{
			if (data >= p->right->data)p=rightRotate(p);
			else
			{
				leftRotate(p->right);
				rightRotate(p);
			}
		}
	}

	return NULL;
}
void AVL::travers_AVL(NodePoint p)
{
	if (p != NULL)
	{
		travers_AVL(p->left);
		printf("%-5d:%d ", p->data,p->height);
		travers_AVL(p->right);
	}
}
NodePoint AVL::getHead()
{
	return this->head;
}
NodePoint AVL::deleteNode(NodePoint p)
{

	return NULL;
}
//查找要删除的节点，找到该节点的后继节点，删除该节点，调整父节点的高度
//根据高度进行调整
NodePoint AVL::deleteNode(NodePoint &head,int data)
{
	if (head == NULL)
	{
		return NULL;
	}
	else if(head->data==data)
	{
		if (head->right == NULL)
		{
			if (head->left != NULL)
			{
				NodePoint parent = head->parent;
				if (parent == NULL)
				{
					parent = head->left;
					delete head;
					head = parent;
					adjust(parent);
					return parent;
				}
				else
				{
					NodePoint temp = head->left;
					temp->parent = parent;
					delete head;
					head = temp;
					adjust(parent);
					return parent;
				}
			}
			else
			{
				NodePoint parent = head->parent;
				delete head;
				head = NULL;
				adjust(parent);
				return parent;
			}
		}
		else
		{
			NodePoint sNode = head->right;
			while (sNode->left != NULL)
			{
				sNode = sNode->left;
			}
			head->data=sNode->data;
			NodePoint parent = sNode->parent;
			if (sNode->right == NULL)
			{
				parent->left == sNode ? parent->left=NULL:parent->right=NULL ;
				delete sNode;
				sNode = NULL;
				adjust(parent);
				return parent;
			}
			else
			{
				parent->left == sNode ? parent->left=sNode->right:parent->right=sNode->right ;
				sNode->right->parent = parent;
				delete sNode;
				sNode = NULL;
				adjust(parent);
				return parent;
			}
		}
	}
	else if (head->data>data)
	{
		deleteNode(head->left, data);
		adjust(head);
	}
	else
	{
		deleteNode(head->right, data);
		adjust(head);
	}
	return NULL;
}
void AVL::adjust(NodePoint & parent)
{
	if (parent != NULL)
	{
		int *p = getMaxHeight(parent->left, parent->right);
		parent->height = p[0]+1;
		if (p[1] == 2)
		{
			int *lp = getMaxHeight(parent->left->left, parent->left->right);
			if (lp[1] > 0)
			{
				leftRotate(parent);
			}
			else
			{
				rightRotate(parent->left);
				leftRotate(parent);
			}
		}
		else if (p[1] == -2)
		{
			int *lp = getMaxHeight(parent->right->left, parent->right->right);
			if (lp[1] > 0)
			{
				leftRotate(parent->right);
				rightRotate(parent);
			}
			else
			{
				rightRotate(parent);
			}
		}
	}
}